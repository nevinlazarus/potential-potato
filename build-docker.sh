#!/bin/sh
sudo docker build . -t connect4
sudo docker run -p 8080:8080 -it connect4

