#include "antwindow.h"
#include "ui_antwindow.h"

#include <QPixmap>
#include <QDebug>
#include <QResizeEvent>
#include <QThread>
#include <QApplication>
#include <QElapsedTimer>
#include <QDir>
#include <QDateTime>

ANTWindow::ANTWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ANTWindow)
{
    ui->setupUi(this);
    antMain = new ANTMain();

    // Event filters
    this->installEventFilter(this);
    ui->pushButton_quit->installEventFilter(this);

    // Savefile directory
    QDateTime dt = QDateTime::currentDateTime();
    saveFile = QDir::currentPath() + "/data/" +
            dt.toString("yyyyMMddhhmm") + "_ant.csv";

    // Accept inputs
    acceptArrows = false;

    // Load initial image
    waitForKey = false;
    pix = QPixmap(":/resources/img/count/waiting.JPG");
}


ANTWindow::~ANTWindow()
{
    delete ui;
}

bool ANTWindow::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() != QEvent::KeyPress) return false;
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    // if waiting for start
    if (waitForKey)
    {
        waitForKey = false;
        countDown();
        return true;
    }
    else if (keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Right) {
        if (acceptArrows)
        {
            acceptArrows = false;
            if (keyEvent->key() == Qt::Key_Left) answeredArrow = "Left";
            if (keyEvent->key() == Qt::Key_Right) answeredArrow = "Right";
            saveResult(antMain->targetArrowName,
                       answeredArrow,
                       timer.elapsed());
            antSession();
            return true;
        } else {
            event->ignore();
            return true;
        }
    }
    else if (keyEvent->key() == Qt::Key_Space){
        event->ignore();
        return true;
    }
    else {
        return false;
    }
}

void ANTWindow::startSession()
{
    ui->label_pic->setPixmap(pix.scaled(ui->label_pic->width(),
                                        ui->label_pic->height(),
                                        Qt::KeepAspectRatio));
    waitForKey = true;
}

void ANTWindow::countDown()
{
    QPixmap count1(":/resources/img/count/count1.JPG");
    QPixmap count2(":/resources/img/count/count2.JPG");
    QPixmap count3(":/resources/img/count/count3.JPG");
    // 3
    ui->label_pic->setPixmap(count3.scaled(ui->label_pic->width(),
                                           ui->label_pic->height(),
                                           Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();
    QThread::msleep(1000);

    //2
    ui->label_pic->setPixmap(count2.scaled(ui->label_pic->width(),
                                           ui->label_pic->height(),
                                           Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();
    QThread::msleep(1000);

    //1
    ui->label_pic->setPixmap(count1.scaled(ui->label_pic->width(),
                                           ui->label_pic->height(),
                                           Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();
    QThread::msleep(1000);

    // Show fixation
    ui->label_pic->setPixmap(antMain->pixWait.scaled(ui->label_pic->width(),
                                                        ui->label_pic->height(),
                                                        Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    antSession();
}

void ANTWindow::antSession()
{
    // Grab new image dataset
    antMain->choosePix();

    // Show fixation
    ui->label_pic->setPixmap(antMain->pixWait.scaled(ui->label_pic->width(),
                                                     ui->label_pic->height(),
                                                     Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();
    int fixationWait = rand() % (1600-400 + 1) + 400; // time to display fixation (400-1600 ms)
    QThread::msleep(fixationWait);

    // Show cue
    ui->label_pic->setPixmap(antMain->pixCue.scaled(ui->label_pic->width(),
                                                    ui->label_pic->height(),
                                                    Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // Duration to show cue
    QThread::msleep(100);

    // Show fixation
    ui->label_pic->setPixmap(antMain->pixWait.scaled(ui->label_pic->width(),
                                                     ui->label_pic->height(),
                                                     Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // Duration to show fixation
    QThread::msleep(400);

    // Show arrow
    ui->label_pic->setPixmap(antMain->pixArrow.scaled(ui->label_pic->width(),
                                                      ui->label_pic->height(),
                                                      Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    acceptArrows = true;
    timer.start(); // continues until an arrow key is entered
}

void ANTWindow::saveResult(QString pixName,
                           QString arrow,
                           qint64 reactionTime)
{
    QFile data(saveFile);
    if(data.open(QFile::WriteOnly |QIODevice::Append))
    {
        QTextStream output(&data);
        output << pixName << "," << arrow << "," << reactionTime << "\n";
    }
}

void ANTWindow::resizeEvent(QResizeEvent *event)
{
    QSize newsize = event->size()*0.9;
    QPixmap px = pix.scaled(newsize, Qt::KeepAspectRatio);
    ui->label_pic->setPixmap(px);
    ui->label_pic->resize(newsize);
    QWidget::resizeEvent(event);
}

void ANTWindow::on_pushButton_quit_clicked()
{
    close();
}
