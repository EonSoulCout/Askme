#ifndef ASKME_H
#define ASKME_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include "apunteform.h"
#include "cuestionarioform.h"
#include "preguntaform.h"
#include "listaform.h"
#include "resultadosform.h"
#include "creditosform.h"


#include "asignatura.h"
#include "tema.h"
#include "apunte.h"


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

    void on_cuestionarioFinalizado(Cuestionario *cuestionario);

private slots:
    void on_actionNuevo_triggered();

    void on_actionGenerar_triggered();

    void on_actionGuardar_triggered();

    void on_actionLista_triggered();

    void on_actionSalir_triggered();

    void on_actionCreditos_triggered();

private:
    Ui::Askme *ui;
    void cargarSubVentana(QWidget *ventana);
    void cargarDatos();
    void cargarApuntesDesdeCSV(const QString &filePath);

    QList<Asignatura*> m_asignaturas;
    QList<Apunte *> m_apuntes;
    Cuestionario *m_cuestionario;
    QString m_path;
    QString m_archivo;
};
#endif // ASKME_H
