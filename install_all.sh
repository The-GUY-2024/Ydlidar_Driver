#!/bin/bash


TEXT_RESET='\e[0m'
TEXT_YELLOW='\e[0;33m'
TEXT_RED_B='\e[1;31m'

sudo apt-get update
echo -e $TEXT_YELLOW
echo 'APT update finished.... '
echo -e $TEXT_RESET


sudo apt-get upgrade 
echo -e $TEXT_YELLOW
echo 'APT upgrade finished.... '
echo -e $TEXT_RESET

sudo apt-get install -y cmake make pkg-config python3 swig python3-dev python3-pip
echo -e $TEXT_YELLOW
echo -e 'APT INSTALL FINISHED....'
echo -e $TEXT_RESET

DIR=$(dirname $0)


#Install the handler writing by me 
cd Python

sudo pip3 install .

cd ..


#installing the sdk 
git clone https://github.com/YDLIDAR/YDLidar-SDK.git

cd YDLidar-SDK

sudo mkdir build && cd build

sudo cmake ..

make 

sudo make install

cd ..

sudo pip3 install .

cd python/examples

python3 test.py


