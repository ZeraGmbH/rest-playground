cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# policy to use new if IN_LIST feature
cmake_policy(SET CMP0057 NEW)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# glob for our custom sources, which are to be injected into the generated code
file(GLOB SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/veinentrysingleton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

file(GLOB HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/veinentrysingleton.h
)

# for visibility in qt creator
add_custom_target(
    custom-sources
    SOURCES ${SRCS} ${HEADERS}
)

set(GENERATED_SERVER_SRC_DIR "${CMAKE_BINARY_DIR}/server/src")

file(GLOB GENERATED_SRCS
    ${GENERATED_SERVER_SRC_DIR}/models/*.cpp
    ${GENERATED_SERVER_SRC_DIR}/handlers/*.cpp
    ${GENERATED_SERVER_SRC_DIR}/requests/*.cpp
    ${GENERATED_SERVER_SRC_DIR}/main.cpp
)

# inject our handlers into generated code
foreach(file ${SRCS})
    get_filename_component(filename ${file} NAME)
    if ("${GENERATED_SERVER_SRC_DIR}/handlers/${filename}" IN_LIST GENERATED_SRCS)
        list(REMOVE_ITEM GENERATED_SRCS "${GENERATED_SERVER_SRC_DIR}/handlers/${filename}")
        list(APPEND GENERATED_SRCS ${file})
        # remove from list to add rest in bulk later
        list(REMOVE_ITEM SRCS "${file}")
    endif()
endforeach()

# inject main into generated code
list(REMOVE_ITEM GENERATED_SRCS "${GENERATED_SERVER_SRC_DIR}/main.cpp")
list(APPEND GENERATED_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
# remove from list to add rest in bulk later
list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# add every leftovers custom sources, which not replace generated ones
list(APPEND GENERATED_SRCS ${SRCS})


include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
    ${GENERATED_SERVER_SRC_DIR}/models
    ${GENERATED_SERVER_SRC_DIR}/handlers
    ${GENERATED_SERVER_SRC_DIR}/requests
)
link_directories(
    ${CMAKE_PREFIX_PATH}/lib
)

add_executable(${PROJECT_NAME} ${GENERATED_SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME} Qt5Core Qt5Network ssl crypto qhttpengine systemd)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
