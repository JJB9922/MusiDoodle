#include "trackeditorwindow.h"
#include "ui_trackeditorwindow.h"
#include "newcomponentpicker.h"
#include "componentfactory.h"

#include <iostream>
#include <string>
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

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        //out << track; //still need to define track data
    }
}

void TrackEditorWindow::on_addComponentButton_clicked()
{
    NewComponentPicker newComponentPicker;
    newComponentPicker.setModal(true);
    newComponentPicker.exec();
    auto button = findChild<QPushButton*>("addComponentButton");

    if (button) {
        auto buttonPos = button->geometry().topLeft();
        std::cout << buttonPos.x() << std::endl;
        std::cout << buttonPos.y() << std::endl;
    }

}

void TrackEditorWindow::createComponent(ComponentFactory* componentCreator){
    componentCreator->ComponentFactory::CreateComponent();
}
