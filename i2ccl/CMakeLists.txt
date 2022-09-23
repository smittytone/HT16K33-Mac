cmake_minimum_required(VERSION 3.20)

message("Building ${APP} ${VERSION_NUMBER} build ${BUILD_NUMBER}")

# Make app data available to the compiler
add_compile_definitions(APP_NAME="${APP_1_NAME}")
add_compile_definitions(APP_VERSION="${APP_1_VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${APP_1_BUILD_NUMBER})

# Uncomment line below for debug output from binary
#add_compile_definitions(VERBOSE="${APP}")

# Compile app source code file(s)
add_executable(${APP_1_NAME}
    ${APP_1_SRC_DIRECTORY}/main.c
    ${COMMON_CODE_DIRECTORY}/i2cdriver.c
)

add_custom_command(OUTPUT APP_1_EXTRA_FILES DEPENDS ${APP_1_NAME}
    # Rename output
    COMMAND mv "${APP_1_NAME}" "${APP_1_CLI_NAME}"
)

# Prepare the additional files
add_custom_target(app_1_xtras ALL DEPENDS APP_1_EXTRA_FILES)