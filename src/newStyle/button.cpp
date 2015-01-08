#include "button.h"

MyPushButton::MyPushButton(QGraphicsItem* parent)
        : QGraphicsProxyWidget(parent)
     {
        widget = new QPushButton("MyPushButton");
        widget->setAttribute(Qt::WA_NoSystemBackground);
        setWidget(widget);
 
        QObject::connect(widget, SIGNAL(clicked(bool)), this, SIGNAL(clicked(bool)));
    }
 
QString MyPushButton::text() const
     {
        return widget->text();
    }
 
void MyPushButton::setText(const QString& text)
     {
        if (text != widget->text())  {
            widget->setText(text);
            emit textChanged();
        }
    }
