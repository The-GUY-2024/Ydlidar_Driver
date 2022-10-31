#ifdef LIDAR_H
#define LIDAR_H

#include <iostream>
#include <string>
#include <src/CYdLidar.h>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <math.h>
#include <complex>

using namespace std;
using namespace ydlidar;


class Lidar{
    public:



        static Lidar& getInstance();

        void Get_port();

        void Parameters();

        bool On_laser();

        LaserScan* DATA();

    private:
        CYdLidar laser;
        string port;
        int baudrate;
        LaserScan Data;
        bool isSingleChannel = true;
        float frequency = 8.0;
        bool ret;

};

#endif
