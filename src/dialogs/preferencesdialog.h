#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>

#include "inimanager.h"

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = nullptr);
    ~PreferencesDialog();

public slots:
    void clickedSelectAdbSlot();


private:
    void initialize();
    void makeConnect();
    void accept();

    Ui::PreferencesDialog *ui;
};

#endif // PREFERENCESDIALOG_H
