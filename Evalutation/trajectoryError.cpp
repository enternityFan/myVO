//
// Created by Phalange on 2022/1/19.
// C'est La vie.Enjoy it! :D
//

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pangolin/pangolin.h>

#include "sophus/se3.h"


using namespace std;
using namespace Sophus;

string groundtruth_file = "/home/lifan/DATA/rgbd_dataset_freiburg1_xyz/groundtruth.txt";
string estimated_file = "/home/lifan/Code/SLAM_Code/VoCode/Evalutation/estimated.txt";


typedef vector<Sophus::SE3,Eigen::aligned_allocator<Sophus::SE3>> TrajectoryType;

void DrawTrajectory(const TrajectoryType &gt,const TrajectoryType & esti);

TrajectoryType ReadTrajectory(const string &path);

void evalATE(const TrajectoryType &gt,const TrajectoryType & esti);

void evalRPE(const TrajectoryType &gt,const TrajectoryType & esti);


int main(int argc,char **argv){

    cout<<"Please pay attention to the format of the dataset when using..."<<endl;

    TrajectoryType groundtruth = ReadTrajectory(groundtruth_file);
    TrajectoryType estimated = ReadTrajectory(estimated_file);
    assert(!groundtruth.empty()&& !estimated.empty());
    //assert(groundtruth.size()==estimated.size());
    evalATE(groundtruth,estimated);
    evalRPE(groundtruth,estimated);





    DrawTrajectory(groundtruth,estimated);
    return 0;
}


TrajectoryType ReadTrajectory(const string &path){
    ifstream fin(path);
    TrajectoryType trajectory;
    if(!fin){
        cerr << "trajectory "<< path <<" not found." << endl;
        return trajectory;
    }

    while(!fin.eof()){
        double time,tx,ty,tz,qx,qy,qz,qw;
        fin >> time >> tx >> ty >> tz>> qx>>qy>>qz>>qw;
        Sophus::SE3 p1(Eigen::Quaterniond(qw,qx,qy,qz),Eigen::Vector3d(tx,ty,tz));
        trajectory.push_back(p1);
    }

    return trajectory;
}

void evalATE(const TrajectoryType &gt,const TrajectoryType & esti)
{
    // compute rmse
    double ate_all = 0.0,ate_trans=0.0;
    for(size_t i = 0;i<esti.size();i++){
        Sophus::SE3 p1 = esti[i],p2 = gt[i];
        double ate_all_error = (p2.inverse()*p1).log().norm();
        ate_all += ate_all_error*ate_all_error;
        double ate_trans_error = (p2.inverse()*p1).translation().norm();
        ate_trans +=ate_trans_error*ate_trans_error;

    }
    ate_all = ate_all / double (esti.size());
    ate_all = sqrt(ate_all);
    ate_trans = ate_trans / double (esti.size());
    ate_trans = sqrt(ate_trans);
    cout<<"ATEAll = " << ate_all << "ATETrans = " << ate_trans<<  endl;
}

void evalRPE(const TrajectoryType &gt,const TrajectoryType & esti){
    // compute rpe
    double rpe_all = 0.0,rpe_trans=0.0;
    double delta = 2; // 间隔两帧
    for(size_t i = 0;i<esti.size()-2;i++){
        double rpe_all_error = ((gt[i].inverse()*gt[i+delta]).inverse()*(esti[i].inverse()*esti[i+delta])).log().norm();
        rpe_all += rpe_all_error*rpe_all_error;
        double rpe_trans_error = ((gt[i].inverse()*gt[i+delta]).inverse()*(esti[i].inverse()*esti[i+delta])).translation().norm();
        rpe_trans +=rpe_trans_error*rpe_trans_error;

    }
    rpe_all = sqrt(rpe_all/double (esti.size()));
    rpe_trans = sqrt(rpe_trans / double (esti.size()));

    cout<<"RPEAll = " << rpe_all << "RPETrans = " << rpe_trans<<  endl;


}










void DrawTrajectory(const TrajectoryType &gt, const TrajectoryType &esti) {
    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));


    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);
        for (size_t i = 0; i < gt.size() - 1; i++) {
            glColor3f(0.0f, 0.0f, 1.0f);  // blue for ground truth
            glBegin(GL_LINES);
            auto p1 = gt[i], p2 = gt[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }

        for (size_t i = 0; i < esti.size() - 1; i++) {
            glColor3f(1.0f, 0.0f, 0.0f);  // red for estimated
            glBegin(GL_LINES);
            auto p1 = esti[i], p2 = esti[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }

}





