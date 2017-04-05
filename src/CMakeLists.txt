# $Id$
# $Date$
#
# This is the CMake Build file for
#   P175873
#
#
# Original Author: Kadir Ince, kadir.ince57@gmail.com
#
# (c) 2017 Kadir Ince

# project properties
set(EXE_NAME cpuinfo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# cmake 2.8 required
cmake_minimum_required(VERSION 2.8)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


find_package(Qt5 COMPONENTS Quick Core )
#find_package(Qt5QuickCompiler)

# if we use Qt resources (.qrc), we need to resource-compile them first
#qtquick_compiler_add_resources(RESOURCES qml.qrc)
qt5_add_resources(RESOURCES qml.qrc)



# Define a list of headers/sources to use
set(EXE_SRCS
	main.cpp
	speedData.cpp
	cpuinfomodel.cpp
	cpuinfodata.cpp
	cpuinfo.cpp
)
set(EXE_HEADERS 
	speedData.h	
	cpuinfomodel.h
	cpuinfodata.h
	cpuinfo.h
)


# bring it all together for the library
set(ALL_SRCS
	${EXE_QT_RES_OUT}
	${EXE_QT_UI_OUT}
	${EXE_HEADERS} ${EXE_SRCS} 
)


# add executable
add_executable(${EXE_NAME} ${ALL_SRCS} ${RESOURCES})

#qt5_use_modules(${EXE_NAME} Quick Core )

# now we need to link against the qt libraries we use
target_link_libraries(${EXE_NAME} ${QT_LIBRARIES} Qt5::Quick)

#strip the debugging symbols
#strip_binary(${EXE_NAME} 1)

# add astyle
add_custom_target( 
	astyle 
	COMMAND astyle
#	--options=${CMAKE_SOURCE_DIR}/asytelformat.txt 
	--style=allman
	--indent=spaces=4
	--break-blocks
	--pad-oper
	--pad-header
	--break-closing-brackets
	--add-brackets
	--mode=c
	--suffix=none
	--recursive
	\"${CMAKE_SOURCE_DIR}/*.cpp\" \"${CMAKE_SOURCE_DIR}/*.h\"
	)


# add cppcheck
add_custom_target( 
	cppcheck 
	COMMAND cppcheck 
	--enable=warning,performance,portability,information,missingInclude 
	--std=c++11 
	--library=qt.cfg 
	--template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)" 
	--verbose 
	--quiet 
	${CMAKE_SOURCE_DIR}
	)



