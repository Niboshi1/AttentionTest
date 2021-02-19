#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog w;

    // Create result folder
    QString dirRsult = QDir::currentPath() + "/data";
    if (!QDir(dirRsult).exists())
    {
        QDir().mkdir(dirRsult);
    }

    w.show();
    return a.exec();
}
