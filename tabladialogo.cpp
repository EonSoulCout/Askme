// tabladialogo.cpp

#include "tabladialogo.h"
#include "ui_tabladialogo.h"
#include <QFileDialog>
#include <QTextStream>

TablaDialogo::TablaDialogo(const QList<Asignatura *> &asignaturas, QWidget *parent)
    : QDialog(parent), ui(new Ui::TablaDialogo), m_asignaturas(asignaturas)
{
    ui->setupUi(this);

    // Configuramos la tabla para usar el modelo
    ui->tblApunt->setRowCount(0);
    ui->tblApunt->setColumnCount(4);

    // Configuramos los encabezados de la tabla
    QStringList encabezados = {"Asignatura", "Tema", "Término", "Concepto"};
    ui->tblApunt->setHorizontalHeaderLabels(encabezados);

    // Inicialmente cargamos la tabla
    cargarTabla();

    connect(ui->btnRefresh, &QPushButton::clicked, this, &TablaDialogo::actualizarTabla);
}

TablaDialogo::~TablaDialogo()
{
    delete ui;
}

void TablaDialogo::cargarTabla()
{
    ui->tblApunt->setRowCount(0); // Limpiar la tabla

    // Llenar la tabla con datos de asignaturas
    for (const Asignatura *asignatura : m_asignaturas)
    {
        for (const Tema *tema : asignatura->temas())
        {
            for (const Apunte *apunte : tema->apuntes())
            {
                int fila = ui->tblApunt->rowCount();
                ui->tblApunt->insertRow(fila);

                // Insertar datos en las celdas
                ui->tblApunt->setItem(fila, 0, new QTableWidgetItem(asignatura->nombre()));
                ui->tblApunt->setItem(fila, 1, new QTableWidgetItem(tema->nombre()));
                ui->tblApunt->setItem(fila, 2, new QTableWidgetItem(apunte->termino()));
                ui->tblApunt->setItem(fila, 3, new QTableWidgetItem(apunte->concepto()));
            }
        }
    }
}

void TablaDialogo::actualizarTabla()
{
    // Recargar datos desde CSV y actualizar el modelo
    QString archivoCSV = QFileDialog::getOpenFileName(this, "Seleccionar archivo CSV", "", "Archivos CSV (*.csv)");
    if (!archivoCSV.isEmpty()) {
        cargarDatosDesdeCSV(archivoCSV);
        cargarTabla();
    }
}

void TablaDialogo::cargarDatosDesdeCSV(const QString &archivoCSV)
{
    // Cargamos datos desde el archivo CSV y actualizamos el modelo
    if (!archivoCSV.isEmpty()) {

    }
}
