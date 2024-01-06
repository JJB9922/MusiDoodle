#include "trackeditorwindow.h"
#include "ui_trackeditorwindow.h"

TrackEditorWindow::TrackEditorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrackEditorWindow)
{
    ui->setupUi(this);
}

TrackEditorWindow::~TrackEditorWindow()
{
    delete ui;
}

void TrackEditorWindow::on_actionQuit_triggered()
{
    close();
}


void TrackEditorWindow::on_actionSave_As_triggered()
{

}

