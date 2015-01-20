#include "qconsole.h"
#include <QTextBlock>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "singleton.h"

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

static int l_my_log(lua_State* L) {
    int nargs = lua_gettop(L);
    std::ofstream ss("log.txt", std::ios::app);
    for (int i=1; i <= nargs; ++i) {
        ss << lua_tostring(L, i);
    }

    return 0;
}

std::string QConsole::bubuf = "";

int QConsole::myPrint(lua_State* L)
{
    std::stringstream ss;
    int nargs = lua_gettop(L);
    for (int i=1; i <= nargs; ++i) {
        ss << lua_tostring(L, i);
    }
    QConsole::bubuf = ss.str();
    return 0;
}

int QConsole::moveX(lua_State* L)
{
    std::stringstream ss;
    int nargs = lua_gettop(L);
    std::string mesh = lua_tostring(L, 1);
    float x = atof(lua_tostring(L, 2));
    float y = atof(lua_tostring(L, 3));
    float z = atof(lua_tostring(L, 4));

    std::cout << "moving " << mesh << " to " << x << " " << y << " " << z << std::endl;

    return 0;
}


QConsole::QConsole(QWidget* parent) : QPlainTextEdit(parent), hIndex(-1), L(NULL)
{
   const struct luaL_Reg printlib2 [] = {
      {"print", QConsole::myPrint},
      {"moveX", moveX},
      {NULL, NULL} /* end of array */
    };

    L =  luaL_newstate();
    luaL_openlibs(L);

    lua_getglobal(L, "_G");
    luaL_setfuncs(L, printlib2, 0);
    lua_pop(L, 1);
}

QConsole::~QConsole()
{
    if(L)
        lua_close(L);
}

void QConsole::mousePressEvent(QMouseEvent * event)
{
    return;
}

void QConsole::mouseReleaseEvent(QMouseEvent * event)
{
    return;
}


void QConsole::keyPressEvent(QKeyEvent *event)
{
    QString txt;
    QString cmd;
    switch(event->key()) {
    case Qt::Key_Return:
         cmd = this->getCurrentLine();
         txt = QString("res: ") + cmd;
         this->execCommand(cmd);
         addHistoryEntry(cmd);

         this->appendPlainText(QString(bubuf.c_str()));
         bubuf="";
         this->appendPlainText("");
        break;
    case Qt::Key_Backspace:
        if(this->textCursor().positionInBlock() != 0)
            QPlainTextEdit::keyPressEvent(event);
        break;
    case Qt::Key_Up:
        this->historyUp();
        break;
    case Qt::Key_Down:
        this->historyDown();
        break;
    default:
        QPlainTextEdit::keyPressEvent(event);
    }

}


QString QConsole::getCurrentLine()
{
    return textCursor().block().text().trimmed();
}

void QConsole::removeCurrentLine()
{
    this->moveCursor( QTextCursor::End, QTextCursor::MoveAnchor );
    this->moveCursor( QTextCursor::StartOfLine, QTextCursor::MoveAnchor );
    this->moveCursor( QTextCursor::End, QTextCursor::KeepAnchor );
    this->textCursor().removeSelectedText();
}


void QConsole::addHistoryEntry(const QString& entry)
{
    this->history.push_back(entry);
    this->hIndex++;
}

void QConsole::historyUp()
{
    if(!this->history.size())
        return;
    this->removeCurrentLine();


    if(this->hIndex > 0)
        this->hIndex--;
    QString cmd = this->history[hIndex];
    this->insertPlainText(cmd);
}

void QConsole::historyDown()
{
    if(!this->history.size())
        return;
    this->removeCurrentLine();

    if(this->hIndex < this->history.size()-1)
        this->hIndex++;
    QString cmd = this->history[hIndex];
    this->insertPlainText(cmd);
}


void QConsole::execCommand(const QString cmd)
{
    luaL_dostring(L, cmd.toStdString().c_str());
}
