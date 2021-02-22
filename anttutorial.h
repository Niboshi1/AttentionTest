#ifndef ANTTUTORIAL_H
#define ANTTUTORIAL_H

#include <QMainWindow>

namespace Ui {
class ANTTutorial;
}

class ANTTutorial : public QMainWindow
{
    Q_OBJECT

public:
    explicit ANTTutorial(QWidget *parent = nullptr);
    ~ANTTutorial();

private:
    Ui::ANTTutorial *ui;

    void initializeImages();
    void nextSlide();

    QStringList imageSlides;
    QPixmap pix;

    int currentSlide;
    bool waitForKey;

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);
private slots:
    void on_pushButton_clicked();
};

#endif // ANTTUTORIAL_H
