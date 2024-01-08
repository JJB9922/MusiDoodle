#include "component.h"
#include <iostream>
#include <QMessageBox>

Component::Component() {
    std::cout << "Component Created!" << std::endl;
}

LyricsComponent::LyricsComponent() {
    std::cout << "Lyrics Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Lyrics Component Created!");
    msgBox.exec();
}

ChordsComponent::ChordsComponent() {
    std::cout << "Chords Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Chords Component Created!");
    msgBox.exec();
}

NotebookComponent::NotebookComponent() {
    std::cout << "Notebook Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Notebook Component Created!");
    msgBox.exec();
}

TabComponent::TabComponent() {
    std::cout << "Tab Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Tab Component Created!");
    msgBox.exec();
}

SheetMusicComponent::SheetMusicComponent() {
    std::cout << "Sheet Music Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Sheet Music Component Created!");
    msgBox.exec();
}
