#include "newcomponentpicker.h"
#include "ui_newcomponentpicker.h"

NewComponentPicker::NewComponentPicker(QWidget *parent)
    : QDialog(parent), ui(new Ui::NewComponentPicker)
{
    ui->setupUi(this);
}

NewComponentPicker::~NewComponentPicker()
{
    delete ui;
}

QString NewComponentPicker::getSelectedComponentType() const
{
    return selectedComponentType;
}

void NewComponentPicker::on_lyricComponentButton_clicked()
{
    selectedComponentType = "Lyrics";
    accept();
}

void NewComponentPicker::on_chordComponentButton_clicked()
{
    selectedComponentType = "Chords";
    accept();
}

void NewComponentPicker::on_notebookComponentButton_clicked()
{
    selectedComponentType = "Notebook";
    accept();
}

void NewComponentPicker::on_tabComponentButton_clicked()
{
    selectedComponentType = "Tab";
    accept();
}

void NewComponentPicker::on_sheetMusicComponentButton_clicked()
{
    selectedComponentType = "SheetMusic";
    accept();
}
