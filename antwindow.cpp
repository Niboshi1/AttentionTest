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

    // Event filters
    this->installEventFilter(this);
    ui->pushButton_quit->installEventFilter(this);



    // Accept inputs
    acceptArrows = false;

    // initialize images
    QPixmap initialPix(":/resources/img/ANT_test/fixation.JPG");
    pixWait = initialPix;
    pixChosen = false;
    initializeImages();

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
            if (keyEvent->key() == Qt::Key_Left) answeredArrow = "L";
            if (keyEvent->key() == Qt::Key_Right) answeredArrow = "R";
            if (correctArrow != answeredArrow){
                saveResult(pixIdxCue,
                           pixIdxArrow,
                           answeredArrow,
                           timer.elapsed(),
                           timerAll.elapsed());
                acceptArrows = true;
            } else {
                saveResult(pixIdxCue,
                           pixIdxArrow,
                           answeredArrow,
                           timer.elapsed(),
                           timerAll.elapsed());
                antSession();
            }
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
    // Savefile directory
    QDateTime dt = QDateTime::currentDateTime();
    saveFile = QDir::currentPath() + "/data/" + userID + "_" +
            dt.toString("yyyyMMddhhmm") + "_ant.csv";

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
    ui->label_pic->setPixmap(pixWait.scaled(ui->label_pic->width(),
                                                        ui->label_pic->height(),
                                                        Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    antSession();
    timerAll.start();
}

void ANTWindow::antSession()
{
    // Grab new image dataset
    choosePix();

    // Wait until dataset is chosen
    while(!pixChosen) {
        QThread::msleep(100);
    }

    //Debug
    switch(pixIdxCue)
    {
    case 0 : qDebug() << "no cue"; break;
    case 1 : qDebug() << "central"; break;
    case 2 : qDebug() << "double"; break;
    case 3 : qDebug() << "top"; break;
    case 4 : qDebug() << "bottom"; break;
    default : break;
    }

    switch(pixIdxCue)
    {
    case 0 : qDebug() << "Left Congruent Top"; break;
    case 1 : qDebug() << "Right Congruent Top"; break;
    case 2 : qDebug() << "Left Incongruent Top"; break;
    case 3 : qDebug() << "Right Incongruent Top"; break;
    case 4 : qDebug() << "Left Neutral Top"; break;
    case 5 : qDebug() << "Right Neutral Top"; break;
    case 6 : qDebug() << "Left Congruent Bottom"; break;
    case 7 : qDebug() << "Right Congruent Bottom"; break;
    case 8 : qDebug() << "Left Incongruent Bottom"; break;
    case 9 : qDebug() << "Right Incongruent Bottom"; break;
    case 10 : qDebug() << "Left Neutral Bottom"; break;
    case 11 : qDebug() << "Right Neutral Bottom"; break;
    default : break;
    }

    qDebug() << "=================================";

    // Show fixation
    ui->label_pic->setPixmap(pixWait.scaled(ui->label_pic->width(),
                                                     ui->label_pic->height(),
                                                     Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();
    int fixationWait = rand() % (1600-400 + 1) + 400; // time to display fixation (400-1600 ms)
    QThread::msleep(fixationWait);

    // Show cue
    ui->label_pic->setPixmap(imagePathsCue[pixIdxCue].scaled(ui->label_pic->width(),
                                                    ui->label_pic->height(),
                                                    Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // Duration to show cue
    QThread::msleep(100);

    // Show fixation
    ui->label_pic->setPixmap(pixWait.scaled(ui->label_pic->width(),
                                                     ui->label_pic->height(),
                                                     Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // Duration to show fixation
    QThread::msleep(400);

    // Show arrow
    ui->label_pic->setPixmap(imagePathsArrow[pixIdxArrow].scaled(ui->label_pic->width(),
                                                      ui->label_pic->height(),
                                                      Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    acceptArrows = true;
    timer.start(); // continues until an arrow key is entered
}

// Processing images++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ANTWindow::initializeImages()
{
    imagePathsArrow = {QPixmap(":/resources/img/ANT_test/arrows/L_cong_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_cong_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_incg_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_incg_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_neut_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_neut_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_cong_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_cong_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_incg_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_incg_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_neut_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_neut_bot.JPG")};

    imagePathsCue = {QPixmap(":/resources/img/ANT_test/cue/cue0_non.JPG"),
                     QPixmap(":/resources/img/ANT_test/cue/cue1_cnt.JPG"),
                     QPixmap(":/resources/img/ANT_test/cue/cue2_dbl.JPG"),
                     QPixmap(":/resources/img/ANT_test/cue/cue3_top.JPG"),
                     QPixmap(":/resources/img/ANT_test/cue/cue4_bot.JPG")};
}

void ANTWindow::choosePix()
{
    pixChosen = false;
    int pixIdxArrowTmp;
    int pixIdxCueTmp = rand() % 5;

    // Get random cue
    while (pixIdxCue == pixIdxCueTmp) pixIdxCueTmp = rand() % 5;
    pixIdxCue = pixIdxCueTmp;

    switch(pixIdxCue)
    {
    case 3 :
        pixIdxArrowTmp = rand() % 6;
        while (pixIdxArrow == pixIdxArrowTmp) pixIdxArrowTmp = rand() % 6;
        pixIdxArrow = pixIdxArrowTmp;
        break;
    case 4 :
        pixIdxArrowTmp = rand() % 6 + 6;
        while (pixIdxArrow == pixIdxArrowTmp) pixIdxArrowTmp = rand() % 6 + 6;
        pixIdxArrow = pixIdxArrowTmp;
        break;
    default:
        pixIdxArrowTmp = rand() % 12;
        while (pixIdxArrow == pixIdxArrowTmp) pixIdxArrowTmp = rand() % 12;
        pixIdxArrow = pixIdxArrowTmp;
        break;
    }

    if (pixIdxArrow % 2) {
        correctArrow = "R";
    } else {
        correctArrow = "L";
    }

    pixChosen = true;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void ANTWindow::saveResult(int cue,
                           int arrow,
                           QString pixName,
                           qint64 reactionTime,
                           qint64 overallTime)
{
    QFile data(saveFile);
    if(data.open(QFile::WriteOnly |QIODevice::Append))
    {
        QTextStream output(&data);
        output << cue << ","
               << arrow << ","
               << pixName << ","
               << reactionTime << ","
               << overallTime << "\n";
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
