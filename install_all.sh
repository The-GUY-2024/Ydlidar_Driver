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


DIR=$(dirname $0)


#Install the handler writing by me 
cd Python

sudo pip3 install .

cd ..


