#!/bin/bash

g++ -o game main.cpp Logger.cpp -I . -I vendor/raylib/src -I vendor/spdlog/include/ -L vendor/raylib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./game