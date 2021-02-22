#include "stroopmain.h"

#include <QDir>
#include <QDebug>
#include <QList>

StroopMain::StroopMain()
{
    initializeImages();
}

QStringList StroopMain::loadImagesets(QString dirName)
{
    QDir dir(dirName);
    QStringList imagePaths;
    qDebug() << "Loading from: " << dirName;
    QStringList fileNames = dir.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
    for (int i=0; i<fileNames.count(); i++)
        imagePaths << dir.absoluteFilePath(fileNames[i]);

    return imagePaths;
}

void StroopMain::initializeImages()
{
    imagePathsPatch = loadImagesets(":/resources/img/Stroop_test/colorPatch");
    imagePathsWords = loadImagesets(":/resources/img/Stroop_test/words");
    imagePathsCwords = loadImagesets(":/resources/img/Stroop_test/colorWords");
    imagePathsCwords2 = loadImagesets(":/resources/img/Stroop_test/colorWords2");
    pixInstructionColor = QPixmap(":/resources/img/Stroop_test/instruction/answer_color.JPG");
    pixInstructionWord = QPixmap(":/resources/img/Stroop_test/instruction/answer_word.JPG");
    pixInstructionCword = QPixmap(":/resources/img/Stroop_test/instruction/answer_cword.JPG");
}

void StroopMain::choosePix(int testmode)
{
    QStringList colorPixFile;

    if (testmode==0){
        colorPixFile = imagePathsPatch;
    } else if (testmode==1) {
        colorPixFile = imagePathsWords;
    } else if (testmode==2) {
        colorPixFile = imagePathsCwords;
    } else if (testmode==3) {
        colorPixFile = imagePathsCwords2;
    }

    // Get random cue
    int pixIdxColor = rand() % colorPixFile.count();
    QFileInfo infoCue(colorPixFile[pixIdxColor]);

    while (targetColorName == infoCue.fileName()) {
        pixIdxColor = rand() % colorPixFile.count();
        infoCue = colorPixFile[pixIdxColor];
    }
    targetColorName = infoCue.fileName();

    //Display cue image
    QPixmap pixDisplay(colorPixFile[pixIdxColor]);
    pixColor = pixDisplay;

    // Debug
    //qDebug() << targetColorName;
}

