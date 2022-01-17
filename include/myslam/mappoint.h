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
        Eigen::Vector3d pos_;
        Eigen::Vector3d norm_;
        cv::Mat descriptor_;
        int observed_times_;
        int correct_times_;

        MapPoint();
        MapPoint(long id,Vector3d position,Vector3d norm);

        static MapPoint::Ptr createMapPoint();
    };





}









#endif //VOCODE_MAPPOINT_H
