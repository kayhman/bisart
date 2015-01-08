#pragma once     
#include <QtDeclarative/QDeclarativeItem>

class MDE : public QDeclarativeItem
{
  Q_OBJECT
  
 public:
  MDE(QDeclarativeItem *parent = 0);
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};
