#include "cuestionario.h"

Cuestionario::Cuestionario()
{

}

Cuestionario::Cuestionario(QString asignatura, Tema *tema) :m_asignatura(asignatura), m_tema(tema), m_mostradas(0)
{
    foreach (Apunte *a, m_tema->apuntes()){
        m_preguntas.append(new Pregunta(a));
        m_terminos.append(a->termino());
    }
}
Pregunta *Cuestionario::siguiente()
{
    QList<Pregunta*> preguntasNoRespondidas;

    // Obtener preguntas no respondidas
    foreach (Pregunta *p, m_preguntas) {
        if (!p->respondida()) {
            preguntasNoRespondidas.append(p);
        }
    }

    // Si aún hay preguntas no respondidas, elige una al azar
    if (!preguntasNoRespondidas.isEmpty()) {
        m_mostradas++;
        int index = QRandomGenerator::global()->bounded(preguntasNoRespondidas.size());
        return preguntasNoRespondidas[index];
    }

    return nullptr;
}

void Cuestionario::terminar()
{
    int correctas = 0;
    int respondidas = 0;
    foreach(Pregunta *p, m_preguntas){
        if(p->respondida()){
            respondidas++;
            if (p->correcta())
                correctas++;
        }
    }
    if (respondidas > 0)
        m_score = (float) correctas / respondidas * 100;
    else
        m_score = 0;
}

const QStringList &Cuestionario::terminos() const
{
    return m_terminos;
}

float Cuestionario::score() const
{
    return m_score;
}

const QList<Pregunta *> &Cuestionario::preguntas() const
{
    return m_preguntas;
}

const QString Cuestionario::nombreTema() const
{
    return m_tema->nombre();
}

int Cuestionario::totalPreguntas()
{
    return m_preguntas.size();
}

bool Cuestionario::hayMasPreguntas()
{
    return (m_mostradas < totalPreguntas());
}

int Cuestionario::mostradas() const
{
    return m_mostradas;
}

const QString &Cuestionario::asignatura() const
{
    return m_asignatura;
}

void Cuestionario::setAsignatura(const QString &newAsignatura)
{
    m_asignatura = newAsignatura;
}
