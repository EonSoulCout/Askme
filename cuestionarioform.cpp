#include <QMessageBox>

#include "cuestionarioform.h"
#include "resultadosform.h"

#include "ui_cuestionarioform.h"

CuestionarioForm::CuestionarioForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CuestionarioForm)
{
    ui->setupUi(this);
}

CuestionarioForm::~CuestionarioForm()
{
    delete ui;
}

void CuestionarioForm::setAsignaturas(QList<Asignatura *> &asignaturas)
{
    m_asignaturas = &asignaturas;
}

void CuestionarioForm::cargarAsignaturas()
{
    ui->cmbAsignaturas->clear();
    foreach (Asignatura *a, *m_asignaturas) {
        ui->cmbAsignaturas->addItem(a->nombre());
    }
}

void CuestionarioForm::on_cmbAsignaturas_currentIndexChanged(int index)
{
    ui->cmbTemas->clear();
    if (index >= 0 && index < m_asignaturas->size()) {
        Asignatura *a = m_asignaturas->at(index);
        foreach (Tema *t, a->temas()) {
            ui->cmbTemas->addItem(t->nombre());
        }
    }
}

void CuestionarioForm::on_buttonBox_accepted()
{
    // Obtener los índices de los combos
    int indexAsignatura = ui->cmbAsignaturas->currentIndex();
    int indexTema = ui->cmbTemas->currentIndex();

    // Validar que se haya seleccionado asignatura y tema
    if (indexAsignatura < 0 || indexTema < 0) {
        QMessageBox::warning(this, "Advertencia", "Por favor, seleccione una asignatura y un tema antes de iniciar.");
        return;
    }

    QString asignatura = ui->cmbAsignaturas->currentText();
    // Crear la tarea
    Tema *t = m_asignaturas->at(indexAsignatura)->temas().at(indexTema);

    // Emitir señal
    emit cuestionarioCreado(new Cuestionario(asignatura, t));

    PreguntaForm *preguntaForm = new PreguntaForm(this);
    preguntaForm->setCuestionario(new Cuestionario(asignatura, t));
    preguntaForm->show();

    // Cerrar la ventana actual
    this->parentWidget()->close();
}


