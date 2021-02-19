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

    ui->label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ant_clicked()
{
    //hide(); // hide MainWindow
    antWindow = new ANTWindow(this);
    antWindow->showMaximized();
    antWindow->startSession();
}

void MainWindow::on_pushButton_stroop_clicked()
{
    //hide(); // hide MainWindow
    stroopWindow = new StroopWindow(this);
    stroopWindow->showFullScreen();
    stroopWindow->startSession();
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


