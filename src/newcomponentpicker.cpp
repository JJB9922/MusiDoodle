#include "newcomponentpicker.h"
#include "trackeditorwindow.h"
#include "ui_newcomponentpicker.h"
#include "componentfactory.h"

#include <iostream>

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

void NewComponentPicker::on_lyricComponentButton_clicked()
{
    LyricsComponentCreator *lyricComponent = new LyricsComponentCreator;
    lyricComponent->CreateComponent();
    close();
    delete lyricComponent;
}

void NewComponentPicker::on_chordComponentButton_clicked()
{
    ComponentFactory* componentCreator = new ChordsComponentCreator();
    close();
    delete componentCreator;
}


void NewComponentPicker::on_notebookComponentButton_clicked()
{
    ComponentFactory* componentCreator = new NotebookComponentCreator();
    close();
    delete componentCreator;
}


void NewComponentPicker::on_tabComponentButton_clicked()
{
    ComponentFactory* componentCreator = new TabComponentCreator();
    close();
    delete componentCreator;
}


void NewComponentPicker::on_sheetMusicComponentButton_clicked()
{
    ComponentFactory* componentCreator = new SheetMusicComponentCreator();
    close();
    delete componentCreator;
}

