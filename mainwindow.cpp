#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    ui->pushButton_ant->installEventFilter(this);

    // Set button size
    QSize buttonSize = QSize(150, 80);
    ui->pushButton_ant->setFixedSize(buttonSize);
    ui->pushButton_stroop->setFixedSize(buttonSize);

    // Create result folder
    QString dirRsult = QDir::currentPath() + "/data";
    if (!QDir(dirRsult).exists())
    {
        QDir().mkdir(dirRsult);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ant_clicked()
{
    //hide(); // hide MainWindow
    ant_window = new ANTWindow(this);
    ant_window->showFullScreen();
    ant_window->antSession();
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() != QEvent::KeyPress) return false;
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if(keyEvent->key() == Qt::Key_Space) {
        event->ignore();
        return true;
      }
    else {
        return false;
    }
}


