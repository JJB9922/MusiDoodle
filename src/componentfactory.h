#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include "component.h"

class ComponentFactory
{
public:
    virtual Component* FactoryMethod() = 0;

    void CreateComponent() {
        Component* ptr = this->FactoryMethod();
    }

    virtual ~ComponentFactory() = default;
};

class LyricsComponentCreator : public ComponentFactory {
    Component* FactoryMethod() override;

};

class ChordsComponentCreator : public ComponentFactory {
    Component* FactoryMethod() override;
};

class NotebookComponentCreator : public ComponentFactory {
    Component* FactoryMethod() override;
};

class TabComponentCreator : public ComponentFactory {
    Component* FactoryMethod() override;
};

class SheetMusicComponentCreator : public ComponentFactory {
    Component* FactoryMethod() override;
};

#endif // COMPONENTFACTORY_H
