#ifndef ASKME_H
#define ASKME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Askme; }
QT_END_NAMESPACE

class Askme : public QMainWindow
{
    Q_OBJECT

public:
    Askme(QWidget *parent = nullptr);
    ~Askme();

private:
    Ui::Askme *ui;
};
#endif // ASKME_H
