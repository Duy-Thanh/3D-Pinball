# Install script for directory: C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/src/main/cpp/SDL_mixer/external/libmodplug

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SpaceCadetPinball")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/Duy Thanh/AppData/Local/Android/Sdk/ndk/21.4.7075529/toolchains/llvm/prebuilt/windows-x86_64/bin/i686-linux-android-objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/.cxx/Debug/6z6d142e/x86/SDL_mixer/external/libmodplug/libmodplug.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libmodplug" TYPE FILE FILES
    "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/src/main/cpp/SDL_mixer/external/libmodplug/src/modplug.h"
    "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/src/main/cpp/SDL_mixer/external/libmodplug/src/libmodplug/it_defs.h"
    "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/src/main/cpp/SDL_mixer/external/libmodplug/src/libmodplug/sndfile.h"
    "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/src/main/cpp/SDL_mixer/external/libmodplug/src/libmodplug/stdafx.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Duy Thanh/Downloads/Compressed/Pinball-on-Android/app/.cxx/Debug/6z6d142e/x86/SDL_mixer/external/libmodplug/libmodplug.pc")
endif()

