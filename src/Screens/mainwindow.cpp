#include "mainwindow.h"
#include "trackeditorwindow.h"
#include "../QTUiFiles/ui_mainwindow.h"
#include <iostream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if (trackEditorWindow != nullptr) {
        delete trackEditorWindow;
    }
    delete ui;
}

void MainWindow::on_newTrackButton_clicked()
{
    close();
    delete ui;
    trackEditorWindow = new TrackEditorWindow(this);
    trackEditorWindow->show();
}

void MainWindow::on_loadTrackButton_clicked()
{
    loadFromFile();
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Track"), "",
                                                    tr("Track (*.tr);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        close();
        trackEditorWindow = new TrackEditorWindow(this);
        trackEditorWindow->show();
        trackEditorWindow->loadTrackData(file.readAll());
    }
}

void MainWindow::on_pushButton_clicked()
{
    QCoreApplication::quit();
}

