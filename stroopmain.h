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
    void choosePix(int testmode);

    QPixmap pixColor;
    QPixmap pixInstructionColor;
    QPixmap pixInstructionWord;
    QPixmap pixInstructionCword;

    QString targetColorName;

private:
    QStringList imagePathsPatch;
    QStringList imagePathsWords;
    QStringList imagePathsCwords;
};

#endif // STROOPMAIN_H
