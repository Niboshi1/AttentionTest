#include "antwindow.h"
#include "ui_antwindow.h"

#include <QPixmap>
#include <QDebug>
#include <QResizeEvent>
#include <QThread>
#include <QApplication>
#include <QElapsedTimer>
#include <QDir>

ANTWindow::ANTWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ANTWindow)
{
    ui->setupUi(this);
    antMain = new ANTMain();

    // Event filters
    this->installEventFilter(this);
    ui->pushButton_quit->installEventFilter(this);

    // Accept inputs
    acceptArrows = false;

    // Load initial image
    pix = antMain->pixWait;
    ui->label_pic->setPixmap(pix.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio));
    ui->label_pic->setScaledContents(true);
}


ANTWindow::~ANTWindow()
{
    delete ui;
}

bool ANTWindow::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() != QEvent::KeyPress) return false;
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Right) {
        if (acceptArrows)
        {
            reactionTime << timer.elapsed();
            if (keyEvent->key() == Qt::Key_Left) answeredArrow << "Left";
            if (keyEvent->key() == Qt::Key_Right) answeredArrow << "Right";
            pixNames << antMain->targetArrowName;
            antSessionWait();
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

void ANTWindow::antSession()
{
    // Grab new image dataset
    antMain->choosePix();

    // Show fixation
    int fixationWait = rand() % (1600-400 + 1) + 400; // time to display fixation (400-1600 ms)
    QThread::msleep(fixationWait);

    // Show cue
    ui->label_pic->setPixmap(antMain->pixCue.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // Duration to show cue
    QThread::msleep(100);

    // Show fixation
    ui->label_pic->setPixmap(antMain->pixWait.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // Duration to show fixation
    QThread::msleep(400);

    // Show arrow
    ui->label_pic->setPixmap(antMain->pixArrow.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    acceptArrows = true;
    timer.start(); // continues until an arrow key is entered
}

void ANTWindow::antSessionWait()
{
    acceptArrows = false;

    // Show fixed cross
    QThread::msleep(300);
    ui->label_pic->setPixmap(antMain->pixWait.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // New session
    antSession();
}

void ANTWindow::saveResult()
{
    QString filePath = QDir::currentPath() + "/data/test.csv";

    QFile data(filePath);
    if(data.open(QFile::WriteOnly |QFile::Truncate))
    {
        QTextStream output(&data);

        // Add answeredArrow data
        for (int i = 0; i < answeredArrow.length(); i++)
        {
            output << answeredArrow[i] << ",";
        }
        output << "\n";

        // Add pixNames data
        for (int i = 0; i < pixNames.length(); i++)
        {
            output << pixNames[i] << ",";
        }
        output << "\n";

        // Add reactionTime data
        for (int i = 0; i < reactionTime.length(); i++)
        {
            output << reactionTime[i] << ",";
        }
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
    saveResult();
    qDebug() << answeredArrow;
    qDebug() << pixNames;
    qDebug() << reactionTime;
    close();
}
