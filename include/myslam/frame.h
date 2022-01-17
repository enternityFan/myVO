//
// Created by Phalange on 2022/1/17.
// C'est La vie.Enjoy it! :D
//


#ifndef VOCODE_FRAME_H
#define VOCODE_FRAME_H

#include "myslam/common_include.h"
#include "myslam/camera.h"

namespace myslam{

    class MapPoint;
    class Frame{

    public:
        typedef std::shared_ptr<Frame> Ptr;
        unsigned long                   id_;
        double                          time_stamp_;
        Sophus::SE3                     T_c_w_;
        Camera::Ptr                     camera_;
        cv::Mat                         color_,depth_;


    public:
       Frame();
       Frame(long id,double time_stamp=0,Sophus::SE3 T_c_w=Sophus::SE3(),Camera::Ptr= nullptr,Mat color=Mat(),Mat depth=Mat());
       ~Frame();

       static Frame::Ptr createFrame();

       double findDepth(const cv::KeyPoint& kp);

       Eigen::Vector3d getCamCenter() const;

       bool isInFrame(const Vector3d& pt_world);



    };


}


#endif //VOCODE_FRAME_H
