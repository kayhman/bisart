#include "hop.h"
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/QDeclarativeView>
#include <QApplication>
#include <QGLWidget>
#include <QPainter>
 
 
MDE::MDE(QDeclarativeItem *parent )
{
 setFlag(QGraphicsItem::ItemHasNoContents, false);
}
 
void MDE::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
 painter->beginNativePainting();
 glClear(GL_COLOR_BUFFER_BIT);
 glLoadIdentity();
 glBegin(GL_QUADS);
  glColor3ub(0,0,255);
  glVertex2d(-0.75,-0.75);
  glVertex2d(-0.75,0.75);
  glColor3ub(255,0,0);
  glVertex2d(0.75,0.75);
  glVertex2d(0.75,-0.75);
 glEnd();
 painter->endNativePainting();
}
