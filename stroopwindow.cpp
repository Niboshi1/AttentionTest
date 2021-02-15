#include "stroopwindow.h"
#include "ui_stroopwindow.h"

#include <QPixmap>
#include <QDebug>
#include <QResizeEvent>
#include <QThread>
#include <QApplication>
#include <QElapsedTimer>
#include <QDir>

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

    // Load initial image
    waitForKey = false;
    changeMode();
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
        stroopSession();
        waitForKey = false;
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
            reactionTime << timer.elapsed();
            if (keyEvent->key() == Qt::Key_Left) answeredArrow << "Left";
            if (keyEvent->key() == Qt::Key_Right) answeredArrow << "Right";
            if (keyEvent->key() == Qt::Key_Up) answeredArrow << "Up";
            if (keyEvent->key() == Qt::Key_Down) answeredArrow << "Down";
            pixNames << stroopMain->targetColorName;
            stroopRule << stroopMain->testMode;
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

void StroopWindow::stroopSession()
{

    // Grab new image dataset
    stroopMain->choosePix();

    // Show cue
    ui->label_pic->setPixmap(stroopMain->pixColor.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio));
    ui->label_pic->repaint();
    qApp->processEvents();

    acceptArrows = true;
    timer.start(); // continues until an arrow key is entered
}

void StroopWindow::changeMode() {
    if (stroopMain->testMode) {
        pix = stroopMain->pixInstructionColor;
    } else {
        pix = stroopMain->pixInstructionWord;
    }

    // Set instruction image
    ui->label_pic->setPixmap(pix.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio));
    ui->label_pic->setScaledContents(true);
    waitForKey = true;

}

void StroopWindow::saveResult()
{
    QString filePath = QDir::currentPath() + "/data/test_stroop.csv";

    QFile data(filePath);
    if(data.open(QFile::WriteOnly |QFile::Truncate))
    {
        QTextStream output(&data);

        // Add stroop rule data
        for (int i = 0; i < stroopRule.length(); i++)
        {
            output << stroopRule[i] << ",";
        }
        output << "\n";

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

void StroopWindow::on_pushButton_quit_clicked()
{
    saveResult();
    qDebug() << stroopRule;
    qDebug() << answeredArrow;
    qDebug() << pixNames;
    qDebug() << reactionTime;
    close();
}
