#ifndef QCONSOLE_H
#define QCONSOLE_H

#include <QPlainTextEdit>
#include <vector>
#include <string>

struct lua_State;

class QConsole : public QPlainTextEdit
{
    Q_OBJECT
private:
    std::vector<QString> history;
    int hIndex;
public:
    explicit QConsole(QWidget* parent = 0);
    ~QConsole();
    static int myPrint(lua_State* L);
    static int moveX(lua_State* L);

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);

    QString getCurrentLine();
    void removeCurrentLine();
    void addHistoryEntry(const QString& entry);
    void historyUp();
    void historyDown();
    void execCommand(const QString cmd);
    lua_State* L;
    static std::string bubuf;
};

#endif // QCONSOLE_H
