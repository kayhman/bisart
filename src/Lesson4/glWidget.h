#pragma once

#include <QtOpenGL/QGLWidget>
#include <map>

class QOpenGLShaderProgram;
class Mesh;
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

public:
    void move(const std::string& id, float x, float y, float z);
    void addMesh(const std::string& name, const std::string& file);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    float m_t;
    int xRot;
    int yRot;
    int zRot;

    float xTrans;
    float yTrans;
    float zTrans;

    std::vector<float> vertices;
    std::vector<int> triangles;
    std::map<std::string, Mesh*> meshes;

    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
    QOpenGLShaderProgram* m_program;
};
