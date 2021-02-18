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


private slots:
    void on_pushButton_quit_clicked();

private:
    void countDown();
    void changeMode();
    void stroopSession();
    void saveResult(int, QString, QString, qint64);

    Ui::StroopWindow *ui;
    QPixmap pix;
    StroopMain *stroopMain;
    QString answeredArrow;
    QElapsedTimer timer;
    bool waitForKey;
    bool acceptArrows;

    QString saveFile;
    int testMode;

    int countPixShown;
    int numPixShow;

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // STROOPWINDOW_H
