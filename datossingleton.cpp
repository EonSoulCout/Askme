#include "datossingleton.h"

DatosSingleton::DatosSingleton()
{

}
// datossingleton.cpp
#include "datossingleton.h"

#include <QFile>
#include <QTextStream>


DatosSingleton::~DatosSingleton()
{
    // Limpieza de memoria para evitar fugas de memoria
    qDeleteAll(m_asignaturas);
}

DatosSingleton& DatosSingleton::getInstance()
{
    static DatosSingleton instance;
    return instance;
}

void DatosSingleton::cargarDatosDesdeCSV(const QString &filePath)
{
    // Limpiar datos existentes si es necesario
    m_asignaturas.clear();

    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(",");

            if (parts.size() == 4) {  // Suponiendo que hay asignatura, tema, término y concepto
                QString asignaturaNombre = parts[0];
                QString temaNombre = parts[1];
                QString termino = parts[2];
                QString concepto = parts[3];

                Asignatura *asignatura = nullptr;
                Tema *tema = nullptr;

                // Buscar o crear la asignatura y el tema
                foreach (Asignatura *a, m_asignaturas) {
                    if (a->nombre() == asignaturaNombre) {
                        asignatura = a;
                        break;
                    }
                }

                if (!asignatura) {
                    asignatura = new Asignatura(asignaturaNombre);
                    m_asignaturas.append(asignatura);
                }

                // Buscar o crear el tema
                foreach (Tema *t, asignatura->temas()) {
                    if (t->nombre() == temaNombre) {
                        tema = t;
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
    }
}

const QList<Asignatura *> &DatosSingleton::getAsignaturas() const
{
    return m_asignaturas;
}

void DatosSingleton::agregarAsignatura(Asignatura *asignatura)
{
    m_asignaturas.append(asignatura);
}
