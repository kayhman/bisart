#pragma once

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>


class GlSceneRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GlSceneRenderer() : m_t(0), m_program(0) { }
    ~GlSceneRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }

public slots:
    void paint();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *m_program;
};
