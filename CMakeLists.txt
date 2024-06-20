#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
cmake_minimum_required(VERSION 3.20)

project(
  JOGA
  DESCRIPTION "An interface to Yoga for JUCE"
  VERSION 2024.6.20
  LANGUAGES CXX)

string(TOLOWER ${PROJECT_NAME} TARGET)
set(TARGET_ALIAS ${TARGET}::${TARGET})

#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
find_package(yoga CONFIG REQUIRED)

#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
add_library(${TARGET} INTERFACE)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})

set_target_properties(${TARGET}
  PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON)

target_include_directories(${TARGET}
  INTERFACE
  include)

target_link_libraries(${TARGET}
  INTERFACE
  yoga::yogacore)
