#pragma once

#include <QtQuick/QQuickItem>

class GlSceneRenderer; //Forward declaration -> compilation perfomance

class GlScene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    GlScene();

    qreal t() const { return m_t; }
    void setT(qreal t);

signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    qreal m_t;
    GlSceneRenderer *m_renderer;
};
