import os
import ydlidar
import time
import numpy as np

#This function detects for a Lidar connected through usb
def Get_port():
    ydlidar.os_init();
    
    #Get usb port list
    ports = ydlidar.lidarPortList();

    port = "/dev/ydlidar";    

    #Look for port address
    for key, value in ports.items():
        port = value;

    return port;

#Define all the lidar parameters
def Parameters(port):
    laser = ydlidar.CYdLidar();
    #Declare the usb address to the SDK
    laser.setlidaropt(ydlidar.LidarPropSerialPort, port);
    #Declare the usb Baudrate (this is different for every lidar)
    laser.setlidaropt(ydlidar.LidarPropSerialBaudrate, 115200);
    #Declare the Type of Lidar (In my case the lidar type is a Triangulation lidar)
    laser.setlidaropt(ydlidar.LidarPropLidarType, ydlidar.TYPE_TRIANGLE);
    #Declare the Device type for this device
    laser.setlidaropt(ydlidar.LidarPropDeviceType, ydlidar.YDLIDAR_TYPE_SERIAL);
    #Define the lidar Frequency 
    laser.setlidaropt(ydlidar.LidarPropScanFrequency, 8);
    #Define the number of samplse per second
    laser.setlidaropt(ydlidar.LidarPropSampleRate, 1);
    #Define if the lidar have multiple channels for communication
        #(a Chanel for Upload only)
        #(a Channel for Downloda only)
        #My lidar has a single channel so is True 
    laser.setlidaropt(ydlidar.LidarPropSingleChannel, True);
    return laser;

#Initialize the SDK for the lidar 
def Initialize_SDK(laser):
    ret = laser.initialize();
    if ret:
        
        #Turn lidar on
        ret = laser.turnOn();

        #Get Laser Scan Data Raw
        scan = ydlidar.LaserScan();

        return ret,scan,laser;
    
    time.sleep(0.0275)
    #Disconnect lidar from program
    laser.disconnecting();


#Extract data from raw laser data
def Extract_Data(ret,scan, laser):
    #Create While loop to extract Lidar data
    while ret and ydlidar.os_isOk():
        r = laser.doProcessSimple(scan);
        if r:
            angle = []
            range = []
            for point in scan.points:
                angle.append(point.angle);
                range.append(point.range);
            
            anglenp = np.array(angle)
            rangenp = np.array(range)

            x = rangenp * np.cos(anglenp)
            y = rangenp * np.sin(anglenp)

            return x,y

        else: 
            print ("Failed to get lidar data");
            return x,y

    laser.turnOff();
