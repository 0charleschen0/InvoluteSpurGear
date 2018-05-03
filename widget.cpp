#include "widget.h"
#include "ui_Main.h"
#include "SpurGear.h"

Widget::Widget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Form) {

    ui->setupUi(this);
    setAdvancedAttributesVisible(false);

    connect(ui->advancedCheckBox, SIGNAL(stateChanged(int)),
            SLOT(on_advanced_checkBox_stateChanged(int)));
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_advanced_checkBox_stateChanged(int status) {
    switch (status) {
        case Qt::Unchecked: {
            setAdvancedAttributesVisible(false);
        break;
        }
        case Qt::Checked: {
            setAdvancedAttributesVisible(true);
        break;
        }
        default:
            //Do Nothing
        break;
    }
}

void Widget::setAdvancedAttributesVisible(bool isVisible) {
    ui->filletRadiusLabel->setVisible(isVisible);
    ui->filletRadiusDoubleSpinBox->setVisible(isVisible);
    ui->shiftLabel->setVisible(isVisible);
    ui->shiftDoubleSpinBox->setVisible(isVisible);
    ui->backlashLabel->setVisible(isVisible);
    ui->backlashDoubleSpinBox->setVisible(isVisible);
}

void Widget::on_generateButton_clicked() {
    int teethNumber = ui->teethNumberSpinBox->value();
    double module = ui->moduleDoubleSpinBox->value();
    double pressAngle = ui->pressAngleDoubleSpinBox->value();
    double filletRaduis = ui->filletRadiusDoubleSpinBox->value();
    double shift = ui->shiftDoubleSpinBox->value();
    double backlash = ui->backlashDoubleSpinBox->value();

    SpurGear::SpurGear gear = SpurGear::SpurGear(teethNumber,
                                                 module,
                                                 pressAngle,
                                                 filletRaduis,
                                                 shift,
                                                 backlash);

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Image"), QDir::currentPath(),
            tr("Image Files (*.png *.jpg *.bmp)"));

    gear.writeToPngFiles(fileName.toStdString());
}
