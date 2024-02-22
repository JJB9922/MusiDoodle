#ifndef TRACKSAVEDATA_H
#define TRACKSAVEDATA_H

#include <QDataStream>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

struct TrackSaveData
{
    int tempo;
    int keyNoteIndex;
    int keyToneIndex;
    int keyModeIndex;
    std::vector<QString> addedWidgets;

    friend QDataStream &operator << (QDataStream &out, const TrackSaveData &d)
    {
        out << d.tempo << d.keyNoteIndex << d.keyToneIndex << d.keyModeIndex;

        out << qint32(d.addedWidgets.size());

        for (const QString &component : d.addedWidgets) {
            out << component;
        }

        return out;
    }

    friend QDataStream &operator >> (QDataStream &in, TrackSaveData &d)
    {
        in >> d.tempo >> d.keyNoteIndex >> d.keyToneIndex >> d.keyModeIndex;

        qint32 size;
        in >> size;

        d.addedWidgets.clear();

        for (int i = 0; i < size; ++i) {
            QString component;
            in >> component;
            d.addedWidgets.push_back(component);
        }

        return in;
    }

};

#endif // TRACKSAVEDATA_H
