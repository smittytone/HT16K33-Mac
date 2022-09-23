cmake_minimum_required(VERSION 3.20)

message("Building ${APP} ${VERSION_NUMBER} build ${BUILD_NUMBER}")

# Make app data available to the compiler
add_compile_definitions(APP_NAME="${APP_2_NAME}")
add_compile_definitions(APP_VERSION="${APP_2_VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${APP_2_BUILD_NUMBER})

# Uncomment line below for debug output from binary
#add_compile_definitions(VERBOSE="${APP}")

# Compile app source code file(s)
add_executable(${APP_2_NAME}
    ${APP_2_SRC_DIRECTORY}/main.c
    ${COMMON_CODE_DIRECTORY}/i2cdriver.c
    ${COMMON_CODE_DIRECTORY}/ht16k33.c
)

add_custom_command(OUTPUT APP_2_EXTRA_FILES DEPENDS ${APP_2_NAME}
    # Rename output
    COMMAND mv "${APP_2_NAME}" "${APP_2_CLI_NAME}"
)

# Prepare the additional files
add_custom_target(app_2_extras ALL DEPENDS APP_2_EXTRA_FILES)