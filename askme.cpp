#include "askme.h"
#include "ui_askme.h"
#include "asignatura.h"
#include "tema.h"
#include "apunteform.h"
#include "tabladialogo.h"  // Incluimos el encabezado de TablaDialogo
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

Askme::Askme(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Askme)
{
    ui->setupUi(this);
    cargarDatos();

    connect(ui->actionGuardar, &QAction::triggered, this, &Askme::guardar);
    connect(ui->actionLista, &QAction::triggered, this, &Askme::mostrarLista);  // Conexión de Lista a mostrarLista
}

Askme::~Askme()
{
    delete ui;
}

void Askme::cargarDatosDesdeCSV(const QString &archivoCSV)
{
    QFile archivo(archivoCSV);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Manejar el error si no se puede abrir el archivo
        qDebug() << "Error al abrir el archivo CSV.";
        return;
    }

    QTextStream stream(&archivo);
    while (!stream.atEnd())
    {
        QString linea = stream.readLine();
        QStringList campos = linea.split('\,'); // asumiendo que el CSV está separado por tabulaciones

        if (campos.size() >= 3) // Asegurarse de tener al menos 3 campos: nombre asignatura, nombre tema, término
        {
            QString nombreAsignatura = campos[0];
            QString nombreTema = campos[1];
            QString termino = campos[2];

            // Buscar la asignatura
            Asignatura *asignatura = nullptr;
            for (Asignatura *a : m_asignaturas)
            {
                if (a->nombre() == nombreAsignatura)
                {
                    asignatura = a;
                    break;
                }
            }

            // Si no existe la asignatura, crearla
            if (!asignatura)
            {
                asignatura = new Asignatura(nombreAsignatura);
                m_asignaturas.append(asignatura);
            }

            // Buscar el tema
            Tema *tema = nullptr;
            for (Tema *t : asignatura->temas())
            {
                if (t->nombre() == nombreTema)
                {
                    tema = t;
                    break;
                }
            }

            // Si no existe el tema, crearlo
            if (!tema)
            {
                tema = new Tema(nombreTema);
                asignatura->agregarTema(tema);
            }

            // Crear apunte y agregarlo al tema
            Apunte *apunte = new Apunte(termino, ""); // Puedes modificarlo para incluir el concepto
            tema->agregarApunte(apunte);
        }
    }

    archivo.close();
}

void Askme::mostrarLista()
{
    if (!tablaModel) {
        tablaModel = new TableList(this);
        tablaModel->setDatos(obtenerAsignaturas());
    }

    TablaDialogo *dlg = new TablaDialogo(obtenerAsignaturas(), this);
    dlg->exec();
}


QList<Asignatura*> Askme::obtenerAsignaturas() const
{
    QList<Asignatura*> asignaturas;
    for (const Asignatura* asignatura : m_asignaturas) {
        asignaturas.append(new Asignatura(*asignatura));  // Copia de asignatura
    }
    return asignaturas;
}

Tema *Askme::encontrarTema(Asignatura *asignatura, const QString &nombre)
{
    foreach (Tema *tema, asignatura->temas()) {
        if (tema->nombre() == nombre) {
            return tema;
        }
    }
    return nullptr;
}

void Askme::cargarDatos()
{
     cargarDatosDesdeCSV("C:/Users/10/Downloads/Apuntes_Test.csv");
}

void Askme::cargarSubVentana(QWidget *ventana)
{
    auto sub = ui->mdiArea->addSubWindow(ventana);
    sub->show();
}

void Askme::on_actionNuevo_triggered()
{
    ApunteForm *w = new ApunteForm(this);
    w->setAsignaturas(m_asignaturas);
    w->cargarAsignaturas();

    cargarSubVentana(w);
}

void Askme::on_actionGuardar_triggered()
{
    QString archivoCSV = QFileDialog::getSaveFileName(this, "Guardar como CSV", "", "Archivos CSV (*.csv)");
    if (!archivoCSV.isEmpty()) {
        guardar();
    }
}

void Askme::guardar()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Guardar como CSV", "", "Archivos CSV (*.csv)");

    if (filePath.isEmpty()) {
        return; // El usuario canceló la operación
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error al guardar", "No se pudo abrir el archivo para escribir.");
        return;
    }

    QTextStream stream(&file);

    for (const Asignatura *asignatura : m_asignaturas) {
        for (const Tema *tema : asignatura->temas()) {
            for (const Apunte *apunte : tema->apuntes()) {
                // Escribir datos
                stream << asignatura->nombre() << ","
                       << tema->nombre() << ","
                       << apunte->termino() << ","
                       << apunte->concepto() << "\n";
            }
        }
    }

    file.close();
}

