#ifndef RECOGNISECORE_H
#define RECOGNISECORE_H

#include <iostream>
using namespace std;

#include <QObject>
#include <QDir>
#include <QVector>
#include <QDateTime>

#include <opencv2/opencv.hpp>

#include "VisionFaceFeature.h"

#define FEA_LEN 512
// 每个人存储5张feature
struct Feature{
    QString name;
    QString imgPath;
    float fea1[FEA_LEN];
    float fea2[FEA_LEN];
    float fea3[FEA_LEN];
    float fea4[FEA_LEN];
    float fea5[FEA_LEN];
    float fea6[FEA_LEN];
};

class RecogniseCore : public QObject
{
    Q_OBJECT
public:
    explicit RecogniseCore(QObject *parent = 0);
    ~RecogniseCore();

    bool Init();
    void SetThd(float i_thd);

    vision::VisionFaceFeature *faceFeature;

protected:
    void timerEvent(QTimerEvent *);

private:
    bool flag = true;
    void CompareScore(vector<float> feature);
    vector<Feature> featureDatabase;

    int registNum;
    float thd;
    cv::Mat rog_img;
    bool gender;

signals:
    void SendAvaliable();
    void SendResult(QVector<QString> result);
    void SendResult(cv::Mat rog_img, QString image_path, QString name, float score, bool gender);
    void SendResultLog(QString info);
    void SendLog(QString info);

public slots:
    void RecogniseSlot(cv::Mat img);
    void SetAvaliable(bool flag);
    void ReloadDatabaseSlot();
};

#endif // RECOGNISECORE_H
