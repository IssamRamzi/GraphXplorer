cmake_minimum_required (VERSION 3.8)

project ("GraphXplorer")


# Dependencies
set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) 
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()



add_executable (GraphXplorer
  "main.cpp"
  "src/Application.cpp"
)

target_link_libraries(${PROJECT_NAME} raylib)

include_directories(
    "${CMAKE_SOURCE_DIR}" 
    "src/headers"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphXplorer PROPERTY CXX_STANDARD 20)
endif()

