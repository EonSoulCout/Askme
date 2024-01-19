#ifndef ASKME_H
#define ASKME_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "apunteform.h"
#include "cuestionarioform.h"
#include "preguntaform.h"
#include "listaform.h"

#include "asignatura.h"
#include "tema.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Askme; }
QT_END_NAMESPACE

class Askme : public QMainWindow
{
    Q_OBJECT

public:
    Askme(QWidget *parent = nullptr);
    ~Askme();

public slots:
    void on_cuestionarioCreado(Cuestionario *cuestionario);

private slots:
    void on_actionNuevo_triggered();

    void on_actionGenerar_triggered();

    void on_actionGuardar_triggered();

    void on_actionLista_triggered();

private:
    Ui::Askme *ui;
    void cargarSubVentana(QWidget *ventana);
    void cargarDatos();
    void cargarApuntesDesdeCSV(const QString &filePath);

    QList<Asignatura*> m_asignaturas;
    QList<Apunte *> m_apuntes;

};
#endif // ASKME_H
