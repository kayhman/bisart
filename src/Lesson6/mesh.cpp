#include "mesh.h"
#include <GL/glut.h>    // Header File For The GLUT Library
#include <QtOpenGL/QtOpenGL>
#include "parser.h"
#include <iostream>
#include <sstream>
#include <QTreeWidgetItem>



Mesh::Mesh() : position(0,0,0),
    item(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("hop")))),
    name(""),
    parent(NULL)
{
    this->item->setData(0, Qt::UserRole, QVariant::fromValue<Mesh*>(this));
}

Mesh::~Mesh()
{

}

QTreeWidgetItem* Mesh::getItem()
{
  return item;
}

Mesh* Mesh::createMeshFromObj(const std::string& file, const std::string& name)
{
    Mesh* m = new Mesh();
    m->name = name;
    ObjParser::load(file, m->getVertices(), m->getIndices());
    return m;
}


void Mesh::addChild(const std::string& name, Mesh* mesh)
{
    mesh->parent = this;
    children[name] = mesh;
    mesh->getItem()->setText(0, name.c_str());
    mesh->getItem()->setFlags(mesh->getItem()->flags() | Qt::ItemIsEditable);
    item->addChild(mesh->getItem());
}

void Mesh::removeChild(const std::string& name)
{
    auto child = this->children.find(name);
    if(child != this->children.end())
    {
        //delete child->second;
        this->children.erase(name);
    }
}


std::string Mesh::getUniqueName()
{
    Mesh* par = parent;
    std::vector<Mesh*> parents;
    while(par)
    {
        parents.push_back(par);
        par = par->parent;
    }
    std::stringstream ss;
    for(auto it = parents.rbegin() ; it != parents.rend() ; it++)
    {
        ss << (*it)->name << '/';
    }
    ss << this->name;

    return ss.str();
}

void Mesh::render()
{
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

const std::string& Mesh::getName()
{
    return this->name;
}


Mesh* Mesh::getParent() const
{
    return this->parent;
}
