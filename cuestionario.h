#ifndef CUESTIONARIO_H
#define CUESTIONARIO_H

#include <tema.h>
#include <pregunta.h>

class Cuestionario
{
public:
    Cuestionario();
    Cuestionario(Tema *tema);

    Pregunta *siguiente();
    void terminar();
    const QStringList &terminos() const;

    float score() const;

    const QList<Pregunta *> &preguntas() const;

private:
    float m_score;
    Tema *m_tema;
    QList<Pregunta*> m_preguntas;
    QStringList m_terminos;
};

#endif // CUESTIONARIO_H
