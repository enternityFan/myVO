//
// Created by Phalange on 2022/1/19.
// C'est La vie.Enjoy it! :D
//


#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include "sophus/se3.h"

using namespace std;
string groundtruth_file = "/home/lifan/Code/SLAM_Code/VoCode/Evalutation/groundtruth.txt";
string associategroundtruth_file = "/home/lifan/DATA/rgbd_dataset_freiburg1_xyz/associate_with_groundtruth.txt";

int main(int argc,char** argv){

    vector<string> data;

    ifstream fin(associategroundtruth_file);
    if(!fin){
        cerr<<"read file failed"<< endl;
        return 0;
    }

    while(!fin.eof()){
        string rgb_time,rgb_file,depth_time,depth_file,time,x,y,z,qs,qy,qz,qw;
        fin>>rgb_time>>rgb_file>>depth_time>>depth_file>>time>>x>>y>>z>>qs>>qy>>qz>>qw;
        data.push_back(rgb_time+" "+x+" "+y+" "+z+" "+qs+" "+qy+" "+qz+" "+qw);
    }
    fin.close();
    ofstream fout(groundtruth_file);
    if(!fout)
    {
        cerr<<"write file failed" << endl;
        return 0;
    }

    for(auto each_line:data){
        fout<<each_line<<endl;
    }




    return 0;
}