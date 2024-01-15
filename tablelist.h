#ifndef TABLELIST_H
#define TABLELIST_H

#include <QObject>
#include <QAbstractTableModel>
#include "asignatura.h"

class TableList : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableList(QObject *parent = nullptr);
    ~TableList();

    void setDatos(const QList<Asignatura *> &asignaturas);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<Asignatura *> m_asignaturas;
};

#endif // TABLELIST_H
