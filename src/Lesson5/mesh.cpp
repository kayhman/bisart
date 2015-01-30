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


void Mesh::addChild(const std::string& name, Mesh* mesh)
{
    children[name] = mesh;
}


void Mesh::render()
{
    std::cout << "bunny pos " << position.x() << std::endl;
    glPushMatrix();
    glTranslatef(position.x(), position.y(), position.z());


    glBegin(GL_TRIANGLES);                      // Drawing Using indices
    std::vector<QVector3D> normals;
    for(int tIdx = 0 ; tIdx < (int)indices.size() ; tIdx+=3)
    {
        int A = indices[tIdx];
        int B = indices[tIdx+1];
        int C = indices[tIdx+2];

        QVector3D AB(vertices[3*B+0]-vertices[3*A+0], vertices[3*B+1]-vertices[3*A+1], vertices[3*B+2]-vertices[3*A+2]);
        QVector3D AC(vertices[3*C+0]-vertices[3*A+0], vertices[3*C+1]-vertices[3*A+1], vertices[3*C+2]-vertices[3*A+2]);
        QVector3D n = QVector3D::crossProduct(AB,AC);
        n.normalize();
//        normals.push_back(n);

        glNormal3f(n.x(), n.y(),n.z());
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(vertices[3*A+0], vertices[3*A+1], vertices[3*A+2]);
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(vertices[3*B+0], vertices[3*B+1], vertices[3*B+2]);
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(vertices[3*C+0], vertices[3*C+1], vertices[3*C+2]);

        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(vertices[3*A+0], vertices[3*A+1], vertices[3*A+2]);
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(vertices[3*C+0], vertices[3*C+1], vertices[3*C+2]);
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(vertices[3*B+0], vertices[3*B+1], vertices[3*B+2]);

    }
    glEnd();

    for(auto mIt = children.begin() ; mIt != children.end() ; mIt++)
    {
        mIt->second->render();
    }
    glPopMatrix();

    return;

    //glBegin(GL_TRIANGLES);                      // Drawing Using indices
    //glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    //glNormalPointer(GL_FLOAT, 3 * sizeof(GLfloat), normals.data());
    glVertexPointer(3, GL_FLOAT, 0, this->vertices.data());


      //glScalef(0.05f, 0.05f, 0.05f);
      //glColor3f(1,1,1);

      glDrawElements(GL_TRIANGLES, this->indices.size()/3, GL_INT, this->indices.data());

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_NORMAL_ARRAY);
    glEnd();
}

std::vector<GLint>& Mesh::getIndices()
{
    return indices;
}
std::vector<GLfloat>& Mesh::getVertices()
{
    return vertices;
}

QVector3D& Mesh::getPosition()
{
    return position;
}
