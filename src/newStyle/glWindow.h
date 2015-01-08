#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class GLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)



public:
    explicit GLWindow(QWindow *parent = 0);
    ~GLWindow();

    virtual void render(QPainter *painter);
    virtual void render();
    void nativePainting();
    virtual void initialize();

    void setAnimating(bool animating);

    qreal t() const { return m_t; }
    void setT(qreal t);

signals:
    void tChanged();


public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

    void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_update_pending;
    bool m_animating;
    qreal m_t;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
};
