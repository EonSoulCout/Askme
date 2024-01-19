#ifndef SCOREFORM_H
#define SCOREFORM_H

#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QStandardItemModel>
#include "pregunta.h"

namespace Ui {
class ScoreForm;
}

class ScoreForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreForm(QWidget *parent = nullptr, const QString& asignatura = "", const QString& tema = "");
    ~ScoreForm();

    void setAsignatura(const QString &asignatura);
    void setTema(const QString &tema);
    void setPreguntasRespondidas(int respondidas, int total);
    void setPorcentajeAciertos(float porcentaje);

public slots:
    void agregarFilaTabla(Pregunta *pregunta);

private slots:
    void on_btnClose_released();

private:
    Ui::ScoreForm *ui;
    QTableView *tabla;
    QStandardItemModel *modelo; // Nuevo modelo
    QString m_asignatura;
    QString m_tema;
};

#endif // SCOREFORM_H
