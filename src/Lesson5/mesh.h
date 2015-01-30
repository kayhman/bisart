#ifndef MESH_H
#define MESH_H
#include <QVector3D>
#include <QtOpenGL/QtOpenGL>

#include <map>

class Mesh
{
private:
    std::vector<GLint> indices;
    std::vector<float> vertices;
    QVector3D position;
    std::map<std::string, Mesh*> children;

public:
    Mesh();
    ~Mesh();
    static Mesh* createMeshFromObj(const std::string& file );
    void render();

    void addChild(const std::string& name, Mesh* mesh);
    std::vector<GLint>& getIndices();
    std::vector<GLfloat>& getVertices();
    QVector3D& getPosition();

};

#endif // MESH_H
