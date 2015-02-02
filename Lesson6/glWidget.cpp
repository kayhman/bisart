#include <QtWidgets>
#include <QtOpenGL/QtOpenGL>

#include <math.h>
#include <iostream>
#include "glWidget.h"

#include <GL/glut.h>    // Header File For The GLUT Library 
#include <iostream>
#include "parser.h"

#include <QVector3D>
#include "mesh.h"
#include <QWidgetItem>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
      m_t(0.),
    m_program(NULL),
    treeWidget(NULL),
    xTrans(0),yTrans(0),zTrans(0)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

}

void GLWidget::setTreeWidget(QTreeWidget* tree)
{
    this->treeWidget = tree;
}

void GLWidget::remove()
{
    QObject* sender = QObject::sender();
    QAction* action = qobject_cast<QAction*>(sender);
    if(action)
    {
        Mesh* m = action->data().value<Mesh*>();
        if(m->getParent())
            m->getParent()->removeChild(m->getName());
        std::cout << "remove " << dynamic_cast<Mesh*>(m)->getUniqueName() << std::endl;
    }

}

void GLWidget::showMenu(const QPoint& globalPos)
{
     QTreeWidgetItem* item =  this->treeWidget->itemAt(globalPos);
     QMenu menu;
     std::cout << "menu " << globalPos.x() << std::endl;

     QAction* remove = new QAction(tr("Remove mesh"), this);
     remove->setStatusTip(tr("Remove mesh"));


     remove->setData(QVariant::fromValue<Mesh*>(item->data(0, Qt::UserRole).value<Mesh*>() ));
     connect(remove, SIGNAL(triggered()), this, SLOT(remove()));

     menu.addAction(remove);

     menu.addAction("Add child");

     menu.exec(this->treeWidget->viewport()->mapToGlobal(globalPos));
}


Mesh* GLWidget::addMesh(const std::string& name, const std::string& file, Mesh* parent)
{
    Mesh* m = Mesh::createMeshFromObj(file, name);
    if(parent)
    {
        parent->addChild(name, m);
    }
    else
    {
        meshes[name] = m;
        if(this->treeWidget && m != NULL)
        {
            m->getItem()->setText(0, name.c_str());
            this->treeWidget->addTopLevelItem(m->getItem());
        }
    }
    this->updateGL();
    return m;
}

GLWidget::~GLWidget()
{
    for(auto it = meshes.begin() ; it != meshes.end(); it++)
        delete it->second;
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::move(const std::string& id, float x, float y, float z)
{
    std::cout << "move " << this->meshes[id] << std::endl;
    this->meshes[id]->getPosition().setX(x);
    this->meshes[id]->getPosition().setY(y);
    this->meshes[id]->getPosition().setZ(z);
    this->updateGL();
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::initializeGL()
{
    qglClearColor(qtPurple.dark());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0.0, -4.0);

    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    glTranslatef(xTrans, yTrans, zTrans);

    glBegin(GL_TRIANGLES);                      // Drawing Using Triangles
    for(int tIdx = 0 ; tIdx < triangles.size() ; tIdx+=3)
    {
        int A = triangles[tIdx];
        int B = triangles[tIdx+1];
        int C = triangles[tIdx+2];

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
    for(auto mIt = meshes.begin() ; mIt != meshes.end() ; mIt++)
        mIt->second->render();


    /*
    glVertex3f( 0.0f, 1.0f, 0.0f);              // Top
    glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
    glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right

    //back side
    glVertex3f( 0.0f, 1.0f, 0.0f);              // Top
    glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right
    glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
    */
    glEnd();

}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
