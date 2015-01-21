#include <QtWidgets>
#include <QtOpenGL/QtOpenGL>

#include <math.h>
#include <iostream>
#include "glWidget.h"

#include <GL/glut.h>    // Header File For The GLUT Library 
#include <iostream>
#include "parser.h"

#include <QVector3D>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
      m_t(0.),
    m_program(NULL),
    xTrans(0),yTrans(0),zTrans(0)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    ObjParser::load("/tmp/bunny.obj", vertices, triangles);

}

GLWidget::~GLWidget()
{
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
    xTrans = x;
    yTrans = y;
    zTrans = z;
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

void GLWidget::paintShader()
{
    if (!m_program) {
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                           "attribute highp vec4 vertices;"
                                           "varying highp vec3 coords;"
                                           "void main() {"
                                           "    gl_Position = vertices;"
                                           "    float perspective_factor = gl_Position.z * 0.5 + 1.0;"
                                           "    gl_Position.x = gl_Position.x/perspective_factor;"
                                           "    gl_Position.y = gl_Position.y/perspective_factor;"
                       "    coords.xy =  vertices.xy;"
                                           "}");
        m_program->bindAttributeLocation("vertices", 0);
        m_program->link();

    }
    m_program->bind();

    m_program->enableAttributeArray(0);

    float values[] = {
      -0.8f, -0.8f, -m_t,
      0.8f, -0.8f, -m_t,
      -0.8f, 0.8f, -m_t,
        0.8f, 0.8f, -m_t
    };
    m_program->setAttributeArray(0, GL_FLOAT, values, 3);
    m_program->setUniformValue("t", (float) m_t);

    //glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    m_program->disableAttributeArray(0);
    m_program->release();
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
