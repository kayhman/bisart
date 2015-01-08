#pragma once

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>


class GlSceneRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GlSceneRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void resize();

public slots:
    void paint();

public:
   void paint2();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram* m_program;
};
