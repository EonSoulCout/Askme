#ifndef CUESTIONARIO_H
#define CUESTIONARIO_H

#include <tema.h>
#include <pregunta.h>

#include <QRandomGenerator>

class Cuestionario
{
public:
    Cuestionario();
    Cuestionario(QString asignatura, Tema *tema);

    Pregunta *siguiente();
    void terminar();
    const QStringList &terminos() const;

    float score() const;

    const QList<Pregunta *> &preguntas() const;
    const QString nombreTema() const;
    int totalPreguntas();
    bool hayMasPreguntas();

    int mostradas() const;
    const QString &asignatura() const;
    void setAsignatura(const QString &newAsignatura);

private:
    float m_score;
    Tema *m_tema;
    QList<Pregunta*> m_preguntas;
    QStringList m_terminos;
    QString m_asignatura;
    int m_mostradas;
};

#endif // CUESTIONARIO_H
