cmake_minimum_required(VERSION 3.20)

project(joga VERSION 0.1.1 LANGUAGES C CXX)

set(TARGET joga)
set(TARGET_ALIAS joga::joga)

include(cmake/FetchYoga.cmake)

add_library(${TARGET} INTERFACE)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})
add_subdirectory(app EXCLUDE_FROM_ALL)

target_compile_features(${TARGET}
  INTERFACE
    cxx_std_23)

target_include_directories(${TARGET}
  INTERFACE
    include)

target_link_libraries(${TARGET}
  INTERFACE
    juce::juce_graphics
    juce::juce_gui_basics
    yogacore)
