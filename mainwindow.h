#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "antwindow.h"
#include "stroopwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject* obj, QEvent* event);

private slots:
    void on_pushButton_ant_clicked();

    void on_pushButton_stroop_clicked();

private:
    Ui::MainWindow *ui;
    ANTWindow *antWindow;
    StroopWindow *stroopWindow;
};
#endif // MAINWINDOW_H
