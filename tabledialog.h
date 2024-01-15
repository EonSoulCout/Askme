#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QPushButton>

#include "tablelist.h"
#include "ui_tabledialog.h"

namespace Ui {
class TableDialog;
}

class TableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableDialog(const QList<Asignatura *> &asignaturas, QWidget *parent = nullptr);
    ~TableDialog();

private:
    Ui::TableDialog *ui;
    TableList *tablaModel;

private slots:
    void on_btnRefresh_clicked();
};

#endif // TABLEDIALOG_H
