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
    NewComponentPicker newComponentPicker(this);
    newComponentPicker.setModal(true);
    newComponentPicker.exec();
    auto button = findChild<QPushButton*>("addComponentButton");

    if (button) {
        auto buttonPos = button->geometry().topLeft();
        std::cout << buttonPos.x() << std::endl;
        std::cout << buttonPos.y() << std::endl;
        button->hide();
    }
}

void TrackEditorWindow::createComponent(std::string componentType) {
    if (componentType.empty()) return;

    QWidget* componentToUse = nullptr;

    if (componentType == "QLineEdit") {
        componentToUse = new QLineEdit();
    } else if (componentType == "QPushButton") {
        componentToUse = new QPushButton("Button");
    }

    if (!componentToUse) {
        std::cerr << "Unsupported component type: " << componentType << std::endl;
        return;
    }

    componentToUse->setFixedSize(256, 16);
    auto button = findChild<QPushButton*>("addComponentButton");

    if (button) {
        auto buttonPos = button->mapToGlobal(button->geometry().topLeft());
        componentToUse->move(buttonPos.x() + button->width() + 10, buttonPos.y());
        componentToUse->show();
    }
}

