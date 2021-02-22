#ifndef ANTWINDOW_H
#define ANTWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include "antmain.h"

namespace Ui {
class ANTWindow;
}

class ANTWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ANTWindow(QWidget *parent = nullptr);
    ~ANTWindow();

    void startSession();
    QString userID;

signals:
    void inputReceived();

private:
    Ui::ANTWindow *ui;
    QPixmap pix;
    QVector<QPixmap> imagePathsArrow;
    QVector<QPixmap> imagePathsCue;
    QString saveFile;

    QElapsedTimer timer;
    QElapsedTimer timerAll;
    QString answeredArrow;
    QString correctArrow;

    bool waitForKey;
    bool acceptArrows;
    bool pixChosen;

    void initializeImages();

    void countDown();
    void choosePix();
    void antSession();
    void saveResult(int, int, QString, qint64, qint64);

    QPixmap pixWait;
    int pixIdxCue;
    int pixIdxArrow;

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);

private slots:
    void on_pushButton_quit_clicked();
};

#endif // ANTWINDOW_H
