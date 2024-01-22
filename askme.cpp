#include "askme.h"
#include "ui_askme.h"

Askme::Askme(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Askme)
{
    ui->setupUi(this);
}

Askme::~Askme()
{
    delete ui;
}

void Askme::on_cuestionarioCreado(Cuestionario *cuestionario)
{
    PreguntaForm *w = new PreguntaForm(this);
    w->setCuestionario(cuestionario);

    cargarSubVentana(w);
}

void Askme::cargarSubVentana(QWidget *ventana)
{
    auto sub = ui->mdiArea->addSubWindow(ventana);
    sub->show();
}

void Askme::cargarDatos()
{

    QString filePath = QFileDialog::getOpenFileName(this, "Seleccionar archivo CSV", "", "Archivos CSV (*.csv)");

     if (!filePath.isEmpty()) {
         cargarApuntesDesdeCSV(filePath);
     } else {
         qDebug() << "No se seleccionó ningún archivo CSV.";
     }
}

void Askme::cargarApuntesDesdeCSV(const QString &filePath)
{
    QFile file(filePath);

     if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
         QTextStream stream(&file);

         while (!stream.atEnd()) {
             QString line = stream.readLine();
             QStringList parts = line.split("\t");

             if (parts.size() == 4) {
                 QString asignaturaNombre = parts[0];
                 QString temaNombre = parts[1];
                 QString termino = parts[2];
                 QString concepto = parts[3];

                 // Buscar la asignatura o crearla si no existe
                 Asignatura *asignatura = nullptr;
                 for (auto existingAsignatura : m_asignaturas) {
                     if (existingAsignatura->nombre() == asignaturaNombre) {
                         asignatura = existingAsignatura;
                         break;
                     }
                 }

                 if (!asignatura) {
                     asignatura = new Asignatura(asignaturaNombre);
                     m_asignaturas.append(asignatura);
                 }

                 // Buscar el tema o crearlo si no existe
                 Tema *tema = nullptr;
                 for (auto existingTema : asignatura->temas()) {
                     if (existingTema->nombre() == temaNombre) {
                         tema = existingTema;
                         break;
                     }
                 }

                 if (!tema) {
                     tema = new Tema(temaNombre);
                     asignatura->agregarTema(tema);
                 }

                 // Crear y agregar el apunte al tema
                 Apunte *apunte = new Apunte(termino, concepto);
                 tema->agregarApunte(apunte);
             }
         }

         file.close();
     } else {
         qDebug() << "Error al abrir el archivo CSV para lectura";
     }
}

void Askme::on_actionNuevo_triggered()
{
    ApunteForm *w = new ApunteForm(this);
    w->setAsignaturas(m_asignaturas);
    w->cargarAsignaturas();

    connect(w, SIGNAL(apunteTomado(Apunte*)), this, SLOT(on_apunteTomado(Apunte*)));

    cargarSubVentana(w);
}


void Askme::on_actionGenerar_triggered()
{
    CuestionarioForm *w = new CuestionarioForm(this);
    w->setAsignaturas(m_asignaturas);
    w->cargarAsignaturas();

    connect(w, SIGNAL(cuestionarioCreado(Cuestionario*)), this, SLOT(on_cuestionarioCreado(Cuestionario*)));

    cargarSubVentana(w);
}


void Askme::on_actionGuardar_triggered()
{
    QString defaultFileName = "Apuntes-Askme";
    QString filePath = QFileDialog::getSaveFileName(this, "Guardar Apuntes como CSV", defaultFileName, "Archivos CSV (*.csv)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);

            // Recorrer todas las asignaturas y temas
            for (auto asignatura : m_asignaturas) {
                for (auto tema : asignatura->temas()) {
                    for (auto apunte : tema->apuntes()) {
                        stream << asignatura->nombre() << "\t" << tema->nombre() << "\t";
                        stream << apunte->termino() << "\t" << apunte->concepto() << "\n";
                    }
                }
            }

            file.close();
        } else {
            qDebug() << "Error al abrir el archivo para escritura";
        }
    }
}


void Askme::on_actionLista_triggered()
{
    cargarDatos();
    ListaForm *w = new ListaForm(this);
    cargarSubVentana(w);
}

void Askme::on_actionSalir_triggered()
{
    -close();
    return;
}

