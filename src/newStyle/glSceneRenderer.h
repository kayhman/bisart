#pragma once

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QWindow>

class GlSceneRenderer : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GlSceneRenderer();
    void initializeGL();
    
    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void resize();

public slots:
    void paint();
virtual void render();
//void renderLater();
public:
   void paint2();
   void paint3();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram* m_program;
    QOpenGLContext* m_context;
};
