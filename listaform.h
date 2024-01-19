#ifndef LISTAFORM_H
#define LISTAFORM_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class ListaForm;
}

class ListaForm : public QWidget
{
    Q_OBJECT

public:
    explicit ListaForm(QWidget *parent = nullptr);
    ~ListaForm();

private slots:
    void on_btnRefresh_clicked();

private:
    Ui::ListaForm *ui;
    QStandardItemModel *modeloTabla;  // Declarar el modelo aquí
    void setupTabla();
    void actualizarTabla();
};

#endif // LISTAFORM_H
