cmake_minimum_required(VERSION 3.8)
project("GraphXplorer")

set(CMAKE_CXX_STANDARD 20)

# ----------------------
# Fetch raylib
# ----------------------
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# ----------------------
# Fetch raygui
# ----------------------
include(FetchContent)
FetchContent_Declare(
    raygui
    URL https://github.com/raysan5/raygui/archive/refs/tags/4.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(raygui)

# ----------------------
# Create executable
# ----------------------
add_executable(GraphXplorer
    main.cpp
    src/Application.cpp
)

# ----------------------
# Include directories
# ----------------------
target_include_directories(GraphXplorer PRIVATE
    ${CMAKE_SOURCE_DIR}
    src/headers
    ${raygui_SOURCE_DIR}/src
)

# ----------------------
# Link libraries
# ----------------------
target_link_libraries(GraphXplorer PRIVATE raylib)
