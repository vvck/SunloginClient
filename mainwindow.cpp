#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_bMoveable(false)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    ui->setupUi(this);
    initWidget();
    connect(ui->toolButton_menu, &QToolButton::clicked, this, &MainWindow::onMin);
    connect(ui->toolButton_min, &QToolButton::clicked, this, &MainWindow::onMin);
    connect(ui->toolButton_close, &QToolButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidget()
{
    QToolPushButton* toolButtonArray[] = { ui->toolButton_assist ,
        ui->toolButton_device,
        ui->toolButton_find,
        ui->toolButton_shot};

        QString rcPath_light[] = {":/pic/pic/assist.png",
        ":/pic/pic/device.png",
        ":/pic/pic/gps.png",
        ":/pic/pic/shot.png"};

        QString rcPath_dark[] = { ":/pic/pic/assist-h.png",
        ":/pic/pic/device-h.png",
        ":/pic/pic/gps-h.png",
        ":/pic/pic/shot-h.png" };

        int nSize = sizeof(toolButtonArray)/sizeof(toolButtonArray[0]);

        for (int i=0; i< nSize; i++)
        {
            toolButtonArray[i]->setChangeIcon(rcPath_light[i],rcPath_dark[i], QSize(36, 36));
            toolButtonArray[i]->setIndex(i);
            connect(toolButtonArray[i], &QToolPushButton::checkSignal, this, &MainWindow::UpdateStack);
        }

        ui->toolButton_assist->setChecked(true);
        ui->stackedWidget->setCurrentIndex(0);
        ui->toolButton_assist->setIcon(QIcon(rcPath_dark[0]));
        ui->toolButton_assist->setIconSize(QSize(36, 36));
        ui->toolButton_device->setChecked(false);
        ui->toolButton_find->setChecked(false);
        ui->toolButton_shot->setChecked(false);
}

void MainWindow::UpdateStack(int nIndex)
{
    QToolPushButton* toolButtonArray[] = { ui->toolButton_assist ,
        ui->toolButton_device,
        ui->toolButton_find,
        ui->toolButton_shot};

    int nSize = sizeof(toolButtonArray) / sizeof(toolButtonArray[0]);
    if (nIndex<0 || nIndex >= nSize)
    {
        return;
    }

    for (int j = 0; j < nSize; j++)
    {
        if (j != nIndex)
        {
            toolButtonArray[j]->setIcon1();
            toolButtonArray[j]->setChecked(false);
        }
    }
    ui->stackedWidget->setCurrentIndex(nIndex);
}

void MainWindow::onMin()
{
    if (windowState() != Qt::WindowMinimized) {
        setWindowState(Qt::WindowMinimized);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
      m_point = event->globalPos() - frameGeometry().topLeft();

      QRect rect1 = ui->frame_head->frameRect();
      QRect rect2 = ui->frame_title->frameRect();
      if(rect1.contains(event->pos()) || rect2.contains(event->pos()))
      {
          m_bMoveable = true;
      }
      event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_bMoveable)
    {
        m_bMoveable = false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton && m_bMoveable)
    {
        move(event->globalPos() - m_point);
        event->accept();
    }
}
