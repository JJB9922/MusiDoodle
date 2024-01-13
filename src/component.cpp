// component.cpp
#include "component.h"
#include <iostream>
#include <QMessageBox>
#include <QWidget>
#include <QComboBox>

Component::Component(QWidget *parent) : QWidget(parent)
{
    std::cout << "Component Created!" << std::endl;
}

LyricsComponent::LyricsComponent(QWidget *parent) : Component(parent)
{
    std::cout << "Lyrics Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Lyrics Component Created!");
    msgBox.exec();

    QLineEdit *lyricEditorComponentType = new QLineEdit();
    emit componentCreated(lyricEditorComponentType);
}

ChordsComponent::ChordsComponent(QWidget *parent) : Component(parent)
{
    std::cout << "Chords Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Chords Component Created!");
    msgBox.exec();

    QComboBox *chordEditorComponentType = new QComboBox();
    emit componentCreated(chordEditorComponentType);
}

NotebookComponent::NotebookComponent(QWidget *parent) : Component(parent)
{
    std::cout << "Notebook Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Notebook Component Created!");
    msgBox.exec();
}

TabComponent::TabComponent(QWidget *parent) : Component(parent)
{
    std::cout << "Tab Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Tab Component Created!");
    msgBox.exec();
}

SheetMusicComponent::SheetMusicComponent(QWidget *parent) : Component(parent)
{
    std::cout << "Sheet Music Component Created!" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("Sheet Music Component Created!");
    msgBox.exec();
}
