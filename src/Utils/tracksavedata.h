#ifndef TRACKSAVEDATA_H
#define TRACKSAVEDATA_H

#include <QDataStream>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

struct TrackSaveData
{
    int tempo;
    int keyNoteIndex;
    int keyToneIndex;
    int keyModeIndex;
    QVector<QJsonObject> componentData;

    friend QDataStream &operator << (QDataStream &out, const TrackSaveData &d)
    {
        out << d.tempo << d.keyNoteIndex << d.keyToneIndex << d.keyModeIndex << d.componentData;
        return out;
    }

    friend QDataStream &operator >> (QDataStream &in, TrackSaveData &d)
    {
        in >> d.tempo >> d.keyNoteIndex >> d.keyToneIndex >> d.keyModeIndex >> d.componentData;
        return in;
    }
};

#endif // TRACKSAVEDATA_H
