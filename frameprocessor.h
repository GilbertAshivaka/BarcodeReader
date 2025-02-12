#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <QObject>
#include <QVideoSink>
#include <QVideoFrame>

class FrameProcessor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVideoSink *videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)
public:
    explicit FrameProcessor(QObject *parent = nullptr);

    QVideoSink *videoSink() const;
    void setVideoSink(QVideoSink *sink);

signals:
    void videoSinkChanged();

public slots:
    processFrame(const QVideoFrame &frame);

private:
    QVideoSink m_videoSink;
};

#endif // FRAMEPROCESSOR_H
