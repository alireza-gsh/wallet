cmake_minimum_required(VERSION 3.14)

project(darkwallet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

find_package(Boost 1.76.0 REQUIRED COMPONENTS system thread regex json)

set(HEADERS_PATH include)

set(
	HEADERS
	${HEADERS_PATH}/backend.h
	${HEADERS_PATH}/tokeninfo.h
	${HEADERS_PATH}/rpc.h
	)

set(
	SOURCES
	src/main.cpp
	src/backend.cpp
	src/tokeninfo.cpp
	src/rpc.cpp
	)

set(PROJECT_SOURCES ${SOURCES} ${HEADERS} resources/qml.qrc)

add_executable(darkwallet ${PROJECT_SOURCES})

target_include_directories(darkwallet PRIVATE ${HEADERS_PATH})

target_link_libraries(
	darkwallet
	PRIVATE Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Quick

	Boost::system
	Boost::thread
	Boost::regex
	Boost::json
	)


