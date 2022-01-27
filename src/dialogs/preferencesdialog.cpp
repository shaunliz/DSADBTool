#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    makeConnect();
    initialize();
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::clickedSelectAdbSlot()
{
    QStringList strListPaths = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    QString filePath = QFileDialog::getOpenFileName(this, "Select adb.exe File.", strListPaths.first(), "adb.exe File(*.exe)");

    if(!filePath.isEmpty() && filePath.compare("") != 0)
        ui->lineEditAdbPath->setText(filePath);
}

void PreferencesDialog::initialize()
{
    if(IniManager::GetInstance()->getUseAdbPath())
    {
        ui->gbUsingAdb->setChecked(true);
        ui->lineEditAdbPath->setText(IniManager::GetInstance()->getAdbPath());
    }
    else
    {
        ui->gbUsingAdb->setChecked(false);
        ui->lineEditAdbPath->setText(IniManager::GetInstance()->getAdbPath());
    }
}

void PreferencesDialog::makeConnect()
{
    connect(ui->btnSelectAdb, SIGNAL(clicked()), this, SLOT(clickedSelectAdbSlot()));
}

void PreferencesDialog::accept()
{
    qDebug() << __FUNCTION__;

    /* adb file path */
    if(ui->gbUsingAdb->isChecked())
    {
        IniManager::GetInstance()->setUseAdbPath(true);
        IniManager::GetInstance()->setAdbPath(ui->lineEditAdbPath->text());
    }
    else
    {
        IniManager::GetInstance()->setUseAdbPath(false);
    }

    QDialog::accept();
}
