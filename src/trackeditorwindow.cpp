#include "trackeditorwindow.h"
#include "ui_trackeditorwindow.h"
#include "newcomponentpicker.h"
#include "componentfactory.h"

#include <iostream>
#include <QtWidgets>
#include <QAction>

TrackEditorWindow::TrackEditorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrackEditorWindow)
{
    ui->setupUi(this);
    connect(ui->addComponentButton, SIGNAL(clicked()), this, SLOT(on_addComponentButton_clicked()));
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
    static NewComponentPicker newComponentPicker(this);
    newComponentPicker.setModal(true);

    if (newComponentPicker.exec() == QDialog::Accepted) {
        QString selectedComponentType = newComponentPicker.getSelectedComponentType();

        ComponentFactory* factory = nullptr;

        if (selectedComponentType == "Lyrics") {
            factory = new LyricsComponentCreator();
        } else if (selectedComponentType == "Chords") {
            factory = new ChordsComponentCreator();
        } else if (selectedComponentType == "Notebook"){
            factory = new NotebookComponentCreator();
        }

        if (factory) {
            QWidget* componentToUse = factory->CreateComponent();
            createComponent(componentToUse);
            delete factory;
        }
    }
}

void TrackEditorWindow::createComponent(QWidget* componentToUse)
{
    if (!componentToUse) {
        std::cerr << "Invalid component." << std::endl;
        return;
    }

    QSize size = qApp->screens()[0]->size();
    componentToUse->setFixedSize(size.width() - 128, 32);
    auto button = findChild<QPushButton*>("addComponentButton");

    if (button) {
        auto buttonPos = button->pos();
        button->hide();
        componentToUse->move(buttonPos.x(), buttonPos.y() + 16);
        componentToUse->setParent(this);
        componentToUse->show();
    }

    // Need to spawn a new button and (recurse?)
}
