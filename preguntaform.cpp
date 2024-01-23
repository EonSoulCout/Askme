#include "preguntaform.h"
#include "resultadosform.h"

#include "ui_preguntaform.h"

#include "pregunta.h"

PreguntaForm::PreguntaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreguntaForm)
{
    ui->setupUi(this);
}

PreguntaForm::~PreguntaForm()
{
    delete ui;
}

void PreguntaForm::setCuestionario(Cuestionario *newCuestionario)
{
    m_cuestionario = newCuestionario;
    cargarDatos();
}

void PreguntaForm::cargarDatos()
{
    ui->lblTema->setText(m_cuestionario->nombreTema());
    ui->cmbTerminos->addItems(m_cuestionario->terminos());
    obtenerPregunta();
}

void PreguntaForm::siguiente()
{
    QString termino = ui->cmbTerminos->currentText();
    m_pregunta->responder(termino);
    obtenerPregunta();
}

void PreguntaForm::obtenerPregunta()
{
    m_pregunta = m_cuestionario->siguiente();

    if (m_pregunta) {
        ui->txtConcepto->setText(m_pregunta->apunte()->concepto());
        int actual = m_cuestionario->mostradas();
        int total = m_cuestionario->totalPreguntas();
        ui->lblContador->setText(QString::number(actual) + " / " + QString::number(total));
    } else {
        ui->txtConcepto->setText("**** FIN DEL CUESTIONARIO ***");
    }
}

void PreguntaForm::finalizarCuestionario()
{

}

void PreguntaForm::on_btnEnd_released()
{
    m_cuestionario->terminar();
    emit cuestionarioFinalizado(m_cuestionario);
    finalizarCuestionario();
    this->parentWidget()->close();
}

void PreguntaForm::on_btnNext_released()
{
    siguiente();
}
