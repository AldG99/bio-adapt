cmake_minimum_required(VERSION 3.16)
project(TardigradeSimulator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Charts)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Source files
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/VisualSimWidget.cpp
    src/ScienceSimWidget.cpp
    src/Tardigrade.cpp
    src/KnowledgeBase.cpp
    src/ChartsWidget.cpp
)

set(HEADERS
    src/MainWindow.h
    src/VisualSimWidget.h
    src/ScienceSimWidget.h
    src/Tardigrade.h
    src/KnowledgeBase.h
    src/ChartsWidget.h
)

# Resource file
qt5_add_resources(RESOURCES resources/resources.qrc)

add_executable(TardigradeSimulator ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(TardigradeSimulator 
    Qt5::Core 
    Qt5::Widgets 
    Qt5::Charts
)

# Set output directory
set_target_properties(TardigradeSimulator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)