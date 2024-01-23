#include "resultadosform.h"
#include "ui_resultadosform.h"

ResultadosForm::ResultadosForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultadosForm)
{
    ui->setupUi(this);

    ui->tblResultados->setColumnCount(3);
    QStringList titulo;
    titulo << "Término" << "Concepto" << "Correcto";
    ui->tblResultados->setHorizontalHeaderLabels(titulo);
}

ResultadosForm::~ResultadosForm()
{
    delete ui;
}

void ResultadosForm::setCuestionario(Cuestionario *newCuestionario)
{
    m_cuestionario = newCuestionario;

    cargarDatos();
}

void ResultadosForm::cargarDatos()
{
    // Mostrar el tema
    QString tema = m_cuestionario->nombreTema();
    ui->lblTema->setText(tema);
    // Mostrar el score
    double score = m_cuestionario->score();
    ui->lblScore->setText(QString::number(score) + " %");
    // Mostrar la asignatura
    QString asignatura = m_cuestionario->asignatura();
    ui->lblAsignatura->setText(asignatura);
    // cargar la tabla de preguntas respondidas
    foreach(Pregunta *p, m_cuestionario->preguntas()){
        if (p->respondida()){
            //Agregar a la tabla
            int fila = ui->tblResultados->rowCount();
            ui->tblResultados->insertRow(fila);
            ui->tblResultados->setItem(fila, TERMINO, new QTableWidgetItem(p->apunte()->termino()));
            ui->tblResultados->setItem(fila, CONCEPTO, new QTableWidgetItem(p->apunte()->concepto()));
            QString correcta = "SI";
            if (!p->correcta())
                correcta = "NO";
            ui->tblResultados->setItem(fila, RESULTADO, new QTableWidgetItem(correcta));
        }
    }
}
