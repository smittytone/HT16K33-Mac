cmake_minimum_required(VERSION 3.14)

# Set project name and binary name
set(PROJECT_NAME "I2CDriver")
set(CLI_NAME "i2ccl")

project(${PROJECT_NAME} C)

# Load the application
add_subdirectory(app)