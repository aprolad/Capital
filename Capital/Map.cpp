#include "Map.h"
#include"Header.h"
#include <algorithm>
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
            for (int i = 0; i < poPolygon->getExteriorRing()->getNumPoints(); i++)
            {
                
                v = transformCoordinates(poPolygon->getExteriorRing()->getX(i), poPolygon->getExteriorRing()->getY(i));
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
    size = 8;
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
        trans = glm::translate(trans, glm::vec3(-center_point.position.x, center_point.position.y, 0.0f));
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
        trans = glm::mat4(1);
        trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
        transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glViewport(0, 0, 2560, 1440);
        // Clean up
        return 0;
    }
}