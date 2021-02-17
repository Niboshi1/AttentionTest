#include "stroopwindow.h"
#include "ui_stroopwindow.h"

#include <QPixmap>
#include <QDebug>
#include <QResizeEvent>
#include <QThread>
#include <QApplication>
#include <QElapsedTimer>
#include <QDir>
#include <QDateTime>

StroopWindow::StroopWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StroopWindow)
{
    ui->setupUi(this);
    stroopMain = new StroopMain();

    // Event filters
    this->installEventFilter(this);
    ui->pushButton_quit->installEventFilter(this);

    // Savefile directory
    QDateTime dt = QDateTime::currentDateTime();
    saveFile = QDir::currentPath() + "/data/" +
            dt.toString("yyyyMMddhhmm") + "_stroop.csv";

    // Accept inputs
    acceptArrows = false;

    // Load initial image
    waitForKey = false;
    pix = QPixmap(":/resources/img/count/waiting.JPG");
}

StroopWindow::~StroopWindow()
{
    delete ui;
}

bool StroopWindow::eventFilter(QObject* obj, QEvent* event)
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

    // if waiting for arrow key input
    else if (keyEvent->key() == Qt::Key_Left ||
             keyEvent->key() == Qt::Key_Right ||
             keyEvent->key() == Qt::Key_Up ||
             keyEvent->key() == Qt::Key_Down)
    {
        if (acceptArrows)
        {
            acceptArrows = false;
            if (keyEvent->key() == Qt::Key_Left) answeredArrow = "Left";
            if (keyEvent->key() == Qt::Key_Right) answeredArrow = "Right";
            if (keyEvent->key() == Qt::Key_Up) answeredArrow = "Up";
            if (keyEvent->key() == Qt::Key_Down) answeredArrow = "Down";
            saveResult(stroopMain->testMode,
                       answeredArrow,
                       stroopMain->targetColorName,
                       timer.elapsed());
            stroopSession();
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


void StroopWindow::resizeEvent(QResizeEvent *event)
{
    QSize newsize = event->size()*0.9;
    QPixmap px = pix.scaled(newsize, Qt::KeepAspectRatio);
    ui->label_pic->setPixmap(px);
    ui->label_pic->resize(newsize);
    QWidget::resizeEvent(event);
}

void StroopWindow::startSession()
{
    ui->label_pic->setPixmap(pix.scaled(ui->label_pic->width(),
                                        ui->label_pic->height(),
                                        Qt::KeepAspectRatio));
    waitForKey = true;
}

void StroopWindow::countDown()
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
    ui->label_pic->setPixmap(stroopMain->pixWait.scaled(ui->label_pic->width(),
                                                        ui->label_pic->height(),
                                                        Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    changeMode();
}

void StroopWindow::changeMode() {
    QPixmap pixRule;
    if (stroopMain->testMode) {
        pixRule = stroopMain->pixInstructionColor;
    } else {
        pixRule = stroopMain->pixInstructionWord;
    }

    // Set instruction image
    ui->label_pic->setPixmap(pixRule.scaled(ui->label_pic->width(),
                                        ui->label_pic->height(),
                                        Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // Start settsion
    QThread::msleep(3000);
    stroopSession();

}

void StroopWindow::stroopSession()
{

    // Grab new image dataset
    stroopMain->choosePix();

    // Show fixation
    ui->label_pic->setPixmap(stroopMain->pixWait.scaled(ui->label_pic->width(),
                                                         ui->label_pic->height(),
                                                         Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    // Duration of fixation
    int fixationWait = rand() % (1600-400 + 1) + 400; // time to display fixation (400-1600 ms)
    QThread::msleep(fixationWait);

    // Show color image
    ui->label_pic->setPixmap(stroopMain->pixColor.scaled(ui->label_pic->width(),
                                                         ui->label_pic->height(),
                                                         Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    acceptArrows = true;
    timer.start(); // continues until an arrow key is entered
}

void StroopWindow::saveResult(bool rule,
                              QString pixName,
                              QString arrow,
                              qint64 reactionTime)
{
    QFile data(saveFile);
    if(data.open(QFile::WriteOnly |QIODevice::Append))
    {
        QTextStream output(&data);
        output << rule << "," << pixName << "," << arrow << "," << reactionTime << "\n";
    }
}

void StroopWindow::on_pushButton_quit_clicked()
{
    close();
}
