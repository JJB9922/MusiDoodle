#include "trackeditorwindow.h"
#include "ui_trackeditorwindow.h"
#include "chordselector.h"


#include <iostream>
#include <QtWidgets>

TrackEditorWindow::TrackEditorWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::TrackEditorWindow)
{
    ui->setupUi(this);
    QSize size = qApp->screens()[0]->size();

    QPushButton* initialButton = new QPushButton(QString("+"), this);
    initialButton->move(10, 64);
    initialButton->setVisible(true);

    ChordSelector* chordSelector = new ChordSelector(this);
    chordSelector->setParent(this);
    chordSelector->setFixedSize(size.width()/3 - 64, 256);
    chordSelector->move(2*(size.width()/3) + 16, 64);
    //chordSelector->setVisible(true);

    connect(initialButton, &QPushButton::clicked, this, &TrackEditorWindow::showNewComponentPicker);
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

void TrackEditorWindow::showNewComponentPicker()
{
    static NewComponentPicker newComponentPicker(this);
    newComponentPicker.setModal(true);

    if (newComponentPicker.exec() == QDialog::Accepted) {
        QString selectedComponentType = newComponentPicker.getSelectedComponentType();

        std::unique_ptr<ComponentFactory> factory;

        if (selectedComponentType == "Lyrics") {
            factory = std::make_unique<LyricsComponentCreator>();
        } else if (selectedComponentType == "Chords") {
            factory = std::make_unique<ChordsComponentCreator>();
        } else if (selectedComponentType == "Notebook") {
            factory = std::make_unique<NotebookComponentCreator>();
        }

        if (factory) {
            QWidget* componentToUse = factory->CreateComponent();
            createComponent(componentToUse);
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
    componentToUse->setFixedSize(2*(size.width()/3), 32);
    auto button = qobject_cast<QPushButton*>(sender());

    if (button) {
        auto buttonPos = button->pos();
        button->hide();
        componentToUse->move(buttonPos.x(), buttonPos.y() + 16);
        componentToUse->setParent(this);
        componentToUse->show();
        QPushButton* newButton = new QPushButton(QString("+"), this);
        newButton->move(buttonPos.x(), buttonPos.y() + 64);
        newButton->setVisible(true);

        connect(newButton, &QPushButton::clicked, this, &TrackEditorWindow::showNewComponentPicker);
    }
}
