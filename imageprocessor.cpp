#include "imageprocessor.h"
#include <QImage>

#define DBRERR_SUCCESS 0
#include "include/DynamsoftBarcodeReader.h"

//using namespace dynamsoft::dbr;

ImageProcessor::ImageProcessor(QObject *parent)
    : QObject(parent)
{
    reader = DBR_CreateInstance();

    char errorMessage[256];

    PublicRuntimeSettings settings;
    DBR_GetRuntimeSettings(reader, &settings);
    DBR_UpdateRuntimeSettings(reader, &settings, errorMessage, 256);


}

ImageProcessor::~ImageProcessor()
{
    if (reader) DBR_DestroyInstance(reader);

}

void ImageProcessor::processImage(const QImage &image)
{
    if (!reader)
        return;

    QString out = "";

    if (!image.isNull()){
        int width = image.width();
        int height = image.height();

        int bytesPerLine = image.bytesPerLine();

        const uchar *pixelData = image.constBits();

        int ret = 0;


        if (image.format() == QImage::Format_RGBA8888_Premultiplied || image.format() == QImage::Format_RGBA8888){
            ret = DBR_DecodeBuffer(reader, pixelData, width, height, bytesPerLine, IPF_ABGR_8888, "");
        }
    }


    TextResultArray *handler = NULL;
    DBR_GetAllTextResults(reader, *handler);
    TextResults **results = handler->results;
    int count = handler->resultCount;


    for (int index = 0; index < count; index++){
        out += "Index: " + QString::number(index)  + "\n";
        out += "Barcode format: " + QLatin1String(results[index]->barcodeFormatString) + "\n";
        out += "Barcode value: " + QLatin1String(results[index]->barcodeText) + "\n";
        out += "----------------------------------------------------------------------------------------\n";
    }

    DBR_FreeTextResults(&handler);

    emit imageProcessed(out);
}


























