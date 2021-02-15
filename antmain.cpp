#include "antmain.h"

#include <QDir>
#include <QDebug>
#include <QList>

ANTMain::ANTMain()
{
    QPixmap initialPix("C:/Users/Coral/Pictures/ANT_test/fixation.JPG");
    pixWait = initialPix;
    initializeImages();
}

QStringList ANTMain::loadImagesets(QString dirName)
{
    QDir dir(dirName);
    QStringList imagePaths;
    qDebug() << "Loading from: " << dirName;
    QStringList fileNames = dir.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
    for (int i=0; i<fileNames.count(); i++)
        imagePaths << dir.absoluteFilePath(fileNames[i]);

    return imagePaths;
}

void ANTMain::initializeImages()
{
    imagePathsArrow = loadImagesets("C:/Users/Coral/Pictures/ANT_test/arrows");
    imagePathsCue = loadImagesets("C:/Users/Coral/Pictures/ANT_test/cue");
}

void ANTMain::choosePix()
{
    QStringList arrowPixFile;

    // Get random cue
    int pixIdxCue = rand() % imagePathsCue.count();
    const QFileInfo infoCue(imagePathsCue[pixIdxCue]);
    const QString file(infoCue.fileName());

    // Choose which arrow to show
    if (file == "cue3_top.JPG") arrowPixFile = imagePathsArrow.filter("top");
    else if (file == "cue4_bot.JPG") arrowPixFile = imagePathsArrow.filter("bot");
    else arrowPixFile = imagePathsArrow;

    int pixIdxArrow = rand() % arrowPixFile.count();
    const QFileInfo infoArrow(arrowPixFile[pixIdxArrow]);
    targetArrowName =  infoArrow.fileName();

    //Display cue image
    QPixmap cuePix(imagePathsCue[pixIdxCue]);
    pixCue = cuePix;

    //Display arrow image
    QPixmap arrowPix(arrowPixFile[pixIdxArrow]);
    pixArrow = arrowPix;

    // Debug
    //qDebug() << file;
    //qDebug() << arrowPixFile;
    qDebug() << imagePathsCue[pixIdxCue];
    qDebug() << arrowPixFile[pixIdxArrow];
}
