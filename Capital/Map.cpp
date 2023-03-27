#include "Map.h"
Vertex transformCoordinates(double longitude, double latitude)
{
    Vertex t;
    t.position.x = (longitude + 180.0) * (1000.0 / 360.0);
    t.position.y = (1 - log(tan(latitude * M_PI / 180.0) + 1 / cos(latitude * M_PI / 180.0)) / M_PI) * 500.0;
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
  //  oDstSRS.SetMercator(0, 0, 1, 0, 0);
   // OGRCoordinateTransformation* poCT = OGRCreateCoordinateTransformation(&oSrcSRS, &oDstSRS);
    // Loop through all the features in the layer
    OGRFeature* poFeature = NULL;
    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != NULL)
    {
        // Get the geometry of the feature
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();

        // Transform the geometry to Mercator coordinates
      //  poGeometry->transform(poCT);

        // Extract the vertices from the geometry and add them to a list of vertices

        if (poGeometry->getGeometryType() == wkbPolygon)
        {
            OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
            for (int i = 0; i < poPolygon->getExteriorRing()->getNumPoints(); i++)
            {
                Vertex v;
                v = transformCoordinates(poPolygon->getExteriorRing()->getX(i), poPolygon->getExteriorRing()->getY(i));
               // v.position.x = poPolygon->getExteriorRing()->getX(i);
               // v.position.y = poPolygon->getExteriorRing()->getY(i);
               // std::cout << v.position.x<<std::endl;
                vertices.push_back(v);
            }
        }
    }
    OGRFeature::DestroyFeature(poFeature);
}
int Map::draw()
{
    {
        glUseProgram(shaderProgram);
        glm::vec4 vec(0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans;
        trans = glm::translate(trans, glm::vec3(600, 350, 0.0f));
        GLuint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
       // GLfloat* vertices = new GLfloat[sizing * 3 + 3];   

        glBindVertexArray(VAO1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        std::vector<GLfloat> v;
        v.resize(0);
        for (auto i : vertices)
        {
            v.push_back(GLfloat(i.position.x));
            v.push_back(GLfloat(i.position.y));
            v.push_back(0);
           // std::cout << vertices.size();
        }

        GLfloat* a = &v[0];
        for (int i =0; i<1000; i++)
        {
            
         //    std::cout << a[i]<<std::endl;
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size() * 3, a, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glBindVertexArray(VAO1);
        glDrawArrays(GL_POINTS, 0, vertices.size() * 3);
        glBindVertexArray(0);

        trans = glm::mat4(1);
        trans = glm::translate(trans, glm::vec3(0, 0, 0.0f));
        transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // Clean up
        return 0;
    }
}