#include "preguntaform.h"
#include "scoreform.h"

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
    // Supongamos que m_cuestionario es la instancia de tu clase Cuestionario
    m_cuestionario->terminar();  // Asegúrate de tener un método terminar() en Cuestionario

    // Crear instancia de ScoreForm con nullptr como padre
    ScoreForm *scoreForm = new ScoreForm(nullptr);

    // Configurar la información en ScoreForm (asignatura, tema, etc.)
    scoreForm->setAsignatura(m_asignatura);  // Agrega m_asignatura como miembro de la clase
    scoreForm->setTema(m_tema);  // Agrega m_tema como miembro de la clase
    scoreForm->setPreguntasRespondidas(m_cuestionario->mostradas(), m_cuestionario->totalPreguntas());  // Utiliza el método correcto
    scoreForm->setPorcentajeAciertos(m_cuestionario->score());  // Reemplaza con la información correcta

    // Agregar filas a la tabla con la información de cada pregunta
    for (const auto& pregunta : m_cuestionario->preguntas()) {
        scoreForm->agregarFilaTabla(pregunta);
    }

    // Mostrar la ventana de ScoreForm
    scoreForm->show();
}

void PreguntaForm::on_btnEnd_released()
{
    finalizarCuestionario();
    close();
}

void PreguntaForm::on_btnNext_released()
{
    siguiente();
}
