#include "askme.h"
#include "ui_askme.h"

Askme::Askme(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Askme)
{
    ui->setupUi(this);
}

Askme::~Askme()
{
    delete ui;
}

void Askme::loadSubWindow(QWidget *ventana)
{
    auto sub = ui->mdiArea->addSubWindow(ventana);
    sub->show();

}


void Askme::on_actionNuevo_triggered()
{
    loadSubWindow(new ApunteForm(this));
}

