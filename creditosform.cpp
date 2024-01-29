#include "creditosform.h"
#include "ui_creditosform.h"


CreditosForm::CreditosForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditosForm)
{
    ui->setupUi(this);

    // Llamar a las nuevas funciones para configurar el contenido de txtAuto y txtDesa
    setAutoresInfo("Nombre de la asignatura:\nSeminario de problemas filosóficos\n\n"
                   "Profesor:\n●William Orlando Cárdenas Marin\n\n"
                   "Estudiantes:\n●Jonathan Andrés Analuisa Vargas.\n"
                   "●Juan Pablo Pauchi Cerda\n"
                   "●Jimmy Xavier Zambrano Campoverde\n"
                   "●Félix David Tulcán Coral\n"
                   "●Gustavo Rubén Quishpe Ayala\n"
                   "●Rómulo Yordan Valera Quispilaya\n"
                   "●Jennifer Nicole Játiva Erazo");

    setDesarrolladoresInfo("Nombre de la asignatura:\nProgramacion Orientada a Objetos\n\n"
                           "Desarrolladores:\n●RodrigoTufino\n"
                           "●Mateo Espinosa");
}

CreditosForm::~CreditosForm()
{
    delete ui;
}

// Implementación de las nuevas funciones
void CreditosForm::setAutoresInfo(const QString &infoAutores)
{
    ui->txtAuto->setText(infoAutores);
}

void CreditosForm::setDesarrolladoresInfo(const QString &infoDesarrolladores)
{
    ui->txtDesa->setText(infoDesarrolladores);
}
void CreditosForm::on_pushButton_released()
{
    this->parentWidget()->close();
}

