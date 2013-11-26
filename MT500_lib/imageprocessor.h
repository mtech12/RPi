#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QByteArray>
#include <QImage>
#include <QBuffer>
#include <QDateTime>
#include <QProcess>
#include <QDebug>

#define SAVEPATH "/root"

class ImageProcessor : public QObject
{

    Q_OBJECT

public:
    ImageProcessor(QObject *parent = 0);

    /*
     * Function responsible for saving image
     */
    bool saveImage(QByteArray data, QString savePath = SAVEPATH);

    /*
     * Loads image into a byte array ready for
     * transmitting
     */
    QByteArray loadImage(QString deviceID, QString time, QString imageToLoad);

    /*
     * Takes an image using the Raspberry Pi
     * camera
     */
    void takePicture(QString savePath = SAVEPATH);

signals:

    void sig_picTaken ();

private slots:

    void slot_processFinished (int exitCode, QProcess::ExitStatus exitStatus);

private:

};

#endif // IMAGEPROCESSOR_H
