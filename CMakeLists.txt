cmake_minimum_required(VERSION 3.10)

project(MyShadowWidget VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets UiTools)

set(SOURCE_FILE
    MyShadowWidget.h
    MyShadowWidget.cpp
    MyShadowWidget.qrc
    MyShadowWidget.ui
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILE})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::UiTools)
