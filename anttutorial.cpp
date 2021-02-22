#include "anttutorial.h"
#include "ui_anttutorial.h"

#include <QPixmap>
#include <QDebug>
#include <QResizeEvent>
#include <QThread>
#include <QApplication>

ANTTutorial::ANTTutorial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ANTTutorial)
{
    ui->setupUi(this);

    // Event filters
    this->installEventFilter(this);
    ui->pushButton->installEventFilter(this);

    // Wait for key
    waitForKey = false;
    currentSlide = 0;

    // Initialize
    initializeImages();
    pix = QPixmap(imageSlides[currentSlide]);
    nextSlide();
}

ANTTutorial::~ANTTutorial()
{
    delete ui;
}

bool ANTTutorial::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() != QEvent::KeyPress) return false;
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

    // if waiting for start
    if (waitForKey && (keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_Enter)) {
        waitForKey = false;
        currentSlide++;
        nextSlide();
        return true;
    } else if (waitForKey && keyEvent->key() == Qt::Key_Left) {
        if (currentSlide != 0) {
            waitForKey = false;
            currentSlide--;
            nextSlide();
            return true;
        } else {
            event->ignore();
            return true;
        }
    } else if (keyEvent->key() == Qt::Key_Space){
        event->ignore();
        return true;
    }
    else {
        return false;
    }
}


void ANTTutorial::resizeEvent(QResizeEvent *event)
{
    QSize newsize = event->size()*0.9;
    QPixmap px = pix.scaled(newsize, Qt::KeepAspectRatio);
    ui->label->setPixmap(px);
    ui->label->resize(newsize);
    QWidget::resizeEvent(event);
}

void ANTTutorial::initializeImages()
{
    imageSlides = QStringList{":/resources/img/ANT_test_guide/Slide1.JPG",
                              ":/resources/img/ANT_test_guide/Slide2.JPG",
                              ":/resources/img/ANT_test_guide/Slide3.JPG",
                              ":/resources/img/ANT_test_guide/Slide4.JPG",
                              ":/resources/img/ANT_test_guide/Slide5.JPG",
                              ":/resources/img/ANT_test_guide/Slide6.JPG",
                              ":/resources/img/ANT_test_guide/Slide7.JPG",
                              ":/resources/img/ANT_test_guide/Slide8.JPG",
                              ":/resources/img/ANT_test_guide/Slide9.JPG",
                              ":/resources/img/ANT_test_guide/Slide10.JPG",
                              ":/resources/img/ANT_test_guide/Slide11.JPG",
                              ":/resources/img/ANT_test_guide/Slide12.JPG",
                              ":/resources/img/ANT_test_guide/Slide13.JPG",
                              ":/resources/img/ANT_test_guide/Slide14.JPG",
                              ":/resources/img/ANT_test_guide/Slide15.JPG",
                              ":/resources/img/ANT_test_guide/Slide16.JPG",
                              ":/resources/img/ANT_test_guide/Slide17.JPG"};
}

void ANTTutorial::nextSlide()
{
    if (currentSlide == imageSlides.count()) {
        close();
    } else {
        pix = QPixmap(imageSlides[currentSlide]);
        ui->label->setPixmap(pix.scaled(ui->label->width(),
                                        ui->label->height(),
                                        Qt::KeepAspectRatio));
        ui->label->repaint();
        qApp->processEvents();
        QThread::msleep(1000);

        // Ready for next slide
        waitForKey = true;
    }
}

void ANTTutorial::on_pushButton_clicked()
{
    close();
}
