﻿#include "Map.h"
#include"Header.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/glm.hpp>
#include "gdal_priv.h"
#include "ogrsf_frmts.h"
#include "Visualization.h"
#include "misc/earcut.hpp"
#include <array>
#include <math.h>
extern Visualization visualization;
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
    double s_a, b_a;
    double angle_size;
    std::vector<glm::vec3> points;
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
	static bool compareByField(const forbidden_zone& obj1, const forbidden_zone& obj2) {
    return obj1.s_a < obj2.s_a;
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
bool counter_clock(Line l1, Line l2)
{
	glm::vec2 v1 = glm::normalize(l1.dir_vector());
    glm::vec2 v2 = glm::normalize(l2.dir_vector());
    glm::vec3 crossProduct = glm::cross(glm::vec3(v1, 0.0f), glm::vec3(v2, 0.0f));
    if (crossProduct.z > 0)
        return true;
    else
        return false;
}
float calculateAngleBetweenLines(Line& line1, Line& line2) {
    // Normalize the vectors

    glm::vec2 v1 = glm::normalize(line1.dir_vector());
    glm::vec2 v2 = glm::normalize(line2.dir_vector());
    glm::vec3 crossProduct = glm::cross(glm::vec3(v1, 0.0f), glm::vec3(v2, 0.0f));

    // Calculate the signed angle in radians
    float angleInRadians = std::atan2(v2.y, v2.x) - std::atan2(v1.y, v1.x);
	if (std::isnan(angleInRadians)) {
        return 0.0f; // Return 0 degrees if the angle is NaN
    }
    if (angleInRadians < 0)
        angleInRadians += M_PI * 2;

    return angleInRadians;
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

const double kEarthRadius = 6371.0; // Earth's radius in kilometers



double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = degreesToRadians(lat2 - lat1);
    double dLon = degreesToRadians(lon2 - lon1);
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(degreesToRadians(lat1))
        * cos(degreesToRadians(lat2)) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    double d = kEarthRadius * c;
    return d;
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
    x_slot = visualization.window_resolution.x / 50;
    y_slot = visualization.window_resolution.y / 50;

    GDALAllRegister();
    OGRRegisterAll();
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &IBO);
    // Open Shapefile
    GDALDataset* poDS = (GDALDataset*)GDALOpenEx("Graphics/map1.shp", GDAL_OF_VECTOR | GDAL_OF_READONLY, NULL, NULL, NULL);

   
    if (poDS == NULL) {
        std::cerr << "Failed to open Shapefile" << std::endl;
        return -1;
    }

    // Get the first layer in the Shapefile
    OGRLayer* poLayer = poDS->GetLayer(0);

    // Set up a projection from geographic coordinates to Mercator coordinates
    OGRSpatialReference oSrcSRS, oDstSRS;




    const char* projection = poDS->GetProjectionRef();

    // Create a new spatial reference object and set the projection
    OGRSpatialReference* spatialRef = new OGRSpatialReference();
    spatialRef->SetFromUserInput(projection);

    // Get the extent of the shapefile
    OGRLayer* layer = poDS->GetLayer(0);
    OGREnvelope envelope;
    layer->GetExtent(&envelope);

    // Calculate the size of each pixel
    double pixelWidth = (envelope.MaxX - envelope.MinX) / 500;
    double pixelHeight = (envelope.MaxY - envelope.MinY) / 500;



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
            //printf("Processing polygon with %d rings\n", poPolygon->getExteriorRing()->getNumPoints() + 1);
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
    std::cout << "Loaded map polygons" << std::endl;

    center_point.position.x /= vertex_count;
    center_point.position.y /= vertex_count;
    size = 21;
    x = 0;
    y = -100;
    OGRFeature::DestroyFeature(poFeature);

}
void Map::draw_map_sizing()
{
    glUseProgram(shaderProgram);
    glm::mat4 trans = glm::mat4(1);
    GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 0, 1);
    draw_rectangle(x_slot * 45, 1190, 75, 25);
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 1, 0, 0, 1);
    draw_line(x_slot * 44, 1190, x_slot * 46, 1190);
    glUniform4f(glGetUniformLocation(shaderProgram, "ourColor"), 0, 0, 0, 1);
    // Calculate sizing of the map based on lattitude 45 degrees
    RenderText(fontShader, std::to_string(int(haversine(45, 0, 45, 36) / size)) + " Km", x_slot * 44, 1175, 0.3, glm::vec3(1.0, 0.0f, 0.0f));
}
int Map::draw()
{
    {
     
        glUseProgram(shaderProgram);
        GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glm::mat4 trans = glm::mat4(1);
        trans = glm::translate(trans, glm::vec3(1000, 500, 0.0f));
        trans = glm::scale(trans, glm::vec3(size, size, size));
        //trans = glm::translate(trans, glm::vec3(-center_point.position.x, center_point.position.y, 0.0f));
        trans = glm::translate(trans, glm::vec3(x, y, 0.0f));

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


       // state_zones[0].draw_zone_of_control();
        state_zones[1].draw_zone_of_control();
        draw_map_sizing();
        previous_x = x;
        previous_y = y;
        return 0;
    }
}
void Map::mouse_callback(int mx, int my)
{
    state_zones[1].mouse_callback(mx, my);
}
void State_zone::mouse_callback(int mx, int my)
{

    double t_x = (mx - 1000) / map->size - map->x + centre_x;
    double t_y = (my - 500) / map->size - map->y + centre_y;
    if (sqrt(pow(t_x, 2) + pow(t_y, 2)) < 10)
        visualization.scene[visualization.choosenScene]->enemy = !visualization.scene[visualization.choosenScene]->enemy;
}

using Point = std::array<double, 2>;
void add_circle_points(std::vector<GLfloat>* shape, std::vector<Point>* polygon,  double start_angle, double end_angle, double radius, double x, double y)
{
    bool over = false;
    if (start_angle > end_angle)
        over = true;
    if (start_angle - end_angle < 0.05)
        return;
    while (start_angle < end_angle || over == true)
    {
        if (start_angle < end_angle)
            over = false;
        double ax = (radius * cos(start_angle) - x);
        double ay = (-radius * sin(start_angle) + y);
        shape->push_back(ax);
		shape->push_back(ay);
		shape->push_back(0);
		polygon->push_back({ax, ay});
        start_angle += 0.003;
        if (start_angle > fmod(start_angle, M_PI * 2))
            end_angle -= 0.01;
        start_angle = fmod(start_angle, M_PI * 2);
        
     //   std::cout << "c";
    }
}
void State_zone::calculate_zone_of_control()
{
    int x = centre_x + map->x;
    int y = centre_y + map->y + 100;
    shape.clear();
    int num_segments = 150;
    float radius = 10;
    long double angle = 2.0f * M_PI / num_segments;
    glPointSize(5.0f);
    Line t;
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


        for (int i = 0; i < map->lines.size(); i++)
        {
            //   if (glm::distance(t.start, b.start) < radius || glm::distance(t.start, b.end) < radius)
            {
                intersection = findIntersection(&map->lines[i].start, &map->lines[i].end, &pr.start, &pr.end);
                if (!(intersection.x == 0 && intersection.y == 0))
                {
     
                    int c = i;
                    while (glm::distance(t.start, map->lines[c].start) < radius)
                    {
                        f.intersection_shape.push_back(map->lines[c].start.x);
                        f.intersection_shape.push_back(map->lines[c].start.y);
                        f.intersection_shape.push_back(0);

                        c++;
                        if (c > map->lines.size() - 1)
                            break;
                    }
                    c = i;
                    while (glm::distance(t.start, map->lines[c].start) < radius)
                    {
                        f.intersection_shape.push_back(map->lines[c].start.x);
                        f.intersection_shape.push_back(map->lines[c].start.y);
                        f.intersection_shape.push_back(0);
                        c--;
                        if (c < 0)
                            break;
                    }
                    if (flag == true)
                    {
                        intersection_shapes.push_back(f);
                        f.intersection_shape.clear();
                    }
                    flag = !flag;

                }
            }
        }

    }



	using Coord = double;
    using N = uint32_t;

    std::vector<std::vector<Point>> polygons;
    std::vector<Point> polygon;
    glm::vec2 base_point = glm::vec2(-x, y);
    glm::vec2 axis_base = glm::vec2(-x + 10, y);
    Line base;

    if (intersection_shapes.size() < 1)
    {
		add_circle_points(&shape, &polygon, 0, PI/2, radius, x, y);
		polygons.push_back(polygon);
		indices = mapbox::earcut<N>(polygons);
        return;
    }
    if (intersection_shapes[0].intersection_shape.size() < 1)
        return;
  //  using std::cout, std::endl;
	base.start = base_point;
    base.end = glm::vec2(intersection_shapes[0].intersection_shape[0], intersection_shapes[0].intersection_shape[1]);
    Line axis = Line(base_point, axis_base);
    double base_angle = calculateAngleBetweenLines(base, axis);


    for (auto& a : intersection_shapes)
    {
        if (a.intersection_shape.size() < 3)
            continue;
        Line s_line = Line(base_point, glm::vec2(a.intersection_shape[0], a.intersection_shape[1]));
		Line e_line = Line(base_point, glm::vec2(a.intersection_shape[a.intersection_shape.size()-3], a.intersection_shape[a.intersection_shape.size()-2]));

        if (counter_clock(s_line, e_line))
            a.reverse();
		s_line = Line(base_point, glm::vec2(a.intersection_shape[0], a.intersection_shape[1]));
		e_line = Line(base_point, glm::vec2(a.intersection_shape[a.intersection_shape.size()-3], a.intersection_shape[a.intersection_shape.size()-2]));
		a.s_a = calculateAngleBetweenLines(s_line, axis);
		a.b_a = calculateAngleBetweenLines(e_line, axis);
        a.angle_size = calculateAngleBetweenLines(e_line, s_line);
        std::cout << "Base angle "<< a.b_a <<std::endl;
		std::cout <<"ANGLE "<< a.angle_size << std::endl;
		std::cout <<"Start ANGLE "<< a.s_a << std::endl;
		std::cout << "||||||||||" << std::endl;
  
    }

	std::sort(intersection_shapes.begin(), intersection_shapes.end(), forbidden_zone::compareByField);
    
    int c = 0;

    for (int is = 0; is < intersection_shapes.size(); is++)
        {
			
            for (int i = 0; i< intersection_shapes[is].intersection_shape.size(); i+=3)
            {
                shape.push_back(intersection_shapes[is].intersection_shape[i]);
                shape.push_back(intersection_shapes[is].intersection_shape[i + 1]);
                shape.push_back(intersection_shapes[is].intersection_shape[i + 2]);
				polygon.push_back({intersection_shapes[is].intersection_shape[i] , intersection_shapes[is].intersection_shape[i + 1]});
            }
            if ((is + 1 < intersection_shapes.size()))
                add_circle_points(&shape, &polygon, intersection_shapes[is].b_a+0.05, intersection_shapes[is+1].s_a-0.05, radius, x, y);

        }
	add_circle_points(&shape, &polygon, intersection_shapes[intersection_shapes.size() - 1].b_a+0.05, intersection_shapes[0].s_a-0.05, radius, x, y);

	polygons.push_back(polygon);
    indices = mapbox::earcut<N>(polygons);


}
void State_zone::draw_zone_of_control()
{
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(1000, 500, 0.0f));
    trans = glm::scale(trans, glm::vec3(*size, *size, *size));

    trans = glm::translate(trans, glm::vec3(map->x, map->y, 0.0f));
    trans = glm::rotate(trans, GLfloat(180), glm::vec3(0, 0, 1));
    trans = glm::rotate(trans, GLfloat(180), glm::vec3(0, 1, 0));
    GLuint transformLoc = glGetUniformLocation(map->shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));



    GLuint vao, vbo;
    if (map->previous_x != map->x || map->previous_y != map->y)
        calculate_zone_of_control();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, shape.size() * sizeof(GLfloat), shape.data(), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &map->IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, map->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao);
    glUniform4f(glGetUniformLocation(map->shaderProgram, "ourColor"), 1, 0, 0, 1);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glUniform4f(glGetUniformLocation(map->shaderProgram, "ourColor"), color.x, color.y, color.z, color[3]);

    glDrawArrays(GL_POINTS, 0, shape.size() / 3);
    glDeleteBuffers(1, &map->IBO);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

}