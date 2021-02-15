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
    void antSession();
    void saveResult(QString, QString, qint64);
    bool acceptArrows;

signals:
    void inputReceived();

private:
    Ui::ANTWindow *ui;
    QPixmap pix;
    ANTMain *antMain;
    QString answeredArrow;
    QElapsedTimer timer;

    QString saveFile;
    bool waitForKey;

    void countDown();

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject* obj, QEvent* event);

private slots:
    void on_pushButton_quit_clicked();
};

#endif // ANTWINDOW_H
