cmake_minimum_required(VERSION 3.1.0)

project(calculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCES 
    src/main.cpp
    src/MainWindow.cpp
    src/Interface.cpp
    src/MathOperation.cpp
    src/NewWindow.cpp
    src/Cursors.cpp
	
    src/MainWindow.h
    src/Interface.h
    src/MathOperation.h
    src/NewWindow.h
    src/Cursors.h
	
    resource/resource.qrc)
add_executable(calculator ${SOURCES})

target_link_libraries(calculator Qt5::Widgets)

IF (WIN32)
  set(QtDLL "${Qt5_DIR}../../../bin")
  set(winBuildDir "${PROJECT_SOURCE_DIR}/bin/winBuild")
  
  IF(NOT EXISTS ${winBuildDir}/Debug/Qt5Widgets.dll)
    add_custom_command(TARGET calculator POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${QtDLL}"
          "${winBuildDir}/Debug")
  ENDIF()

  set(QtPlugins "${Qt5_DIR}../../../plugins")
  
  IF(NOT EXISTS ${winBuildDir}/plugins)
  #add_custom_command(TARGET calculator POST_BUILD
 # COMMAND MAKE_DIRECTORY
   #   "${winBuildDir}/plugins")
	  
  add_custom_command(TARGET calculator POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${QtPlugins}"
      "${winBuildDir}/plugins")
  ENDIF()
ENDIF()
