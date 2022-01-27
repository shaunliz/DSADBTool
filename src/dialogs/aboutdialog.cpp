#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QString str = QString();

    str += ".Version : 1.0 \n";
    str += "\n";
    str += ".Develoer : \n";
    str += "\n";
    str += ".License : LGPLv3 \n";

    ui->textEdit->setText(str);
    ui->textEdit->setReadOnly(true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
