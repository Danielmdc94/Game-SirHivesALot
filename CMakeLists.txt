cmake_minimum_required(VERSION 3.22)
include(FetchContent)

project(Sir-Hives-a-Lot VERSION 1.0)

FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(TARGET_NAME Sir-Hives-a-Lot)

file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB ASSETS assets/*)

source_group("source" FILES ${SOURCES})
source_group("include" FILES ${HEADERS})
source_group("assets" FILES ${ASSETS})

add_executable(${TARGET_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET_NAME} PRIVATE sfml-audio sfml-graphics sfml-window sfml-system Shlwapi)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sir-Hives-a-Lot)

if(APPLE)
    file(GLOB RESOURCE_FILES "assets")
    set_source_files_properties("${RESOURCE_FILES}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    target_sources(${TARGET_NAME} PRIVATE ${RESOURCE_FILES})
    set_target_properties(${TARGET_NAME} PROPERTIES RESOURCE "${RESOURCE_FILES}")
    add_compile_definitions(TARGET_OS_MAC)
else()
    set(WORKING_PATH assets)
    cmake_path(ABSOLUTE_PATH WORKING_PATH OUTPUT_VARIABLE WORKING_PATH)
    set_target_properties(${TARGET_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY ${WORKING_PATH}
    )
    add_custom_command(TARGET Sir-Hives-a-Lot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-graphics-d-2.dll"
            "${PROJECT_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-window-d-2.dll"
            "${PROJECT_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-audio-d-2.dll"
            "${PROJECT_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-system-d-2.dll"
            $<TARGET_FILE_DIR:Sir-Hives-a-Lot>)
    add_custom_command(
        TARGET Sir-Hives-a-Lot
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Sir-Hives-a-Lot>
        VERBATIM)
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
        COMMENT "Copy assets directory"
        VERBATIM
    )
endif()