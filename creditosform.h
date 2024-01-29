#ifndef CREDITOSFORM_H
#define CREDITOSFORM_H

#include <QWidget>

namespace Ui {
class CreditosForm;
}

class CreditosForm : public QWidget
{
    Q_OBJECT

public:
    explicit CreditosForm(QWidget *parent = nullptr);
    ~CreditosForm();

    // Funciones para configurar el contenido de txtAuto y txtDesa
    void setAutoresInfo(const QString &infoAutores);
    void setDesarrolladoresInfo(const QString &infoDesarrolladores);

private slots:
    void on_pushButton_released();

private:
    Ui::CreditosForm *ui;
};

#endif // CREDITOSFORM_H
