add_library(VoCode SHARED
        frame.cpp
        mappoint.cpp
        camera.cpp
        config.cpp ../include/myslam/frame.h ../include/myslam/map.h ../include/myslam/mappoint.h ../include/myslam/config.h map.cpp)

target_link_libraries(VoCode ${THIRD_PARTY_LIBS})