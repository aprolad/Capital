#include "Map.h"
#include"Header.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "Utility_graphic_functions.h"
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
        // std::cout << b << std::endl;
        if (angle > a.s_angle && angle < a.b_angle)
            return true;
    }
    return false;
}
// Find intersection point of two line segments in 2D space
glm::vec2 findIntersection(glm::vec2 p1, glm::vec2 p2, glm::vec2 q1, glm::vec2 q2) {
    glm::vec2 intersection(GLfloat(0), GLfloat(0));
    long double det, t, u;
    const long double EPSILON = 0.00000001f;

    det = (q2.y - q1.y) * (p2.x - p1.x) - (q2.x - q1.x) * (p2.y - p1.y);
    if (det == 0) {
        return intersection; // Lines are parallel, no intersection
    }

    t = ((q2.x - q1.x) * (p1.y - q1.y) - (q2.y - q1.y) * (p1.x - q1.x)) / det;
    u = ((p2.x - p1.x) * (p1.y - q1.y) - (p2.y - p1.y) * (p1.x - q1.x)) / det;

    if (t >= -EPSILON && t <= 1 + EPSILON && u >= -EPSILON && u <= 1 + EPSILON) {
        intersection.x = p1.x + t * (p2.x - p1.x);
        intersection.y = p1.y + t * (p2.y - p1.y);
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
    std::cout << lines.size() << std::endl;
   // std::cout << map() << std::endl;
    center_point.position.x /= vertex_count;
    center_point.position.y /= vertex_count;
    size = 8;
   // x = 100;
    y = -100;
    OGRFeature::DestroyFeature(poFeature);

}
int Map::draw()
{
    {
        glUseProgram(shaderProgram);
        glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans;
        trans = glm::translate(trans, glm::vec3(500, 500, 0.0f));
        trans = glm::scale(trans, glm::vec3(size, size, size));
        //trans = glm::translate(trans, glm::vec3(-center_point.position.x, center_point.position.y, 0.0f));
        trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
        glViewport(1080, 070, 2560, 1400);
        trans = glm::rotate(trans, GLfloat(180), glm::vec3(0, 0, 1));
        trans = glm::rotate(trans, GLfloat(180), glm::vec3(0, 1, 0));
        GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        

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
        trans = glm::mat4(1);
        trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
        transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glViewport(0, 0, 2560, 1440);
        // Clean up
        return 0;
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
    std::vector<GLfloat> vert;
    vert.resize(0);
    GLuint vao, vbo;
    int num_segments = 150;
    float radius = 10;
    long double angle = 2.0f * M_PI / num_segments;
    glPointSize(5.0f);
    GLfloat* vertices1 = new GLfloat[(num_segments + 5) * 3];
    Line t;
    std::vector<GLfloat> intersection_shape;
    std::vector<forbidden_zone> intersection_shapes;
    std::vector<double> forbidden_angle;
    forbidden_zone f;
    bool flag = false;
    double a1=0, a2=0, b=0;
    for (int i = 0; i < (num_segments + 2) * 3; i += 3) {

        glm::vec2 base;
        glm::vec2 intersection;

        double current_angle = angle * (i / 3 - 1);
       // std::cout << current_angle << " " << b<<std::endl;
      
        vertices1[i] = radius * cos(angle * (i / 3 - 1)) + 00 - x;
        vertices1[i + 1] = radius * sin(angle * (i / 3 - 1)) - 000 + y;
        vertices1[i + 2] = 0;
        
        auto prev = t.end;
        prev.x = t.end.x;
        prev.y = t.end.y;
        t.start = glm::vec2(00 - x, -000 + y);
        t.end.x = vertices1[i];
        t.end.y = vertices1[i + 1];
        if (prev.x == 0)
            prev = t.end;
        Line pr;
        pr.start = prev;
        pr.end = t.end;

       // if (pr.start.x != 0)
      //  draw_line(pr.start.x, pr.start.y, pr.end.x, pr.end.y);
        for (int i = 0; i<lines.size(); i++)
        {
         //   if (glm::distance(t.start, b.start) < radius || glm::distance(t.start, b.end) < radius)
            {
                intersection = findIntersection(lines[i].start, lines[i].end, pr.start, pr.end);
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


                    forbidden_angle.push_back(angleBetweenLineAndAxis(t.start, glm::vec2(intersection.x, intersection.y)));

                    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 1, 0, 0, 1);
                    draw_point(intersection.x, intersection.y);
                    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 0, 1);
                    int c = i;
                    
                    while (glm::distance(t.start, lines[c].start) < radius)
                    {      
                      //  draw_point(lines[c].start.x, lines[c].start.y);
                        f.intersection_shape.push_back(lines[c].start.x);
                        f.intersection_shape.push_back(lines[c].start.y);
                        f.intersection_shape.push_back(0);

                        a1 = angleBetweenLineAndAxis(t.start, glm::vec2(lines[c].start));
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
    std::vector<GLfloat> shape;
    int intersect_number = 0;
    while (current_angle < 2*M_PI)
    {

        current_angle += 0.01;
        if (!is_forbidden(current_angle, intersection_shapes))
        {
            shape.push_back(radius * cos(current_angle) + 0 - x);
            shape.push_back(radius * sin(current_angle) - 0 + y);
            shape.push_back(0);
        }
        else
        {
            glm::vec2 cur;
            //std::cout << "ANGLES " <<intersect_number << std::endl;
            if (shape.size() > 2)
                cur = glm::vec2(shape[shape.size() - 3], shape[shape.size() - 2]);
            else
                cur = glm::vec2(0, 0);
            if (glm::distance(cur, intersection_shapes[intersect_number].first_point()) > glm::distance(cur, intersection_shapes[intersect_number].last_point()))
                std::cout << "first" << std::endl;
            else
                std::cout << "second" << std::endl;
            intersection_shapes[intersect_number].reverse();
            // shape.insert(shape.end(), intersection_shapes[intersect_number].intersection_shape.begin(), intersection_shapes[intersect_number].intersection_shape.end());
            for (int i = 0; i < intersection_shapes[intersect_number].intersection_shape.size()-3; i+=3)
            {

                shape.push_back(intersection_shapes[intersect_number].intersection_shape[i]);
                shape.push_back(intersection_shapes[intersect_number].intersection_shape[i + 1]);
                shape.push_back(intersection_shapes[intersect_number].intersection_shape[i + 2]);
            }
            current_angle = intersection_shapes[intersect_number].b_angle;

            intersect_number++;
        }
    }
  
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, shape.size() * sizeof(GLfloat), shape.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao);
  //  std::cout << shape.size()<<std::endl;
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 1, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, shape.size()/3);
  
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    delete[] vertices1;
}