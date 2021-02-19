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

void ANTMain::initializeImages()
{
    imagePathsArrow = {QPixmap(":/resources/img/ANT_test/arrows/L_cong_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_cong_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_incg_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_incg_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_neut_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_neut_top.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_cong_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_cong_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_incg_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_incg_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/L_neut_bot.JPG"),
                       QPixmap(":/resources/img/ANT_test/arrows/R_neut_bot.JPG")};

    imagePathsCue = {QPixmap(":/resources/img/ANT_test/cue/cue0_non.JPG"),
                     QPixmap(":/resources/img/ANT_test/cue/cue1_cnt.JPG"),
                     QPixmap(":/resources/img/ANT_test/cue/cue2_dbl.JPG"),
                     QPixmap(":/resources/img/ANT_test/cue/cue3_top.JPG"),
                     QPixmap(":/resources/img/ANT_test/cue/cue4_bot.JPG")};
}

void ANTMain::choosePix()
{
    pixChosen = false;
    int pixIdxArrowTmp;
    int pixIdxCueTmp = rand() % 5;

    // Get random cue
    while (pixIdxCue == pixIdxCueTmp) pixIdxCueTmp = rand() % 5;
    pixIdxCue = pixIdxCueTmp;

    switch(pixIdxCue)
    {
    case 3 :
        pixIdxArrowTmp = rand() % 6;
        while (pixIdxArrow == pixIdxArrowTmp) pixIdxArrowTmp = rand() % 6;
        pixIdxArrow = pixIdxArrowTmp;
        break;
    case 4 :
        pixIdxArrowTmp = rand() % 6 + 6;
        while (pixIdxArrow == pixIdxArrowTmp) pixIdxArrowTmp = rand() % 6 + 6;
        pixIdxArrow = pixIdxArrowTmp;
        break;
    default:
        pixIdxArrowTmp = rand() % 12;
        while (pixIdxArrow == pixIdxArrowTmp) pixIdxArrowTmp = rand() % 12;
        pixIdxArrow = pixIdxArrowTmp;
        break;
    }

    if (pixIdxArrow % 2) {
        correctArrow = "R";
    } else {
        correctArrow = "L";
    }

    pixChosen = true;
}
