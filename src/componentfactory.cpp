#include "componentfactory.h"
#include "component.h"

#include <QLineEdit>
#include <QComboBox>

QWidget* LyricsComponentCreator::FactoryMethod() {
    return new QLineEdit();
}

QWidget* ChordsComponentCreator::FactoryMethod() {
    return new QComboBox();
}

QWidget* NotebookComponentCreator::FactoryMethod() {

}

QWidget* TabComponentCreator::FactoryMethod() {

}

QWidget* SheetMusicComponentCreator::FactoryMethod() {

}
