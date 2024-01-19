#include "listaform.h"

#include "ui_listaform.h"

#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QStringList>

ListaForm::ListaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListaForm)
{
    ui->setupUi(this);
    setupTabla();
}

ListaForm::~ListaForm()
{
    delete ui;
}

void ListaForm::setupTabla()
{
    // Crear el modelo de la tabla
    modeloTabla = new QStandardItemModel(this);

    // Configurar las columnas
    modeloTabla->setColumnCount(4);
    modeloTabla->setHeaderData(0, Qt::Horizontal, "Asignatura");
    modeloTabla->setHeaderData(1, Qt::Horizontal, "Tema");
    modeloTabla->setHeaderData(2, Qt::Horizontal, "Término");
    modeloTabla->setHeaderData(3, Qt::Horizontal, "Concepto");

    // Configurar el modelo para la tabla
    ui->tblApuntes->setModel(modeloTabla);

    // Actualizar la tabla con los datos existentes
    actualizarTabla();
}

void ListaForm::actualizarTabla()
{
    // Limpiar el modelo actual
    modeloTabla->removeRows(0, modeloTabla->rowCount());

    // Leer datos desde el archivo CSV
    QFile file("Apuntes-Askme.csv");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("\t");

            if (fields.size() == 4) {
                // Agregar una nueva fila al modelo
                QList<QStandardItem *> rowItems;
                rowItems << new QStandardItem(fields[0]) << new QStandardItem(fields[1]) << new QStandardItem(fields[2]) << new QStandardItem(fields[3]);
                modeloTabla->appendRow(rowItems);
            }
        }
        file.close();
    }
}

void ListaForm::on_btnRefresh_clicked()
{
    // Actualizar la tabla al hacer clic en el botón de actualización
    actualizarTabla();
}
