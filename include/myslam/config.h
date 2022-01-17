//
// Created by Phalange on 2022/1/17.
// C'est La vie.Enjoy it! :D
//


#ifndef VOCODE_CONFIG_H
#define VOCODE_CONFIG_H

#include "myslam/common_include.h"

namespace myslam{
    class Config{
    private:
        static std::shared_ptr<Config> config_;
        cv::FileStorage file_;
        Config(){} // private constructor makes a singleton

    public:
        ~Config();
        static void setParameterFile(const std::string& filename);

        template<class T>
                static T get(const std:: string &key){
                    return T(Config::config_->file_[key]);
                }
    };
}




#endif //VOCODE_CONFIG_H
