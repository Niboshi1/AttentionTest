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

    void stroopSession();
    void saveResult();
    void changeMode();
    bool acceptArrows;

private slots:
    void on_pushButton_quit_clicked();

private:
    Ui::StroopWindow *ui;
    QPixmap pix;
    StroopMain *stroopMain;
    QStringList pixNames;
    QStringList answeredArrow;
    QList<bool> stroopRule;
    QList<qint64> reactionTime;
    QElapsedTimer timer;
    bool waitForKey;


protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // STROOPWINDOW_H
