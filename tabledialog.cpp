#include "tabledialog.h"

TableDialog::TableDialog(const QList<Asignatura *> &asignaturas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableDialog)
{
    ui->setupUi(this);

    tablaModel = new TableList(this);
    tablaModel->setDatos(asignaturas);

    ui->tblApunt->setModel(tablaModel);

    connect(ui->btnRefresh, &QPushButton::clicked, this, &TableDialog::on_btnRefresh_clicked);
}

TableDialog::~TableDialog()
{
    delete ui;
}

void TableDialog::on_btnRefresh_clicked()
{
    // Aquí puedes escribir la lógica para actualizar la tabla cuando se hace clic en el botón Refresh
    // Puedes llamar a tablaModel->setDatos(...) para actualizar los datos en la tabla.
    // ...
}
