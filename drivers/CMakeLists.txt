set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/adc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/pwm.c
    )

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY_NAME drivers)
add_library(${LIBRARY_NAME} STATIC ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${HEADERS})

target_link_libraries(${LIBRARY_NAME} PRIVATE
    project_features
    project_warnings
    project_config
    )