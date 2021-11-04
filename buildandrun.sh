#!/bin/bash

g++ -o bin/game main.cpp Logger.cpp -I . -I vendor/raylib/src -I vendor/spdlog/include/ -I vendor/entt/src -L vendor/raylib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./bin/game