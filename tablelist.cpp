#include "tablelist.h"

TableList::TableList(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableList::~TableList()
{
}

void TableList::setDatos(const QList<Asignatura *> &asignaturas)
{
    beginResetModel();
    m_asignaturas = asignaturas;
    endResetModel();
}

int TableList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    int rowCount = 0;

    for (const Asignatura *asignatura : m_asignaturas) {
        rowCount += asignatura->temas().size();
    }

    return rowCount;
}

int TableList::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 4;
}

QVariant TableList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        int temaIndex = index.row();
        int asignaturaIndex = 0;

        // Encuentra la asignatura y tema correspondientes al índice
        for (const Asignatura *asignatura : m_asignaturas) {
            if (temaIndex < asignatura->temas().size()) {
                break;
            }

            temaIndex -= asignatura->temas().size();
            ++asignaturaIndex;
        }

        const Asignatura *asignatura = m_asignaturas[asignaturaIndex];
        const Tema *tema = asignatura->temas()[temaIndex];

        // Ajusta esto según la información que quieras mostrar
        switch (index.column()) {
        case 0:
            return asignatura->nombre();
        case 1:
            return tema->nombre();
        case 2:
            return tema->apuntes().at(0)->termino(); // Ejemplo, mostrar el término del primer apunte
        case 3:
            return tema->apuntes().at(0)->concepto(); // Ejemplo, mostrar el concepto del primer apunte
        }
    }

    return QVariant();
}

QVariant TableList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        // Ajusta esto según los encabezados que quieras mostrar
        switch (section) {
        case 0:
            return tr("Asignatura");
        case 1:
            return tr("Tema");
        case 2:
            return tr("Término");
        case 3:
            return tr("Concepto");
        }
    }

    return QVariant();
}
