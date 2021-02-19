#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QPixmap>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/img/logo_ut.png");
    ui->label_2->setPixmap(pix);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    QString userID = ui->lineEdit_userID->text();
    if (userID.isEmpty()) {
        QMessageBox::critical(this, "Error", "被験者IDが入力されていません");
    } else {
        int ret = QMessageBox::question(this, "Confirm", ("被験者IDは" + userID + "で正しいですか？"),
                                        QMessageBox::No | QMessageBox::Yes);

        switch (ret) {
        case QMessageBox::Yes:
            // No was clicked
            hide();
            mainWindow = new MainWindow(this);
            mainWindow->userID = userID;
            mainWindow->initialize();
            mainWindow->show();
              break;
        case QMessageBox::No:
            // No was clicked
            break;
        default:
            // should never be reached
            break;
        }
    }
}
