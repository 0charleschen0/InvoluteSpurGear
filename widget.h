#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
QT_END_NAMESPACE

namespace Ui {
class Form;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:

public slots:

private slots:
    void on_advanced_checkBox_stateChanged(int status);

    void on_generateButton_clicked();

private:
    void setAdvancedAttributesVisible(bool isVisible);

    Ui::Form *ui;
};

#endif // WIDGET_H
