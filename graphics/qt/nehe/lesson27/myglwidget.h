#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QTime>

class QTimer;
class QKeyEvent;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    virtual ~MyGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *);
    void closeEvent(QCloseEvent *);

private:
    void showFPS();

    QTimer *timer;
    QTime fpsUpdater;

    bool fullscreen;
};

#endif // MYGLWIDGET_H
