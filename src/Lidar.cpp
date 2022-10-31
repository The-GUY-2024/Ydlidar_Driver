#include "Lidar.h"

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
        static Lidar& getInstance(){
            static Lidar instance;
            return instance;
        }

        void Get_port(){
            //Clear the output buffer before  you initialize the os 
            fflush(stdout);
            
            //Initialize the lidar os
            ydlidar::os_init();

            std::map<std::string, std::string> ports =
            //Here we get the list of usb devices available
                ydlidar::lidarPortList();
            std::map<std::string, std::string>::iterator it;

            if (port.size() == 1)
            {
                port = ports.begin()->second;

                std::cout << "Port at: " << port << std::endl;
            }else{
                std::cout << " Failed to find lidar \n" << std::endl;
                int id = 0;

                //If the lidar is not detected in this for loop
                for (it = ports.begin(); it != ports.end(); it++ )
                {
                    //printf("%d. %s\n", id, it-second.c_str());
                    port = it->second.c_str();
                    id++;
                }

            }


        }


        //Declaring all the lidar parameters
        void Parameters(){
            //Parameters here are declare for a specific lidar (YDLIDAR X2L 360 Degree )

            // Clear the memory buffer 
            fflush(stdout);

            laser.setlidaropt(LidarPropSerialPort, port.c_str(), port.size());

            //ignore array
            std::string ignore_array;

            ignore_array.clear();
            laser.setlidaropt(LidarPropIgnoreArray, ignore_array.c_str(), ignore_array.size());


            //int property
            //Lidar baudrate
            laser.setlidaropt( LidarPropSerialBaudrate, &baudrate, sizeof(int));

            //Tof Lidar
            int optval = YDLIDAR_TYPE_SERIAL;
            laser.setlidaropt(LidarPropDeviceType, &optval, sizeof(int));

            //Device rateLaserScan data
            optval = isSingleChannel ? 3 : 4;
            laser.setlidaropt(LidarPropSampleRate, &optval, sizeof(int));

            //abnormal count
            optval =4; 
            laser.setlidaropt(LidarPropAbnormalCheckCount, &optval,sizeof(int));

            

            //Angle resolutuion declaration
            bool b_optvalue = false;
            laser.setlidaropt(LidarPropFixedResolution, &b_optvalue, sizeof(bool));

            //rotate 180
            laser.setlidaropt(LidarPropReversion, &b_optvalue, sizeof(bool));

            //Counter-Clockwise 
            laser.setlidaropt(LidarPropInverted, &b_optvalue, sizeof(bool));
            b_optvalue = true;
            laser.setlidaropt(LidarPropAutoReconnect, &b_optvalue, sizeof(bool));

            //one-Way communucation declaration
            laser.setlidaropt(LidarPropSingleChannel, &isSingleChannel, sizeof(bool));

            // Lidar intensity
            b_optvalue = false;
            laser.setlidaropt(LidarPropIntenstiy, &b_optvalue, sizeof(bool));

            //This is the motor controller
            //Motor DTR
            b_optvalue = true;
            laser.setlidaropt(LidarPropSupportMotorDtrCtrl, &b_optvalue, sizeof(bool));

            //HeartBeat
            b_optvalue = false;
            laser.setlidaropt(LidarPropSupportHeartBeat, &b_optvalue, sizeof(bool));

            //Float property
            //Unit of mesurment: Degrees 
            float f_optvalue = 180.0f;
            laser.setlidaropt(LidarPropMaxAngle, &f_optvalue, sizeof(float));

            f_optvalue= -180.0f;
            laser.setlidaropt(LidarPropMinAngle, &f_optvalue, sizeof(float));

            //unit of mesurment: Meters

            //This parameter declare the maximun amout of meters to mesure
            f_optvalue = 64.f;
            laser.setlidaropt(LidarPropMaxRange, &f_optvalue, sizeof(float));

            // Mi 
            //This parameter declare the minimun amout of meters to mesure
            f_optvalue = -180.0f;
            laser.setlidaropt(LidarPropMinAngle, &f_optvalue, sizeof(float));

            //Lidar Frequency Declaration
            // Unit of mesurement is in: Hz (hertz)
            laser.setlidaropt(LidarPropScanFrequency, &frequency, sizeof(float));
        }


        //Tunring the lidar laser on  & off

        bool On_laser(){
            ret = laser.initialize();

            //If ret  value is true
            if (ret){
                //Turn the lidar on 
                ret = laser.turnOn();
            }else{
                std::cout << "Error " << ret << std::endl;
                fprintf(stderr, "%s\n", laser.DescribeError());
                fflush(stderr);
            }

            //Return the ret = value 
            return ret;
        }


    //This function fetch the raw lidar data from the sdk
        LaserScan* DATA(){
            if (laser.doProcessSimple(Data)){

            }else{
                std::cout << stderr << " Failed to get lidar data \n" << std::endl;
                fflush(stderr);
            }

            return &Data;
        }
    private:
        CYdLidar laser;
        string port;
        int baudrate;
        LaserScan Data;
        bool isSingleChannel = true;
        float frequency = 8.0;
        bool ret;
};
