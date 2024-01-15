#ifndef ASKME_H
#define ASKME_H

#include <QMdiSubWindow>
#include <QMainWindow>
#include <QList>

#include "asignatura.h"
#include "tablelist.h"
#include "tabladialogo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Askme; }
QT_END_NAMESPACE

class Askme : public QMainWindow
{
    Q_OBJECT

public:
    Askme(QWidget *parent = nullptr);
    ~Askme();

    void cargarDatosDesdeCSV(const QString &archivoCSV);
    void mostrarLista();
    QList<Asignatura*> obtenerAsignaturas() const;
    Tema *encontrarTema(Asignatura *asignatura, const QString &nombre);
    void cargarDatos();
    void cargarSubVentana(QWidget *ventana);

private slots:
    void on_actionNuevo_triggered();
    void on_actionGuardar_triggered();
    void guardar();

private:
    Ui::Askme *ui;
    QList<Asignatura*> m_asignaturas;
    TableList *tablaModel;
};

#endif // ASKME_H

