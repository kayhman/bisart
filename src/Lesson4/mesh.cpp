#include "mesh.h"
#include <GL/glut.h>    // Header File For The GLUT Library
#include <QtOpenGL/QtOpenGL>
#include "parser.h"
#include <iostream>
Mesh::Mesh() : position(0,0,0)
{

}

Mesh::~Mesh()
{

}

Mesh* Mesh::createMeshFromObj(const std::string& file )
{
    Mesh* m = new Mesh();
    ObjParser::load(file, m->getVertices(), m->getIndices());
    return m;
}


void Mesh::render()
{
    glTranslatef(position.x(), position.y(), position.z());
    std::cout << "bunny pos " << position.x() << std::endl;
    glBegin(GL_TRIANGLES);                      // Drawing Using indices
    for(int tIdx = 0 ; tIdx < indices.size() ; tIdx+=3)
    {
        int A = indices[tIdx];
        int B = indices[tIdx+1];
        int C = indices[tIdx+2];

        QVector3D AB(vertices[3*B+0]-vertices[3*A+0], vertices[3*B+1]-vertices[3*A+1], vertices[3*B+2]-vertices[3*A+2]);
        QVector3D AC(vertices[3*C+0]-vertices[3*A+0], vertices[3*C+1]-vertices[3*A+1], vertices[3*C+2]-vertices[3*A+2]);
        QVector3D n = QVector3D::crossProduct(AB,AC);
        n.normalize();

        glNormal3f(n.x(), n.y(),n.z());
        glVertex3f(vertices[3*A+0], vertices[3*A+1], vertices[3*A+2]);
        glVertex3f(vertices[3*B+0], vertices[3*B+1], vertices[3*B+2]);
        glVertex3f(vertices[3*C+0], vertices[3*C+1], vertices[3*C+2]);

        glVertex3f(vertices[3*A+0], vertices[3*A+1], vertices[3*A+2]);
        glVertex3f(vertices[3*C+0], vertices[3*C+1], vertices[3*C+2]);
        glVertex3f(vertices[3*B+0], vertices[3*B+1], vertices[3*B+2]);

    }
    glEnd();
}
























std::vector<int>& Mesh::getIndices()
{
    return indices;
}
std::vector<float>& Mesh::getVertices()
{
    return vertices;
}

QVector3D& Mesh::getPosition()
{
    return position;
}
