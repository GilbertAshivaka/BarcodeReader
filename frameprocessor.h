#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <QObject>
#include <QVideoSink>

class FrameProcessor : public QObject
{
    Q_OBJECT
public:
    explicit FrameProcessor(QObject *parent = nullptr);

signals:

};

#endif // FRAMEPROCESSOR_H
