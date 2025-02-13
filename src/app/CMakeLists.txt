add_executable(${PROJECT_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_NAME}-lib
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
