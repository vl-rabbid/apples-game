cmake_minimum_required(VERSION 3.16)

project(apples-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

#SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

#Source
file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

#Executable
add_executable(apples-game ${SOURCES})

#Headers
target_include_directories(
    apples-game
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

#Resources
target_compile_definitions(
    apples-game
    PRIVATE
    RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
)

#Libraries
target_link_libraries(apples-game PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

if(WIN32)
    add_custom_command(
        TARGET apples-game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:sfml-graphics>"
            "$<TARGET_FILE_DIR:apples-game>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:sfml-window>"
            "$<TARGET_FILE_DIR:apples-game>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:sfml-system>"
            "$<TARGET_FILE_DIR:apples-game>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:sfml-audio>"
            "$<TARGET_FILE_DIR:apples-game>"
    )
endif()
