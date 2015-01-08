#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>
//#include <QGuiApplication>


#include "glScene.h"
#include "glWindow.h"
#include "button.h"


int main(int argc, char *argv[])
{
QApplication app(argc, argv);

qmlRegisterType<GlScene>("IsartOpenGL", 1, 0, "GlScene");
qmlRegisterType<MyPushButton>("MyPushButton", 2, 0, "PushButton");
//qmlRegisterType<GLWindow>("IsartOpenGL", 1, 0, "GlScene");

  
  //QQmlApplicationEngine engine;
  //engine.load("main.qml");

  QQuickView view;
  QUrl source = QUrl::fromLocalFile("mainGl.qml");
  view.setSource(source);
  view.show();
  
  return app.exec();
}


int main2(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    GLWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}
