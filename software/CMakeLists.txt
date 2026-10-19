cmake_minimum_required(VERSION 3.16)

#include esp-idf build env
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

list(APPEND EXTRA_COMPONENT_DIRS ./components)

project(dormgarden)
