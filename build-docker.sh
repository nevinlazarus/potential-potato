#!/bin/sh
sudo docker build . -t connect4
sudo docker run -it connect4

