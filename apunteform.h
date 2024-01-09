#ifndef APUNTEFORM_H
#define APUNTEFORM_H

#include <QWidget>

namespace Ui {
class ApunteForm;
}

class ApunteForm : public QWidget
{
    Q_OBJECT

public:
    explicit ApunteForm(QWidget *parent = nullptr);
    ~ApunteForm();

private slots:
    void on_fontComboBox_textHighlighted(const QString &arg1);

private:
    Ui::ApunteForm *ui;
};

#endif // APUNTEFORM_H
