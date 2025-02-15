#include "frameprocessor.h"
#include "imageprocessor.h"

#include "include/DynamsoftBarcodeReader.h"
#include "include/DynamsoftCaptureVisionRouter.h"

using namespace dynamsoft::license;
using namespace dynamsoft::cvr;
using namespace dynamsoft::dbr;
//using namespace dynamsoft::utility;
//using namespace cv;

FrameProcessor::FrameProcessor(QObject *parent)
    : QObject{parent}
{
    m_isAvailable = true;
    char errorMsgBuffer[512];

    CLicenseManager::InitLicense("t0068lQAAABa8p7d6vIsLzXULX4XjMq689SBDTTjrc+ysij5GMVzyfNu0DF7yMUPWY+FmrDMolnhZSBqdHn9nzwVElDQ/8aY=;t0068lQAAAGXVdR0NdbdrG3GmOSmy5GOkKEP4v8XG+qCXVenT2I9CHYIDns4ZHJc0FE+BxPXzC1tbsOMkKlWxRCbz3F7dCqE=", errorMsgBuffer, 512);
    printf("DBR_InitLicense: %s\n", errorMsgBuffer);

    const char *version = CBarcodeReaderModule::GetVersion();
    m_displayingString = QString(version);

    ImageProcessor *processor = new ImageProcessor();
    QThread *workerThread = new QThread();

    processor->moveToThread(workerThread);
    connect(workerThread, &QThread::finished, processor, &QObject::deleteLater);
    connect(this, &FrameProcessor::newFrameAvailable, processor, &ImageProcessor::processImage);
    connect(processor, &ImageProcessor::imageProcessed, this, &FrameProcessor::onImageProcessed);
    workerThread->start();

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
    if (!frame.isValid() || !m_isAvailable)
        return;

    m_isAvailable = false;
    QImage image = frame.toImage();
    emit newFrameAvailable(image);
}











