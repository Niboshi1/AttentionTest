#ifndef STROOPWINDOW_H
#define STROOPWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include "stroopmain.h"

namespace Ui {
class StroopWindow;
}

class StroopWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StroopWindow(QWidget *parent = nullptr);
    ~StroopWindow();

    void startSession();

    QString userID;

private slots:
    void on_pushButton_quit_clicked();

private:
    void startSessionStroop();
    void countDown();
    void changeMode();
    void stroopSession();
    void saveResult(int, QString, QString, qint64, qint64);

    Ui::StroopWindow *ui;
    QPixmap pix;
    StroopMain *stroopMain;
    QString answeredArrow;
    QElapsedTimer timer;
    QElapsedTimer timerAll;
    QElapsedTimer timerSession;
    bool waitForKey;
    bool acceptArrows;

    QString saveFile;
    int testMode;

    int countPixShown;
    int numPixShow;

    bool checkInput(QString, QString);

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // STROOPWINDOW_H
