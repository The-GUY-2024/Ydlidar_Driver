import datetime
import os
import ydlidar 
import time
import numpy as np


class Lidar:
    def __init__(self):
        #Define variables parameters
        self.port= ""
        self.laser = ""
        self.scan = ""
        self.ret = ""
        #Declarin Lidar data 
        self.x =[]
        self.y =[]

        #parameter for return data from lidar 
        
        self.Get_port();
        self.Parameters();
        self.Initialize_SDK();
        



#This function detects for a Lidar connected through usb
    def Get_port(self):
        ydlidar.os_init();

        #Get usb port list
        ports = ydlidar.lidarPortList();

        self.port = "/dev/ydlidar";

        #Look for port address
        for key, value in ports.items():
            self.port = value;


    #Define All The lidar parameters
    def Parameters(self):
        self.laser = ydlidar.CYdLidar();
        #Declare the usb address to the SDK
        self.laser.setlidaropt(ydlidar.LidarPropSerialPort, self.port);
        #Declare the usb Baudrate (this is different for every lidar)
        self.laser.setlidaropt(ydlidar.LidarPropSerialBaudrate, 115200);
        #Declare the Type of Lidar (In my case the lidar type is a Triangulation lidar)
        self.laser.setlidaropt(ydlidar.LidarPropLidarType, ydlidar.TYPE_TRIANGLE);
        #Declare the Device type for this device
        self.laser.setlidaropt(ydlidar.LidarPropDeviceType, ydlidar.YDLIDAR_TYPE_SERIAL);
        #Define the lidar Frequency 
        self.laser.setlidaropt(ydlidar.LidarPropScanFrequency, 8);
        #Define the number of samplse per second
        self.laser.setlidaropt(ydlidar.LidarPropSampleRate, 1);
        #Define if the lidar have multiple channels for communication
            #(a Chanel for Upload only)
            #(a Channel for Downloda only)
            #My lidar has a single channel so is True 
        self.laser.setlidaropt(ydlidar.LidarPropSingleChannel, True);

#Initialize the SDK for The lidar 
    def Initialize_SDK(self):
        self.ret = self.laser.initialize();
        if self.ret:
            
            #Turn lidar Laser on
            self.ret = self.laser.turnOn();
            #Get Laser Scan Data Raw
            self.scan =ydlidar.LaserScan(); 
            

            #Start extracting data
            self.Extract_Data();
            
        time.sleep(0.0275)
#Disconnect lidar from program
        self.laser.disconnecting()


#Extract Data from raw laser data 
    def Extract_Data(self):
        #Create while loop to extract Lidar data
            while self.ret and ydlidar.os_isOk():
                r = self.laser.doProcessSimple(self.scan);
                if r:
                    angle = []
                    range = []
                    for point in self.scan.points:
                        angle.append(point.angle)
                        range.append(point.range)

                    anglenp = np.array(angle)
                    rangenp = np.array(range)

                    x = rangenp * np.cos(anglenp)
                    y = rangenp * np.sin(anglenp)

                    return x,y

                else:
                    print("Failed to get Lidar Data")
            
            #turn off Laser
            self.laser.turnOff();



Lidar();
