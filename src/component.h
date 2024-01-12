#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>
#include <QLineEdit>

class Component : public QWidget
{
    Q_OBJECT

public:
    Component(QWidget *parent = nullptr);

signals:
    void componentCreated(QWidget *component);
};

class LyricsComponent : public Component
{
    Q_OBJECT

public:
    LyricsComponent(QWidget *parent = nullptr);
};

class ChordsComponent : public Component
{
    Q_OBJECT

public:
    ChordsComponent(QWidget *parent = nullptr);
};

class NotebookComponent : public Component
{
    Q_OBJECT

public:
    NotebookComponent(QWidget *parent = nullptr);
};

class TabComponent : public Component
{
    Q_OBJECT

public:
    TabComponent(QWidget *parent = nullptr);
};

class SheetMusicComponent : public Component
{
    Q_OBJECT

public:
    SheetMusicComponent(QWidget *parent = nullptr);
};

#endif // COMPONENT_H
