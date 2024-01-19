// datossingleton.h
#ifndef DATOSSINGLETON_H
#define DATOSSINGLETON_H

#include <QList>
#include "asignatura.h"

class DatosSingleton
{
public:
    static DatosSingleton& getInstance();

    void cargarDatosDesdeCSV(const QString &filePath);
    const QList<Asignatura *> &getAsignaturas() const;

private:
    QList<Asignatura*> m_asignaturas;

    DatosSingleton(); // Constructor privado para evitar instancias múltiples
    ~DatosSingleton();
    DatosSingleton(const DatosSingleton&) = delete;
    DatosSingleton& operator=(const DatosSingleton&) = delete;

    void agregarAsignatura(Asignatura *asignatura);
};

#endif // DATOSSINGLETON_H
