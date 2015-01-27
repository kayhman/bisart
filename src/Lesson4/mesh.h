#ifndef MESH_H
#define MESH_H
#include <QVector3D>

class Mesh
{
private:
    std::vector<int> indices;
    std::vector<float> vertices;
    QVector3D position;

public:
    Mesh();
    ~Mesh();
    static Mesh* createMeshFromObj(const std::string& file );
    void render();

    std::vector<int>& getIndices();
    std::vector<float>& getVertices();
    QVector3D& getPosition();

};

#endif // MESH_H
