#include "Map.h"
#include"Header.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "Utility_graphic_functions.h"
#include <glm/glm.hpp>

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
                lines.push_back(t);
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
    size = 1;
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

    GLuint vao, vbo;
    int num_segments = 150;
    float radius = 10;
    long double angle = 2.0f * M_PI / num_segments;
    glPointSize(5.0f);
    GLfloat* vertices1 = new GLfloat[(num_segments + 2) * 3];

    for (int i = 0; i < (num_segments + 2) * 3; i += 3) {
        Line t;
        glm::vec2 base;
        glm::vec2 intersection;



        vertices1[i] = radius * cos(angle * (i / 3 - 1))+00-x;
        vertices1[i + 1] = radius * sin(angle * (i / 3 - 1)) - 000 + y;
        vertices1[i + 2] = 0;

        t.start = glm::vec2(00-x,-000+y );
        t.end.x = vertices1[i];
        t.end.y = vertices1[i + 1];

        draw_line(t.start.x, t.start.y, t.end.x, t.end.y);
        for (auto b : lines)
        {
            if (glm::distance(t.end, b.start) < radius || glm::distance(t.end, b.end) < radius)
            {
                intersection = findIntersection(b.start, b.end, t.start, t.end);
                if (!(intersection.x == 0 && intersection.y == 0))
                {
                    //      std::cout << intersection.x << std::endl;
                    draw_point(intersection.x, intersection.y);
                          vertices1[i] = intersection.x;
                            vertices1[i+1] = intersection.y;
                            break;
                }
            }
        }
 
  

    }

 


 

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (num_segments + 2) * 3 * sizeof(GLfloat), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments + 2);
    //draw_line(t.start.x, t.start.y, t.end.x, t.end.y);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    delete[] vertices1;
}