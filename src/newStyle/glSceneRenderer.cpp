#include "glSceneRenderer.h"
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <iostream>
#include <QSurface>

GlSceneRenderer::GlSceneRenderer() : m_t(0) {
  /*
  setSurfaceType(QSurface::OpenGLSurface);
  create();
  
  // Create an OpenGL context
  m_context = new QOpenGLContext;
  m_context->create();
  initializeOpenGLFunctions();
  */
  // Setup scene and render it
  initializeGL();
  paint();
}

void GlSceneRenderer::initializeGL()
{
  const int width = m_viewportSize.width();
  const int height = m_viewportSize.height();
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
  
  glClearColor(1, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0, 0.0, -4.0);
}

void GlSceneRenderer::render()
{
std::cout <<  "render" << std::endl;
}

/*
void GlSceneRenderer::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
    }*/

void GlSceneRenderer::paint3()
{
if (!isExposed())
  return;

std::cout << "rendering" << std::endl;
m_context->makeCurrent(this);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, GL_TEXTURE1);

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

m_context->swapBuffers(this);
m_context->doneCurrent();
}

void GlSceneRenderer::paint()
{
    if (!m_program) {
        initializeOpenGLFunctions();

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
      -0.8, -0.8, -m_t,
      0.8, -0.8, -m_t,
      -0.8, 0.8, -m_t,
        0.8, 0.8, -m_t
    };
    m_program->setAttributeArray(0, GL_FLOAT, values, 3);
    m_program->setUniformValue("t", (float) m_t);

    //glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    resize();
    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    m_program->disableAttributeArray(0);
    m_program->release();
}

void GlSceneRenderer::paint2()
{
  static bool stop = false;
  if(stop)
    return;
  stop = true;
  std::cout << "m_t : " << m_t << std::endl;
  
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0, 0.0, -4.0);

  //glRotatef(m_t / 16.0, 1.0, 0.0, 0.0);
  //glRotatef(m_t / 16.0, 0.0, 1.0, 0.0);
  //glRotatef(m_t / 16.0, 0.0, 0.0, 1.0);
  //glTranslatef(0, 0.0, m_t);

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

}

void GlSceneRenderer::resize()
{
  const int width = m_viewportSize.width();
  const int height = m_viewportSize.height();
  int side = qMin(width, height);
    
  glViewport((width - side) / 2, (height - side) / 2, side, side);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(5.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
  
  glMatrixMode(GL_MODELVIEW);
}
