#include "componentfactory.h"

#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>

QWidget* LyricsComponentCreator::FactoryMethod() {
    return new QLineEdit();
}

QWidget* ChordsComponentCreator::FactoryMethod() {
    QComboBox* newComboBox = new QComboBox();
    newComboBox->addItem(QString("A"));
    newComboBox->addItem(QString("B"));
    return newComboBox;
}

QWidget* NotebookComponentCreator::FactoryMethod() {
    return new QTextEdit();
}

QWidget* TabComponentCreator::FactoryMethod() {
    return new QLineEdit();
}

QWidget* SheetMusicComponentCreator::FactoryMethod() {
    return new QLineEdit();
}
