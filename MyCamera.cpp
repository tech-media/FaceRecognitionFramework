#include "mycamera.h"

MyCamera::MyCamera(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    interval = 130; // Default Value
    cameraStarted = false;
}

void MyCamera::StartCamera(int ID)
{
    //if(!cameraStarted)
    {
        cameraID = ID;
//        ID = 1;
        cout << "Camera ID:" << cameraID << endl;
        /// 2015-03-03 为了演示，ID设置为1
        //ID = 0;
        if(videoCapture.open(ID))
        {
            cout << "Change Camera SUCCEED." << endl;
            connect(timer, SIGNAL(timeout()), this, SLOT(NextFrame()));
            timer->setInterval(interval);
        }
        else
        {
            cout << "Failed to Open Camera." << endl;
            emit SendPlayErrorSig("Failed to Open Camera.");
        }
        cameraStarted = true;
    }
}

void MyCamera::StartCameraTimer()
{
    timer->start();
}

void MyCamera::CloseCameraSlot()
{
    timer->stop();
}

void MyCamera::NextFrame()
{
#ifdef DEBUG
    cout << "A Picture was Captrued." << endl;
#endif
    cv::Mat frm;
    videoCapture >> frm;

    if(!frm.empty())
    {
        emit SendFrameMat(frm);
    }
    else
    {
        cout << "Read Frame Failed!" << endl;
    }
}

void MyCamera::SetInterval(int i_interval)
{
    interval = i_interval;
}

MyCamera::~MyCamera()
{

}

