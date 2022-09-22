cmake_minimum_required(VERSION 3.14)

# Set application data
set(APP "I2CDriver")
set(VERSION_NUMBER "1.0.0")
set(BUILD_NUMBER "0")

message("Building ${APP} ${VERSION_NUMBER} build ${BUILD_NUMBER}")

# Make app data available to the compiler
add_compile_definitions(APP_NAME="${APP}")
add_compile_definitions(APP_VERSION="${VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${BUILD_NUMBER})

# Uncomment line below for debug output from binary
#add_compile_definitions(VERBOSE="${APP}")

# Compile app source code file(s)
add_executable(${PROJECT_NAME}
    main.c
    ht16k33.c
    i2cdriver.c
)

add_custom_command(OUTPUT EXTRA_FILES DEPENDS ${PROJECT_NAME}
    # Rename output
    COMMAND mv "${PROJECT_NAME}" "${CLI_NAME}"
)

# Prepare the additional files
add_custom_target(extras ALL DEPENDS EXTRA_FILES)