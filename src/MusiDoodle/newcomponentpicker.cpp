#include "newcomponentpicker.h"
#include "trackeditorwindow.h"
#include "ui_newcomponentpicker.h"
#include "componentfactory.h"

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
    TrackEditorWindow* trackEditorWindow = new TrackEditorWindow();
    ComponentFactory* componentCreator = new LyricsComponentCreator();
    trackEditorWindow->createComponent(componentCreator);
}

void NewComponentPicker::on_chordComponentButton_clicked()
{

}

