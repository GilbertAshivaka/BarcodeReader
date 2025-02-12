#include "frameprocessor.h"

FrameProcessor::FrameProcessor(QObject *parent)
    : QObject{parent}
{

}

QVideoSink *FrameProcessor::videoSink() const
{
    return m_videoSink;
}

void FrameProcessor::setVideoSink(QVideoSink *sink)
{
    if (m_videoSink != sink){
        connect(m_videoSink, &QVideoSink::videoFrameChanged, this, &FrameProcessor::processFrame);
    }
}

FrameProcessor::processFrame(const QVideoFrame &frame)
{
    //image processing
}
