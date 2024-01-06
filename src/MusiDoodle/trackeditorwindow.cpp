#include "trackeditorwindow.h"
#include "ui_trackeditorwindow.h"
#include <QtWidgets>

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
    saveToFile();
}

void TrackEditorWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Track"),
                                                    "",
                                                    tr("Track (*.tr);;All Files (*)"));


}

