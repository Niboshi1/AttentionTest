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



    // Accept inputs
    acceptArrows = false;

    // Mode count
    numPixShow = 10;
    countPixShown = numPixShow;
    testMode = 0;

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
            if (keyEvent->key() == Qt::Key_Left) answeredArrow = "yellow";
            if (keyEvent->key() == Qt::Key_Right) answeredArrow = "blue";
            if (keyEvent->key() == Qt::Key_Up) answeredArrow = "red";
            if (keyEvent->key() == Qt::Key_Down) answeredArrow = "green";
            if (!checkInput(stroopMain->targetColorName, answeredArrow)) {
                // if a miss, do nothing
                saveResult(testMode,
                           answeredArrow,
                           stroopMain->targetColorName,
                           timer.elapsed(),
                           timerAll.elapsed());
                acceptArrows = true;
                return true;
            }
            else {
                // if a hit, got to next session
                saveResult(testMode,
                           answeredArrow,
                           stroopMain->targetColorName,
                           timer.elapsed(),
                           timerAll.elapsed());
                stroopSession();
                return true;
            }

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
    // Savefile directory
    QDateTime dt = QDateTime::currentDateTime();
    qDebug() << userID;
    saveFile = QDir::currentPath() + "/data/" + userID + "_" +
            dt.toString("yyyyMMddhhmm") + "_stroop.csv";

    timerAll.start();
    startSessionStroop();

}

void StroopWindow::startSessionStroop()
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

    changeMode();
}

void StroopWindow::changeMode() {
    QPixmap pixRule;
    if (testMode==0) {
        pixRule = stroopMain->pixInstructionColor;
    } else if (testMode==1) {
        pixRule = stroopMain->pixInstructionWord;
    } else if (testMode==2) {
        pixRule = stroopMain->pixInstructionCword;
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
    // Check session number
    if (countPixShown==0) {
        //initialize
        countPixShown=numPixShow;
        switch (testMode) {
                case 0:
                    testMode = 1;
                    startSessionStroop();
                    break;
                case 1:
                    testMode = 2;
                    startSessionStroop();
                    break;
                case 2:
                    close();
                    break;
                default:
                    break;
            }
    } else {
        // Decrement number
        countPixShown--;

        // Grab new image dataset
        stroopMain->choosePix(testMode);

        // Show color image
        ui->label_pic->setPixmap(stroopMain->pixColor.scaled(ui->label_pic->width(),
                                                             ui->label_pic->height(),
                                                             Qt::KeepAspectRatio));
        ui->label_pic->repaint();
        qApp->processEvents();

        acceptArrows = true;
        timer.start(); // continues until an arrow key is entered
    }
}

bool StroopWindow::checkInput(QString pixName, QString color)
{
    if (pixName.contains(color)) {
        return true;
    } else return false;
}

void StroopWindow::saveResult(int rule,
                              QString pixName,
                              QString arrow,
                              qint64 reactionTime,
                              qint64 overallTime)
{
    QFile data(saveFile);
    if(data.open(QFile::WriteOnly |QIODevice::Append))
    {
        QTextStream output(&data);
        output << rule << ","
               << pixName << ","
               << arrow << ","
               << reactionTime << ","
               << overallTime << "\n";;
    }
}

void StroopWindow::on_pushButton_quit_clicked()
{
    close();
}
