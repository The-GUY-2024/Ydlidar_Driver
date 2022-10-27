import Lidar

port = Lidar.Get_port();

laser = Lidar.Parameters(port);

ret, scan, laser = Lidar.Initialize_SDK(laser);
while True:
    x,y = Lidar.Extract_Data(ret,scan,laser);
    print(len(x))
