#ifndef STROOPTUTORIAL_H
#define STROOPTUTORIAL_H

#include <QMainWindow>

namespace Ui {
class StroopTutorial;
}

class StroopTutorial : public QMainWindow
{
    Q_OBJECT

public:
    explicit StroopTutorial(QWidget *parent = nullptr);
    ~StroopTutorial();

private:
    Ui::StroopTutorial *ui;

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

#endif // STROOPTUTORIAL_H
