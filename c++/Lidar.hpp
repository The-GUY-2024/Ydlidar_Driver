#pragma once

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


#if defined(_MSC_VER)
#pragma comment(lib, "ydlidar_sdk.lib")
#endif

namespace _
{
    class Lidar 
    {
    public:
        static Lidar& getInstance()
        {
            static Lidar instance;
            return instance;
        }
       
        void Get_port()
        {
            fflush(stdout);
            
            ydlidar::os_init();


            std::map<std::string, std::string> ports = 
            //Here we get the list of usb devices available
                ydlidar::lidarPortList();
            std::map<std::string, std::string>::iterator it;

            if(port.size() == 1)
            {
                port = ports.begin()->second;

                std::cout << "port at: " << port << std::endl;
                
            }else{
                std::cout << "Failed to find lidar \n" << std::endl; 

                int id = 0;
                //IF lidar not detected here then Go down
                for(it = ports.begin(); it != ports.end(); it++)
                {
                    //printf("%d. %s\n", id, it->second.c_str());
                    port = it->second.c_str();
                    id++;
                }



            }
        }       
            //Setting all lidar parameters
        void OPT()
        {
            fflush(stdout);
             //lidar port

            laser.setlidaropt(LidarPropSerialPort, port.c_str(), port.size());
            //ignore array
            std::string ignore_array;
            ignore_array.clear();
            laser.setlidaropt(LidarPropIgnoreArray, ignore_array.c_str(), ignore_array.size());




            //int property 
            //lidar baudrate
            laser.setlidaropt(LidarPropSerialBaudrate, &baudrate, sizeof(int));

            //tof lidar
            int optval = YDLIDAR_TYPE_SERIAL;
            laser.setlidaropt(LidarPropDeviceType, &optval, sizeof(int));

            //Device type 
            optval = YDLIDAR_TYPE_SERIAL;
            laser.setlidaropt(LidarPropDeviceType, &optval, sizeof(int));

            //Sample rateLaserScan data;
            optval = isSingleChannel ? 3 : 4;
            laser.setlidaropt(LidarPropSampleRate, &optval, sizeof(int));

            //abnormal count
            optval = 4;
            laser.setlidaropt(LidarPropAbnormalCheckCount, &optval, sizeof(int));


            /////bool property
    
            //fixed angle resolution
            bool b_optvalue = false;
            laser.setlidaropt(LidarPropFixedResolution, &b_optvalue, sizeof(bool));

            //rotate 180
            laser.setlidaropt(LidarPropReversion, &b_optvalue, sizeof(bool));


            //CounterClockwise
            laser.setlidaropt(LidarPropInverted, &b_optvalue, sizeof(bool));
            b_optvalue = true;
            laser.setlidaropt(LidarPropAutoReconnect, &b_optvalue, sizeof(bool));

            //one-way communication
            laser.setlidaropt(LidarPropSingleChannel, &isSingleChannel, sizeof(bool));

            //intensity
            b_optvalue = false;
            laser.setlidaropt(LidarPropIntenstiy, &b_optvalue, sizeof(bool));

            //THIS IS THE MOTOR CONTROLLER
            //Motor DTR
            b_optvalue = true;
            laser.setlidaropt(LidarPropSupportMotorDtrCtrl, &b_optvalue, sizeof(bool));


            //HeartBeat
            b_optvalue = false;
            laser.setlidaropt(LidarPropSupportHeartBeat, &b_optvalue, sizeof(bool));



            ////float property
            //unit: °
            float f_optvalue = 180.0f;
            laser.setlidaropt(LidarPropMaxAngle, &f_optvalue, sizeof(float));

            f_optvalue = -180.0f;
            laser.setlidaropt(LidarPropMinAngle, &f_optvalue, sizeof(float));

            //unit: m
            f_optvalue = 64.f;
            laser.setlidaropt(LidarPropMaxRange, &f_optvalue ,sizeof(float));

            f_optvalue = 0.05f;
            laser.setlidaropt(LidarPropMinRange, &f_optvalue, sizeof(float));

            //unit: Hz
            laser.setlidaropt(LidarPropScanFrequency, &frequency,sizeof(float));
    
        }

        //Turning the laser on  or off
        bool On_laser()
        {
            ret = laser.initialize();
            //if ret on laser on
            if(ret)
            {
                ret = laser.turnOn();
            }
            else
            {
                std::cout << "Error " << ret << std::endl;
                fprintf(stderr, "%s\n", laser.DescribeError());
                fflush(stderr);
            }
            return ret;
        }


    //This function return data
        LaserScan* DATA()
        {
            if(laser.doProcessSimple(DAta))
            {

            }else
            {
                std::cout << stderr << "Failed to get lidar data \n" << std::endl;
                fflush(stderr);
            }

            return &DAta;
        }
        //To use function DATA() :  LaserScan* data = DATA();
    private:
        CYdLidar laser;
        string port;
        int baudrate = 115200;
        LaserScan DAta;
        bool isSingleChannel = true;
        float frequency = 8.0;
        bool ret;

    };
}
