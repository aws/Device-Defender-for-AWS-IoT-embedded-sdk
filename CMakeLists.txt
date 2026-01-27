cmake_minimum_required(VERSION 3.15)

project(Device-Defender LANGUAGES C)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------

include(${CMAKE_CURRENT_LIST_DIR}/defenderFilePaths.cmake)

# ------------------------------------------------------------------------------
# Library targets
# ------------------------------------------------------------------------------

add_library(device_defender_for_aws INTERFACE)

target_sources(device_defender_for_aws INTERFACE ${DEFENDER_SOURCES})

target_include_directories(device_defender_for_aws INTERFACE ${DEFENDER_INCLUDE_PUBLIC_DIRS})

message(STATUS "device_defender_for_aws library requires DEFENDER_DO_NOT_USE_CUSTOM_CONFIG definition or a defender_config.h file.")
