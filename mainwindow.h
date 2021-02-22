#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "antwindow.h"
#include "stroopwindow.h"
#include "anttutorial.h"
#include "strooptutorial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString userID;
    void initialize();

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private slots:
    void on_pushButton_ant_clicked();

    void on_pushButton_stroop_clicked();

    void on_pushButton_stroop_tutorial_clicked();

    void on_pushButton_ant_tutorial_clicked();

private:
    Ui::MainWindow *ui;
    ANTWindow *antWindow;
    StroopWindow *stroopWindow;
    ANTTutorial *antTutorial;
    StroopTutorial *stroopTutorial;
};
#endif // MAINWINDOW_H
