cmake_minimum_required(VERSION 3.16)
project(sfml-snake LANGUAGES CXX)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 2)
set(VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 11b73743c42cf7ecd7c596ba83fdbf1150ffa96c
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(gamemenu
    GIT_REPOSITORY https://github.com/mheller575/GameMenu-cpp.git
    GIT_TAG eca33376a4c9197d4522aab5c5bec05864aa8b81
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(gamemenu)

set(SOURCE_FILES 
"src/main.cpp"
"src/ui/MainMenu.cpp"
"src/ui/MainMenu.h"
"src/core/FoodComponent.cpp"
"src/core/FoodComponent.h"
"src/core/GameBoard.cpp"
"src/core/GameBoard.h"
"src/core/GameController.cpp"
"src/core/GameController.h"
"src/core/IComponent.h"
"src/core/RandomNumberGenerator.cpp"
"src/core/RandomNumberGenerator.h"
"src/core/SnakeComponent.cpp"
"src/core/SnakeComponent.h"
"src/core/Utilities.cpp"
"src/core/Utilities.h"
)

add_executable(snake ${SOURCE_FILES})

target_link_libraries(snake PRIVATE sfml-graphics gamemenu)
target_compile_features(snake PRIVATE cxx_std_17)
target_include_directories(snake PRIVATE src)

add_custom_target(copy_menu_font
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/sansation.ttf ${CMAKE_BINARY_DIR}
)
add_dependencies(snake copy_menu_font)

if(WIN32)
    add_custom_command(
        TARGET snake
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:snake>
        VERBATIM)
endif()

install(TARGETS snake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)