// tabladialogo.h

#ifndef TABLADIALOGO_H
#define TABLADIALOGO_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include "asignatura.h"
#include "tablelist.h"

namespace Ui {
class TablaDialogo;
}

class TablaDialogo : public QDialog
{
    Q_OBJECT

public:
    explicit TablaDialogo(const QList<Asignatura *> &asignaturas, QWidget *parent = nullptr);
    ~TablaDialogo();

private slots:
    void actualizarTabla();
    void cargarDatosDesdeCSV(const QString &archivoCSV);

private:
    Ui::TablaDialogo *ui;
    QList<Asignatura *> m_asignaturas;
    TableList *tablaModel;

    void cargarTabla();
};

#endif // TABLADIALOGO_H
