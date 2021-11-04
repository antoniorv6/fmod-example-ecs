#!/bin/bash

g++ -o bin/game main.cpp Logger.cpp -I . -I vendor/raylib/src -I vendor/spdlog/include/ -I vendor/entt/src -I vendor/FMOD/inc -L vendor/FMOD/lib -L vendor/raylib/ -lfmod -lfmodstudio -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && cp -r vendor bin/ && ./bin/game