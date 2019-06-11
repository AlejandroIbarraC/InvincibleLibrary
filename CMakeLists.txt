cmake_minimum_required(VERSION 3.10)
project(MyInvincibleLibrary)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

add_executable(MyInvincibleLibrary client/main.cpp client/GUI/menu.cpp client/GUI/menu.h client/GUI/menu.ui client/GUI/assets/resources.qrc client/GUI/elements/buttonhoverwatcher.cpp client/GUI/elements/buttonhoverwatcher.h client/GUI/elements/image.h client/GUI/elements/image.cpp)

include_directories(${CPR_INCLUDE_DIRS})
target_link_libraries(MyInvincibleLibrary Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia ${CPR_LIBRARIES})
