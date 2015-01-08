#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>

#include "glScene.h"


int main(int argc, char *argv[])
{
QApplication app(argc, argv);

qmlRegisterType<GlScene>("IsartOpenGL", 1, 0, "GlScene");

  QQuickView view;
  QUrl source = QUrl::fromLocalFile("mainGl.qml");
  view.setSource(source);
  view.show();
  
  return app.exec();
}
