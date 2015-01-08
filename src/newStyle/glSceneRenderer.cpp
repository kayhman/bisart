#include "glSceneRenderer.h"
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <iostream>


GlSceneRenderer::GlSceneRenderer() : m_t(0) {
  return;
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
					   "    coords.xy =  vertices.xy;"
                                           "}");
        m_program->bindAttributeLocation("vertices", 0);
        m_program->link();

    }
    m_program->bind();

    m_program->enableAttributeArray(0);

    float values[] = {
      -1, -0.8, -10*m_t,
      1, -1, -1,
      -1, 1, -1,
        1, 1, -1
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
