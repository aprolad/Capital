#include "Map.h"
#include"Header.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>


double find_angle(glm::vec2 vec1, glm::vec2 vec2)
{
    float angleRadians = atan2(vec2.y, vec2.x) - atan2(vec1.y, vec1.x);

    // make sure the angle is between 0 and 2π radians
    if (angleRadians < 0.0f) {
        angleRadians += 2.0f * glm::pi<float>();
    }
    return angleRadians * 180/M_PI;
}
struct forbidden_zone
{
    std::vector<GLfloat> intersection_shape;
    std::vector<glm::vec3> points;
    double s_angle, b_angle;
    glm::vec2 first_point()
    {
        if (intersection_shape.size() > 1)
            return glm::vec2(intersection_shape[0], intersection_shape[1]);
        else
            return glm::vec2(0, 0);
    }
    glm::vec2 last_point()
    {
        if (intersection_shape.size() > 2)
            return glm::vec2(intersection_shape[intersection_shape.size()-3], intersection_shape[intersection_shape.size()-2]);
        else
            return glm::vec2(0, 0);
    }
    void reverse()
    {
        points.clear();
        for (int i = 0; i < intersection_shape.size(); i += 3)
        {
            glm::vec3 t(intersection_shape[i], intersection_shape[i+1], intersection_shape[i+2]);
            points.push_back(t);
        }
        std::reverse(points.begin(), points.end());
        intersection_shape.clear();
        for (auto i : points)
        {
            intersection_shape.push_back(i.x);
            intersection_shape.push_back(i.y);
            intersection_shape.push_back(i.z);
        }
    }
};
float angleBetweenLineAndAxis(glm::vec2 linePoint1, glm::vec2 linePoint2, char axis = 'x') {
    glm::vec2 lineDir = linePoint2 - linePoint1;

    // Create a unit vector in the direction of the specified axis
    glm::vec2 unitVector;
    if (axis == 'x') {
        unitVector = glm::vec2(1.0f, 0.0f);
    }
    else if (axis == 'y') {
        unitVector = glm::vec2(0.0f, 1.0f);
    }
    else {
        std::cerr << "Invalid axis specified." << std::endl;
        return 0.0f;
    }

    float cosTheta = glm::dot(lineDir, unitVector) / (glm::length(lineDir) * glm::length(unitVector));
    float theta = glm::acos(cosTheta);

    if (lineDir.y < 0) {
        theta = 2 * glm::pi<float>() - theta;
    }

    return theta;
}

bool is_forbidden(double angle, std::vector<forbidden_zone> forbidden_angle)
{
    for (auto a : forbidden_angle)
    {
        if (angle > a.s_angle && angle < a.b_angle)
            return true;
    }
    return false;
}
// Find intersection point of two line segments in 2D space
inline glm::vec2 findIntersection(glm::vec2* p1, glm::vec2* p2, glm::vec2* q1, glm::vec2* q2) {
    glm::vec2 intersection(GLfloat(0), GLfloat(0));
    GLfloat det, t, u;
    const GLfloat EPSILON = 0.00000001f;

    det = (q2->y - q1->y) * (p2->x - p1->x) - (q2->x - q1->x) * (p2->y - p1->y);
    if (det == 0) {
        return intersection; // Lines are parallel, no intersection
    }

    t = ((q2->x - q1->x) * (p1->y - q1->y) - (q2->y - q1->y) * (p1->x - q1->x)) / det;
    u = ((p2->x - p1->x) * (p1->y - q1->y) - (p2->y - p1->y) * (p1->x - q1->x)) / det;

    if (t >= -EPSILON && t <= 1 + EPSILON && u >= -EPSILON && u <= 1 + EPSILON) {
        intersection.x = p1->x + t * (p2->x - p1->x);
        intersection.y = p1->y + t * (p2->y - p1->y);
    }

    return intersection;
}

Vertex transformCoordinates(double longitude, double latitude)
{
    Vertex t;
    t.position.x = (longitude + 180.0) * (1000.0 / 360.0) - 500;
    t.position.y = (1 - log(tan(latitude * M_PI / 180.0) + 1 / cos(latitude * M_PI / 180.0)) / M_PI) * 500.0 - 500;
    return t;
}
int Map::init()
{
    GDALAllRegister();
    OGRRegisterAll();
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    // Open Shapefile
    GDALDataset* poDS = (GDALDataset*)GDALOpenEx("Graphics/map.shp", GDAL_OF_VECTOR | GDAL_OF_READONLY, NULL, NULL, NULL);

    if (poDS == NULL) {
        std::cerr << "Failed to open Shapefile" << std::endl;
        return -1;
    }

    // Get the first layer in the Shapefile
    OGRLayer* poLayer = poDS->GetLayer(0);

    // Set up a projection from geographic coordinates to Mercator coordinates
    OGRSpatialReference oSrcSRS, oDstSRS;
    oSrcSRS.SetWellKnownGeogCS("WGS84");
    OGRFeature* poFeature = NULL;
    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != NULL)
    {
        // Get the geometry of the feature
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();

        vertices.resize(0);
        if (poGeometry->getGeometryType() == wkbPolygon)
        {
            OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
            printf("Processing polygon with %d rings\n", poPolygon->getExteriorRing()->getNumPoints() + 1);
            Vertex v;
            Line t;

            for (int i = 0; i < poPolygon->getExteriorRing()->getNumPoints(); i++)
            {
                if (i != 0)
                    t.start = v.position;
                v = transformCoordinates(poPolygon->getExteriorRing()->getX(i), poPolygon->getExteriorRing()->getY(i));
                t.end = v.position;
                if (i != 0)
                {
                    lines.push_back(t);
                }
                center_point.position.x += v.position.x;
                center_point.position.y += v.position.y;
                vertex_count++;
                vertices.push_back(v);
            }
            map_features.push_back(vertices);
        }
    }

    center_point.position.x /= vertex_count;
    center_point.position.y /= vertex_count;
    size = 18;
   // x = 100;
    y = -100;
    OGRFeature::DestroyFeature(poFeature);

}
void Map::draw_border()
{
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.5, 0.5, 1, 1);
    draw_line(1040, -165, 1040, -990);
    draw_line(-330, -165, -330, -990);
    draw_line(-330, -165, 1040, -165);
    draw_line(-330, -990, 1040, -990);
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0.0, 0.0, 0.0, 1);
}
int Map::draw()
{
    {
        glUseProgram(shaderProgram);
        glm::mat4 trans = glm::mat4(1);
        GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        draw_border();

        trans = glm::mat4(1);
        trans = glm::translate(trans, glm::vec3(500, 500, 0.0f));
        trans = glm::scale(trans, glm::vec3(size, size, size));
        //trans = glm::translate(trans, glm::vec3(-center_point.position.x, center_point.position.y, 0.0f));
        trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
        glViewport(1080, 290, 85*16, 85*9);
        trans = glm::rotate(trans, GLfloat(180), glm::vec3(0, 0, 1));
        trans = glm::rotate(trans, GLfloat(180), glm::vec3(0, 1, 0));
       
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glLineWidth(3);

        for (auto feature_iter : map_features)
        {
            glBindVertexArray(VAO1);
            glBindBuffer(GL_ARRAY_BUFFER, VBO1);
            std::vector<GLfloat> v;
            v.clear();
            for (auto i : feature_iter)
            {
                v.push_back(GLfloat(i.position.x));
                v.push_back(GLfloat(i.position.y));
                v.push_back(GLfloat(0));
            }
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * v.size(), v.data(), GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            glPointSize(5.0f);
            glBindVertexArray(VAO1);
            glDrawArrays(GL_LINE_STRIP, 0, feature_iter.size());
            glBindVertexArray(0);
        }


        draw_zone_of_control();
        
        glViewport(0, 0, 2560, 1440);
        // Clean up
        return 0;
    }
}
void Map::calculate_zone_of_control()
{
    shape.clear();
    int num_segments = 150;
    float radius = 10;
    long double angle = 2.0f * M_PI / num_segments;
    glPointSize(5.0f);
    Line t;
    std::vector<GLfloat> intersection_shape;
    std::vector<forbidden_zone> intersection_shapes;
    forbidden_zone f;
    bool flag = false;
    for (int i = 0; i < (num_segments + 2) * 3; i += 3) {

        glm::vec2 intersection;

        double current_angle = angle * (i / 3 - 1);
        auto prev = t.end;

        t.start = glm::vec2(0 - x, 0 + y);
        t.end.x = radius * cos(current_angle) + 0 - x;
        t.end.y = radius * sin(current_angle) - 0 + y;

        if (prev.x == 0)
            prev = t.end;

        Line pr;
        pr.start = prev;
        pr.end = t.end;


        for (int i = 0; i < lines.size(); i++)
        {
            //   if (glm::distance(t.start, b.start) < radius || glm::distance(t.start, b.end) < radius)
            {
                intersection = findIntersection(&lines[i].start, &lines[i].end, &pr.start, &pr.end);
                if (!(intersection.x == 0 && intersection.y == 0))
                {
                    f.intersection_shape.push_back(intersection.x);
                    f.intersection_shape.push_back(intersection.y);
                    f.intersection_shape.push_back(0);

                    if (flag == false)
                        f.s_angle = angleBetweenLineAndAxis(t.start, glm::vec2(intersection.x, intersection.y));
                    else
                    {
                        f.b_angle = angleBetweenLineAndAxis(t.start, glm::vec2(intersection.x, intersection.y));
                    }
                    int c = i;
                    while (glm::distance(t.start, lines[c].start) < radius)
                    {
                        //  draw_point(lines[c].start.x, lines[c].start.y);
                        f.intersection_shape.push_back(lines[c].start.x);
                        f.intersection_shape.push_back(lines[c].start.y);
                        f.intersection_shape.push_back(0);

                        c++;
                        if (c > lines.size() - 1)
                            break;
                    }
                    c = i;
                    while (glm::distance(t.start, lines[c].start) < radius)
                    {
                        //  draw_point(lines[c].start.x, lines[c].start.y);
                        f.intersection_shape.push_back(lines[c].start.x);
                        f.intersection_shape.push_back(lines[c].start.y);
                        f.intersection_shape.push_back(0);
                        c--;
                        if (c < 0)
                            break;
                    }
                    if (flag == true)
                        intersection_shapes.push_back(f);

                    flag = !flag;

                }
            }
        }

    }

    double current_angle = 0;
 
    int intersect_number = 0;
    while (current_angle < 2 * M_PI)
    {
        current_angle += 0.01;
        shape.push_back(radius * cos(current_angle) + 0 - x);
        shape.push_back(radius * sin(current_angle) - 0 + y);
        shape.push_back(0);
    }

    for (auto ic : intersection_shapes)
        for (int i = 0; i < ic.intersection_shape.size() - 3; i += 3)
        {

            shape.push_back(ic.intersection_shape[i]);
            shape.push_back(ic.intersection_shape[i + 1]);
            shape.push_back(ic.intersection_shape[i + 2]);
        }
}
void Map::draw_zone_of_control()
{
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(500, 500, 0.0f));
    trans = glm::scale(trans, glm::vec3(size, size, size));
  //  trans = glm::translate(trans, glm::vec3(center_point.position.x, -center_point.position.y, 0.0f));
    trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
    trans = glm::rotate(trans, GLfloat(180), glm::vec3(0, 0, 1));
    trans = glm::rotate(trans, GLfloat(180), glm::vec3(0, 1, 0));
    GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    GLuint vao, vbo;
    if (previous_x != x || previous_y != y)
        calculate_zone_of_control();
    previous_x = x;
    previous_y = y;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, shape.size() * sizeof(GLfloat), shape.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao);
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 1, 0, 0, 1);
    glDrawArrays(GL_POINTS, 0, shape.size()/3);
  
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

}