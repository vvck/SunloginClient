#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
public Q_SLOTS:
    void UpdateStack(int nIndex);
    void onMin();
private:
    Ui::MainWindow *ui;
    bool m_bMoveable;
    QPoint m_point;
private:
    void initWidget();
};
#endif // MAINWINDOW_H
