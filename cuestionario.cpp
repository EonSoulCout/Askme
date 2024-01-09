#include <algorithm>  // Necesario para std::shuffle
#include <random>     // Necesario para std::default_random_engine y std::random_device

#include "cuestionario.h"

Cuestionario::Cuestionario()
{

}

Cuestionario::Cuestionario(Tema *tema) : m_tema(tema)
{
    foreach (Apunte *a, m_tema->apuntes()){
        m_preguntas.append(new Pregunta(a));
        m_terminos.append(a->termino());
    }
}

Pregunta *Cuestionario::siguiente()
{
    // Mezcla aleatoria de las preguntas
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(m_preguntas.begin(), m_preguntas.end(), rng);

    // Busca la primera pregunta no respondida en la lista mezclada
    for (Pregunta *p : m_preguntas) {
        if (!p->respondida()) {
            return p;
        }
    }

    // Si todas las preguntas están respondidas, devuelve nullptr
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
