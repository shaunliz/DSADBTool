#ifndef LOGPROXYMODEL_H
#define LOGPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QObject>
#include <QDebug>

#include "const.h"
#include "filtermanager.h"

using namespace DSADB_TOOL;

class LogProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    LogProxyModel(QObject* parent = 0);
    LogProxyModel(FilterManager* filterMgr, QObject* parent = 0);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

public slots:
    void updateFilterSlot();
    void pidTextChangedSlot(QString strPid);
    void tidTextChangedSlot(QString strPid);

private:
    FilterManager* mFilterMgr;

};

#endif // LOGPROXYMODEL_H
