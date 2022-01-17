//
// Created by Phalange on 2022/1/17.
// C'est La vie.Enjoy it! :D
//


#ifndef VOCODE_MAPPOINT_H
#define VOCODE_MAPPOINT_H
#include "common_include.h"
namespace myslam{
    class Frame;
    class MapPoint{

    public:
        typedef std::shared_ptr<MapPoint> Ptr;

        unsigned long id_;
        static unsigned long factory_id_;
        bool good_;
        Eigen::Vector3d pos_;
        Eigen::Vector3d norm_;
        cv::Mat descriptor_;

        list<Frame*> observed_frames_;

        int matched_times_;
        int visible_times_;


        MapPoint();

        MapPoint(unsigned long id,const Eigen::Vector3d& position,const Vector3d& norm,Frame* frame= nullptr,const cv::Mat& descriptor=cv::Mat());

       inline cv::Point3f getPositionCV() const{
           return cv::Point3f(pos_(0,0),pos_(1,0),pos_(2,0));
       }

        static MapPoint::Ptr createMapPoint();

       static MapPoint::Ptr createMapPoint(const Eigen::Vector3d& pos_world,const Vector3d& norm,const Mat& descriptor,Frame* frame);
    };





}









#endif //VOCODE_MAPPOINT_H
