#ifndef ANTMAIN_H
#define ANTMAIN_H

#include <QBasicTimer>
#include <QList>
#include <QPixmap>

class ANTMain
{
public:
    ANTMain();

    void initializeImages();
    void choosePix();

    QPixmap pixWait;
    QPixmap pixCue;
    QPixmap pixArrow;

    int pixIdxCue;
    int pixIdxArrow;
    QString correctArrow;

    QVector<QPixmap> imagePathsArrow;
    QVector<QPixmap> imagePathsCue;

    bool pixChosen;

private:

};

#endif // ANTMAIN_H
