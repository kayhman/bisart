#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  //QQmlApplicationEngine engine;
  //engine.load("main.qml");

  QQuickView* view = new QQuickView();
  QUrl source = QUrl::fromLocalFile("main.qml");
  view->setSource(source);
  view->show();
  
  return app.exec();
}
