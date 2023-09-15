file(GLOB SPEC_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/Vein.json
)

set(OPENAPI_JAR openapi-generator-cli-6.6.0.jar)

add_custom_target(
    spec-files
    SOURCES ${SPEC_FILE}
)

add_custom_target(
    3rd-party-tools
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${OPENAPI_JAR}
)

execute_process(COMMAND java -jar ${CMAKE_CURRENT_SOURCE_DIR}/${OPENAPI_JAR} generate -i ${SPEC_FILE} -g cpp-qt-qhttpengine-server -o ${CMAKE_BINARY_DIR})
