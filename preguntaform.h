#ifndef PREGUNTAFORM_H
#define PREGUNTAFORM_H

#include <QWidget>

#include "cuestionario.h"

namespace Ui {
class PreguntaForm;
}

class PreguntaForm : public QWidget
{
    Q_OBJECT

public:
    explicit PreguntaForm(QWidget *parent = nullptr);
    ~PreguntaForm();

    void setCuestionario(Cuestionario *newCuestionario);

private slots:
    void finalizarCuestionario();
    void siguiente();
    void cargarDatos();
    void obtenerPregunta();

    // Slots conectados a los botones en el formulario
    void on_btnEnd_released();
    void on_btnNext_released();

private:
    Ui::PreguntaForm *ui;
    Cuestionario *m_cuestionario;
    Pregunta *m_pregunta;
    QString m_asignatura;
    QString m_tema;
};

#endif // PREGUNTAFORM_H
