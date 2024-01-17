#include "componentfactory.h"

#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>

QWidget* LyricsComponentCreator::FactoryMethod() {
    return new QLineEdit();
}

QWidget* ChordsComponentCreator::FactoryMethod() {
    return new QComboBox();
}

QWidget* NotebookComponentCreator::FactoryMethod() {
    return new QTextEdit();
}

QWidget* TabComponentCreator::FactoryMethod() {

}

QWidget* SheetMusicComponentCreator::FactoryMethod() {

}
