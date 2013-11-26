#include "imageprocessor.h"

ImageProcessor::ImageProcessor(QObject *parent) :
    QObject(parent)
{
}

bool ImageProcessor::saveImage(QByteArray data, QString savePath)
{
    /*
     * Extract id and timestamp from data
     *
     */
    QByteArray id = data.mid(0, 3);
    QByteArray time = data.mid(3, 17);
    /*
     * Create filename from timestamp
     *
     */
    QString filename = savePath + id.data() + "_" + time.data();
    qDebug() << filename;
    data = data.right(data.size() - 20);
    /*
     * Create image from byte array
     * and save it
     *
     */
    QImage image;
    image.loadFromData(data);
    return image.save(filename, "JPEG");
}

QByteArray ImageProcessor::loadImage(QString deviceID, QString time, QString imageToLoad)
{
    /*
     * Load image into byte array
     *
     */
    QByteArray bytes;
    QImage image;
    if(!image.load(imageToLoad)) qDebug() << "Failed to load image!";
    else {
        QBuffer buffer (&bytes);
        buffer.open (QBuffer::WriteOnly);
        image.save (&buffer, "JPEG");
    }
    /*
     * Prepend id and timestamp to front of image
     * Format: xxxyyyyMMddThh:mm:ss
     *
     */
    QString toPrepend = QString("%1%2").arg(deviceID).arg(time);
    bytes.prepend(toPrepend.toStdString().c_str());
    return bytes;
}

void ImageProcessor::takePicture(QString savePath)
{

    QProcess *picProc = new QProcess ();
    connect(picProc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slot_processFinished(int, QProcess::ExitStatus)));
    picProc->start("./raspistill -o /root/test.jpg");
    picProc->waitForFinished(10000);
}

void ImageProcessor::slot_processFinished (int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "PIc taken!!!!";
    emit sig_picTaken ();
}
