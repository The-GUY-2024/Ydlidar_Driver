
import os
import ydlidar 
import time


class Lidar:
    def __init__(self):
        
        ydlidar.os_init();

        ports = ydlidar.lidarPortList()
        self.port = "/dev/ydlidar";

        for key, value in ports.items():
            self.port = value;
        
        self.laser = ydlidar.CYdLidar();


        self.parameters();

        self.ret = self.laser.initialize();
        
        if self.ret:
            self.ret = self.laser.turnOn();
            self.scan = ydlidar.LaserScan();

            while self.ret and ydlidar.os_isOk():
                r = self.laser.doProcessSimple(self.scan)
                if r:
                    
                    range=[]
                    angle=[]

                    for point in self.scan.points:

                        angle.append(point.angle);
                        range.append(point.range); 
                        
                    print(angle)
                    print(range)
                else:
                    print("Failed to get Lidar data")

    #This are the paramerts for my lidar wich is the YDLIDAR X2L 

    def parameters(self):
        self.laser.setlidaropt(ydlidar.LidarPropSerialPort, self.port);
        self.laser.setlidaropt(ydlidar.LidarPropSerialBaudrate, 115200);
        self.laser.setlidaropt(ydlidar.LidarPropLidarType, ydlidar.TYPE_TRIANGLE);
        self.laser.setlidaropt(ydlidar.LidarPropDeviceType, ydlidar.YDLIDAR_TYPE_SERIAL);
        self.laser.setlidaropt(ydlidar.LidarPropScanFrequency, 8);
        self.laser.setlidaropt(ydlidar.LidarPropSampleRate, 9);
        self.laser.setlidaropt(ydlidar.LidarPropSingleChannel, True);



Lidar();
