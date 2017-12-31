#ifndef KINECT_PREVIEW_H
#define KINECT_PREVIEW_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Kinect.h>

class KinectPreview : public QThread
{
    Q_OBJECT

private:
    static const int depth_w_ = 512;  //512
    static const int depth_h_ = 424;  //424
    static const int color_w_ = 1920; //1920
    static const int color_h_ = 1080; //1080

    IKinectSensor* sensor;
    IDepthFrameReader* depthReader;
    IColorFrameReader* colorReader;

    std::vector<cv::Mat> depth;
    std::vector<cv::Mat> colors;
    //cv::Mat* depthForDisplay;

    QImage frameImage;
    QSize frameImageSize;

    bool stopped;
    QMutex mutex;
    QWaitCondition condition;

    void initDepthSource();
    void initColorSource();

    void convertAndSaveDepthMat(IDepthFrame* depthFrame);
    void convertAndSaveColorMat(IColorFrame* colorFrame);

signals:
      void frameReady(const QImage &frame);

protected:
     void run();

public:
    KinectPreview(QObject *parent = 0);
    ~KinectPreview();

    void startPreview(QSize previewSize);
    void stopPreview();

    bool isStopped() const;
};

#endif // KINECT_PREVIEW_H