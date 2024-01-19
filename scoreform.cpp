#include "scoreform.h"
#include "ui_scoreform.h"

ScoreForm::ScoreForm(QWidget *parent, const QString& asignatura, const QString& tema) :
    QWidget(parent),
    ui(new Ui::ScoreForm),
    m_asignatura(asignatura),
    m_tema(tema)
{
    ui->setupUi(this);

    // Conecta el botón "Cerrar" a la función correspondiente
    connect(ui->btnClose, &QPushButton::released, this, &ScoreForm::on_btnClose_released);

    // Nuevo modelo
    modelo = new QStandardItemModel();
    tabla = ui->tblScore;
    tabla->setModel(modelo);

    // Configuración de la tabla
    modelo->setColumnCount(2);
    modelo->setHorizontalHeaderLabels({"Término", "Respuesta Correcta"});

    // Configurar la información de asignatura y tema
    setAsignatura(m_asignatura);
    setTema(m_tema);
}

ScoreForm::~ScoreForm()
{
    delete ui;
}

void ScoreForm::on_btnClose_released()
{
    // Cierra la ventana
    close();
}

void ScoreForm::setAsignatura(const QString &asignatura)
{
    ui->Asig->setText(asignatura);
}

void ScoreForm::setTema(const QString &tema)
{
    ui->Tema->setText(tema);
}

void ScoreForm::setPreguntasRespondidas(int respondidas, int total)
{
    ui->Cont->setText(QString::number(respondidas) + "/" + QString::number(total));
}

void ScoreForm::setPorcentajeAciertos(float porcentaje)
{
    ui->Porc->setText(QString::number(porcentaje) + "%");
}

void ScoreForm::agregarFilaTabla(Pregunta *pregunta)
{
    int fila = modelo->rowCount();
    modelo->insertRow(fila);
    modelo->setData(modelo->index(fila, 0), pregunta->apunte()->termino());
    modelo->setData(modelo->index(fila, 1), pregunta->correcta() ? "Correcta" : "Incorrecta");
}
