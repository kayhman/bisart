//#include <QtDeclarative/QDeclarativeExtensionPlugin>
//#include <QtDeclarative/qdeclarative.h>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QDebug>
 
class MyPushButton : public QGraphicsProxyWidget
 {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
 
public:
    MyPushButton(QGraphicsItem* parent = 0);
    QString text() const;
    void setText(const QString& text);
 
Q_SIGNALS:
    void clicked(bool);
    void textChanged();
 
private:
    QPushButton *widget;
};
  
//#include "qwidgets.moc"
 
//Q_EXPORT_PLUGIN2(qmlqwidgetsplugin, QWidgetsPlugin);
