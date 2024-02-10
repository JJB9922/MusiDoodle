#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <QWidget>
#include <QStackedWidget>
#include "Utils/dropwidget.h"

class ComponentFactory
{
public:
    virtual QWidget* FactoryMethod() = 0;

    QWidget* CreateComponent() {
        return this->FactoryMethod();
    }

    virtual ~ComponentFactory() = default;
};

class LyricsComponentCreator : public ComponentFactory {
    QWidget* FactoryMethod() override;
};

class ChordsComponentCreator : public ComponentFactory {
    QWidget* FactoryMethod() override;
};

class NotebookComponentCreator : public ComponentFactory {
    QWidget* FactoryMethod() override;
};

class TabComponentCreator : public ComponentFactory {
    QWidget* FactoryMethod() override;
};

class SheetMusicComponentCreator : public ComponentFactory {
    QWidget* FactoryMethod() override;
};

#endif // COMPONENTFACTORY_H
