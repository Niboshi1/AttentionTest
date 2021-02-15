#include "stroopmain.h"

#include <QDir>
#include <QDebug>
#include <QList>

StroopMain::StroopMain()
{
    testMode = true; // when true, answer color of words
    this->initializeImages();
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
    this->imagePathsColors = loadImagesets("C:/Users/Coral/Pictures/Stroop_test/colors");
    pixInstructionColor = QPixmap("C:/Users/Coral/Pictures/Stroop_test/instruction/answer_color.JPG");
    pixInstructionWord = QPixmap("C:/Users/Coral/Pictures/Stroop_test/instruction/answer_word.JPG");
}

void StroopMain::choosePix()
{
    QStringList colorPixFile;

    // Get random cue
    int pixIdxColor = rand() % imagePathsColors.count();
    const QFileInfo infoCue(imagePathsColors[pixIdxColor]);
    targetColorName = infoCue.fileName();

    //Display cue image
    QPixmap cueColor(imagePathsColors[pixIdxColor]);
    this->pixColor = cueColor;

    // Debug
    //qDebug() << targetColorName;
}

