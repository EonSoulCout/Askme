#ifndef RESULTADOSFORM_H
#define RESULTADOSFORM_H

#include <QWidget>

#include "cuestionario.h"

namespace Ui {
class ResultadosForm;
}

class ResultadosForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResultadosForm(QWidget *parent = nullptr);
    ~ResultadosForm();

    void setCuestionario(Cuestionario *newCuestionario);

private:
    Ui::ResultadosForm *ui;
    Cuestionario *m_cuestionario;

    void cargarDatos();
    enum Columna
    {
        TERMINO, CONCEPTO, RESULTADO
    };
};

#endif // RESULTADOSFORM_H
