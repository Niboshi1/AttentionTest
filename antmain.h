#ifndef ANTMAIN_H
#define ANTMAIN_H

#include <QBasicTimer>
#include <QList>
#include <QPixmap>

class ANTMain
{
public:
    ANTMain();
    QStringList loadImagesets(QString dirName);
    void initializeImages();
    void choosePix();

    QPixmap pixWait;
    QPixmap pixCue;
    QPixmap pixArrow;
    QString targetArrowName;
    QString targetCueName;

private:
    QStringList imagePathsArrow;
    QStringList imagePathsCue;

};

#endif // ANTMAIN_H
