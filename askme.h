#ifndef ASKME_H
#define ASKME_H

#include <QMainWindow>
#include <QMdiSubWindow>

#include "apunteform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Askme; }
QT_END_NAMESPACE

class Askme : public QMainWindow
{
    Q_OBJECT

public:
    Askme(QWidget *parent = nullptr);
    ~Askme();

private slots:
    void on_actionNuevo_triggered();

private:
    Ui::Askme *ui;
    void loadSubWindow(QWidget *ventana);
};
#endif // ASKME_H
