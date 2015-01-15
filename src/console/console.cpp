#include "console.h"

#include <QScrollBar>
#include <QTextBlock>

#include <QtCore/QDebug>

extern "C" {

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <string>
#include <iostream>
#include <sstream>

void bail(lua_State *L, char *msg){
	fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
		msg, lua_tostring(L, -1));
}

static std::string buffer = "";

static int l_my_print(lua_State* L) {
    int nargs = lua_gettop(L);
    std::stringstream ss;
    for (int i=1; i <= nargs; ++i) {
        ss << lua_tostring(L, i);
    }
    buffer = ss.str();
    return 0;
}

static const struct luaL_Reg printlib [] = {
  {"print", l_my_print},
  {NULL, NULL} /* end of array */
};


Console::Console(QWidget *parent)
    : QPlainTextEdit(parent), L(NULL)
{
    document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);

    this->insertPlainText(">");

    L = luaL_newstate();                        /* Create Lua state variable */
    luaL_openlibs(L);                           /* Load Lua libraries */

    lua_getglobal(L, "_G");
    luaL_setfuncs(L, printlib, 0);
    lua_pop(L, 1);
}

Console::~Console()
{
    if(L)
      lua_close(L);                               /* Clean up, free the Lua state var */
}


void Console::keyPressEvent(QKeyEvent *e)
{
    std::string cmd;
    const char* str = NULL;
    switch (e->key()) {
    case Qt::Key_Return:
        cmd = textCursor().block().text().trimmed().toStdString();
        QPlainTextEdit::keyPressEvent(e);
        if(luaL_dostring(L, cmd.substr(1).c_str()))
        {
          bail(L, "lua_pcall() failed");          /* Error out if Lua file has an error */
          str = lua_tostring(L, -1);
          this->insertPlainText(QString(str));
        }
        else
        {
            this->insertPlainText(QString(buffer.c_str()));
        }
     this->appendPlainText(">");
     break;
    case Qt::Key_Backspace:
      QPlainTextEdit::keyPressEvent(e);
      break;
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
            QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text().toLocal8Bit());
    }
}

void Console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void Console::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
