#include "mainwindow.h"
#include "trackeditorwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <fstream>

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

void MainWindow::on_newTrackButton_pressed()
{
    close();
    trackEditorWindow = new TrackEditorWindow(this);
    trackEditorWindow->show();
}

void MainWindow::on_loadTrackButton_pressed()
{
    std::cout << "Load Track Button Pressed" << std::endl;
}

