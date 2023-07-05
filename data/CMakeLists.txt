file(GLOB SPEC_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/Vein.json
)

add_custom_target(
    spec-files
    SOURCES ${SPEC_FILE}
)

execute_process(COMMAND openapi-generator-cli generate -i ${SPEC_FILE} -g cpp-qt-qhttpengine-server -o ${CMAKE_BINARY_DIR})
