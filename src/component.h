#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    Component();
};

class LyricsComponent : public Component {
public:
    LyricsComponent();
};

class ChordsComponent : public Component {
public:
    ChordsComponent();
};

class NotebookComponent : public Component {
public:
    NotebookComponent();
};

class TabComponent : public Component {
public:
    TabComponent();
};

class SheetMusicComponent : public Component {
public:
    SheetMusicComponent();
};

#endif // COMPONENT_H
