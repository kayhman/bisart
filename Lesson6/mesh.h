#ifndef MESH_H
#define MESH_H
#include <QVector3D>
#include <QtOpenGL/QtOpenGL>

#include <map>
class QTreeWidgetItem;

class Mesh
{
private:
    std::vector<GLint> indices;
    std::vector<float> vertices;
    QVector3D position;
    std::map<std::string, Mesh*> children;
    Mesh* parent;
    QTreeWidgetItem* item;
    std::string name;

public:
    Mesh();
    ~Mesh();
    QTreeWidgetItem* getItem();
    static Mesh* createMeshFromObj(const std::string& file, const std::string& name);
    void render();
    std::string getUniqueName();

    void addChild(const std::string& name, Mesh* mesh);
    void removeChild(const std::string& name);
    std::vector<GLint>& getIndices();
    std::vector<GLfloat>& getVertices();
    QVector3D& getPosition();
    const std::string& getName();
    Mesh* getParent() const;

};

 Q_DECLARE_METATYPE(Mesh*)

#endif // MESH_H
