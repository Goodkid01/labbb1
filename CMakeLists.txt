cmake_minimum_required(VERSION 3.15) 

set(PROJECT_NAME example) 			 


set(CMAKE_CXX_STANDARD 17)			 
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Сказать программе, что должен быть исполняемый файл
add_executable("${PROJECT_NAME}" main.cpp)

