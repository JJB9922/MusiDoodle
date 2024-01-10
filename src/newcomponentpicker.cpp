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
    close();
    delete componentCreator;
}

void NewComponentPicker::on_chordComponentButton_clicked()
{
    TrackEditorWindow* trackEditorWindow = new TrackEditorWindow();
    ComponentFactory* componentCreator = new ChordsComponentCreator();
    trackEditorWindow->createComponent(componentCreator);
    close();
    delete componentCreator;
}


void NewComponentPicker::on_notebookComponentButton_clicked()
{
    TrackEditorWindow* trackEditorWindow = new TrackEditorWindow();
    ComponentFactory* componentCreator = new NotebookComponentCreator();
    trackEditorWindow->createComponent(componentCreator);
    close();
    delete componentCreator;
}


void NewComponentPicker::on_tabComponentButton_clicked()
{
    TrackEditorWindow* trackEditorWindow = new TrackEditorWindow();
    ComponentFactory* componentCreator = new TabComponentCreator();
    trackEditorWindow->createComponent(componentCreator);
    close();
    delete componentCreator;
}


void NewComponentPicker::on_sheetMusicComponentButton_clicked()
{
    TrackEditorWindow* trackEditorWindow = new TrackEditorWindow();
    ComponentFactory* componentCreator = new SheetMusicComponentCreator();
    trackEditorWindow->createComponent(componentCreator);
    close();
    delete componentCreator;
}

