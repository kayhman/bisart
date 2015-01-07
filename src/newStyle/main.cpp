#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>
//#include <QGuiApplication>


#include "glScene.h"


int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  qmlRegisterType<GlScene>("IsartOpenGL", 1, 0, "GlScene");

  
  //QQmlApplicationEngine engine;
  //engine.load("main.qml");

  QQuickView view;
  QUrl source = QUrl::fromLocalFile("mainGl.qml");
  view.setSource(source);
  view.show();
  
  return app.exec();
}
