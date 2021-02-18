#include "antmain.h"

#include <QDir>
#include <QDebug>
#include <QList>

ANTMain::ANTMain()
{
    QPixmap initialPix(":/resources/img/ANT_test/fixation.JPG");
    pixWait = initialPix;
    pixChosen = false;
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
    imagePathsArrow = loadImagesets(":/resources/img/ANT_test/arrows/");
    imagePathsCue = loadImagesets(":/resources/img/ANT_test/cue");
}

void ANTMain::choosePix()
{
    pixChosen = false;
    QStringList arrowPixFile;

    // Get random cue
    int pixIdxCue = rand() % imagePathsCue.count();
    QFileInfo infoCue(imagePathsCue[pixIdxCue]);
    QString file(infoCue.fileName());

    // if file is same as previous
    while (targetCueName==file){
        int pixIdxCue = rand() % imagePathsCue.count();
        infoCue = imagePathsCue[pixIdxCue];
        file = infoCue.fileName();
    }
    targetCueName = file;

    // Choose which arrow to show
    if (file == "cue3_top.JPG") {
        arrowPixFile = imagePathsArrow.filter("top");
    } else if (file == "cue4_bot.JPG") {
        arrowPixFile = imagePathsArrow.filter("bot");
    } else {
        arrowPixFile = imagePathsArrow;
    }

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
    qDebug() << targetCueName;
    qDebug() << targetArrowName;
    qDebug() << arrowPixFile;

    pixChosen = true;
}
