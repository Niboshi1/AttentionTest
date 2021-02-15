#ifndef STROOPMAIN_H
#define STROOPMAIN_H

#include <QBasicTimer>
#include <QList>
#include <QPixmap>

class StroopMain
{
public:
    StroopMain();

    QStringList loadImagesets(QString dirName);
    void initializeImages();
    void choosePix();

    //QPixmap pixWait;
    QPixmap pixColor;
    QPixmap pixInstructionColor;
    QPixmap pixInstructionWord;

    QString targetColorName;

    bool testMode;

private:
    QStringList imagePathsColors;
};

#endif // STROOPMAIN_H
