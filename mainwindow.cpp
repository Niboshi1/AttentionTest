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
    ui->pushButton_ant_tutorial->setFixedSize(buttonSize);
    ui->pushButton_stroop_tutorial->setFixedSize(buttonSize);


    // Set pictures
    QSize picSize = QSize(400, 300);
    ui->label_ant_pic->setFixedSize(picSize);
    ui->label_stroop_pic->setFixedSize(picSize);

    QPixmap pixant(":/resources/img/ANT_test/arrows/L_incg_top.JPG");
    ui->label_ant_pic->setPixmap(pixant.scaled(ui->label_ant_pic->width(),
                                               ui->label_ant_pic->height(),
                                               Qt::KeepAspectRatio));

    QPixmap pixstroop(":/resources/img/Stroop_test/colorWords/blueRcword.JPG");
    ui->label_stroop_pic->setPixmap(pixstroop.scaled(ui->label_stroop_pic->width(),
                                                     ui->label_stroop_pic->height(),
                                                     Qt::KeepAspectRatio));

    ui->label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    ui->label_userID->setText(("被験者ID：" + userID));
}


void MainWindow::on_pushButton_ant_clicked()
{
    //hide(); // hide MainWindow
    antWindow = new ANTWindow(this);
    antWindow->userID = userID;
    antWindow->showFullScreen();
    antWindow->startSession();
}

void MainWindow::on_pushButton_stroop_clicked()
{
    //hide(); // hide MainWindow
    stroopWindow = new StroopWindow(this);
    stroopWindow->userID = userID;
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


