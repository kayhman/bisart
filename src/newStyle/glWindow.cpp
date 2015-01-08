#include "glWindow.h"

#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include <GL/glut.h>    // Header File For The GLUT Library 
#include <iostream>

void GLWindow::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    //    if (window())
    //        window()->update();
}

GLWindow::GLWindow(QWindow *parent)
    : QWindow(parent)
    , m_update_pending(false)
    , m_animating(true)
    , m_context(0)
    , m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

GLWindow::~GLWindow()
{
    delete m_device;
}

void GLWindow::nativePainting()
{
    static const float vertexPositions[] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.0f,  0.8f, 0.0f
    };
 
    static const float vertexColors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
 
    QOpenGLBuffer vertexPositionBuffer(QOpenGLBuffer::VertexBuffer);
    vertexPositionBuffer.create();
    vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexPositionBuffer.bind();
    vertexPositionBuffer.allocate(vertexPositions, 9 * sizeof(float));
 
    QOpenGLBuffer vertexColorBuffer(QOpenGLBuffer::VertexBuffer);
    vertexColorBuffer.create();
    vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexColorBuffer.bind();
    vertexColorBuffer.allocate(vertexColors, 9 * sizeof(float));
 
    QOpenGLShaderProgram program;
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                    "#version 330\n"
                                    "in vec3 position;\n"
                                    "in vec3 color;\n"
                                    "out vec3 fragColor;\n"
                                    "void main() {\n"
                                    "    fragColor = color;\n"
                                    "    gl_Position = vec4(position, 1.0);\n"
                                    "}\n"
                                    );
    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                    "#version 330\n"
                                    "in vec3 fragColor;\n"
                                    "out vec4 color;\n"
                                    "void main() {\n"
                                    "    color = vec4(fragColor, 1.0);\n"
                                    "}\n"
                                    );
    program.link();
    program.bind();
 
    vertexPositionBuffer.bind();
    program.enableAttributeArray("position");
    program.setAttributeBuffer("position", GL_FLOAT, 0, 3);
 
    vertexColorBuffer.bind();
    program.enableAttributeArray("color");
    program.setAttributeBuffer("color", GL_FLOAT, 0, 3);
 
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLWindow::render(QPainter *painter)
{
  painter->beginNativePainting();
  this->nativePainting();

#ifdef toto
  std::cout << "rendering" << std::endl;
  const int width = this->width();
  const int height = this->height();
  int side = qMin(width, height);
  


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(5.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
    
  
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_MULTISAMPLE);
  static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  
  //glClearColor(1, 0, 0, 0);
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0, 0.0, -4.0);



  //m_context->makeCurrent(this);
  //glActiveTexture(GL_TEXTURE1);
  //glBindTexture(GL_TEXTURE_2D, GL_TEXTURE1);
  
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0, 0.0, -4.0);
  
  GLfloat twoTri[] = {
    0.0f, 1.0f, 0.0f,              // Top
    -1.0f,-1.0f, 0.0f,              // Bottom Left
    1.0f,-1.0f, 0.0f,              // Bottom Right
    
    0.0f, 1.0f, 0.0f,              // Top
    1.0f,-1.0f, 0.0f,              // Bottom Right
    -1.0f,-1.0f, 0.0f,              // Bottom Left
  };
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, twoTri);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
  glDisableClientState(GL_VERTEX_ARRAY);
  
  //m_context->swapBuffers(this);
  //m_context->doneCurrent();
  
  /*
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
  */
#endif
    painter->endNativePainting();
}

void GLWindow::initialize()
{
}

void GLWindow::render()
{
}

void GLWindow::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool GLWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void GLWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void GLWindow::renderNow()
{
  std::cout << "rendering now" << std::endl;
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}

void GLWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}
