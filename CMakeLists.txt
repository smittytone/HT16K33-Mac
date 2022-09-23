cmake_minimum_required(VERSION 3.20)

# Set project name and binary name
set(PROJECT_NAME "I2C_Apps")

# Set app name(s) and version(s)
set(APP_1_NAME "I2CDriver")
set(APP_1_VERSION_NUMBER "1.0.0")
set(APP_1_BUILD_NUMBER "0")
set(APP_1_CLI_NAME "i2ccl")

set(APP_2_NAME "MatrixDriver")
set(APP_2_VERSION_NUMBER "1.0.0")
set(APP_2_BUILD_NUMBER "0")
set(APP_2_CLI_NAME "matrix")

# Specify the app(s) source code
set(APP_1_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/i2ccl")
set(APP_2_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/matrix")

# Code common to multiple apps
set(COMMON_CODE_DIRECTORY "${CMAKE_SOURCE_DIR}/Common")

project(${PROJECT_NAME} 
        LANGUAGES C
        DESCRIPTION "macOS drivers for use with I2C Mini")

# Load the application
add_subdirectory(${APP_1_SRC_DIRECTORY})
add_subdirectory(${APP_2_SRC_DIRECTORY})