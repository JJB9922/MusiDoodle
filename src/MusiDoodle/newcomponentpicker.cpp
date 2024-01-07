#include "newcomponentpicker.h"
#include "ui_newcomponentpicker.h"

NewComponentPicker::NewComponentPicker(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewComponentPicker)
{
    ui->setupUi(this);
}

NewComponentPicker::~NewComponentPicker()
{
    delete ui;
}
