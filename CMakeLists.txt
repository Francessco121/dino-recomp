cmake_minimum_required(VERSION 3.20)
project(DinoRecomp)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-everything /W4")
endif()

# Opt out of constexpr mutex constructor on windows to prevent vcredist issues
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR")
endif()

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/lib/")
endif()

# RT64
set(RT64_STATIC TRUE)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/rt64 ${CMAKE_BINARY_DIR}/rt64)
target_include_directories(rt64 PRIVATE ${CMAKE_BINARY_DIR}/rt64/src)

# N64ModernRuntime
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/N64ModernRuntime)

# RecompiledFuncs - Library containing the primary recompiler output
add_library(RecompiledFuncs STATIC)

# TODO: these flags dont work on MSVC
target_compile_options(RecompiledFuncs PRIVATE
    # -Wno-unused-but-set-variable
    #-fno-strict-aliasing
    #-Wno-unused-variable
    #-Wno-implicit-function-declaration
)

target_include_directories(RecompiledFuncs PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/N64ModernRuntime/ultramodern/include
    ${CMAKE_SOURCE_DIR}/lib/N64ModernRuntime/librecomp/include
)

file(GLOB FUNC_C_SOURCES ${CMAKE_SOURCE_DIR}/RecompiledFuncs/*.c)
file(GLOB FUNC_CXX_SOURCES ${CMAKE_SOURCE_DIR}/RecompiledFuncs/*.cpp)

target_sources(RecompiledFuncs PRIVATE ${FUNC_C_SOURCES} ${FUNC_CXX_SOURCES})

# Main executable
add_executable(DinoRecomp)

set (SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_include_directories(DinoRecomp PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/rt64/src/contrib
    ${CMAKE_SOURCE_DIR}/lib/rt64/src/contrib/hlslpp/include
    ${CMAKE_SOURCE_DIR}/lib/rt64/src/contrib/dxc/inc
    ${CMAKE_SOURCE_DIR}/lib/rt64/src
    ${CMAKE_SOURCE_DIR}/lib/rt64/src/rhi
    ${CMAKE_SOURCE_DIR}/lib/rt64/src/render
    ${CMAKE_CURRENT_BINARY_DIR}
)
# TODO: more flags that dont work on msvc
if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|AMD64")
    target_compile_options(DinoRecomp PRIVATE
        -march=nehalem
        -fno-strict-aliasing
        -fms-extensions
    )
else()
    target_compile_options(DinoRecomp PRIVATE
        -fno-strict-aliasing
        -fms-extensions
    )
endif()

if (WIN32)
    include(FetchContent)

    if (DEFINED ENV{SDL2_VERSION})
        set(SDL2_VERSION $ENV{SDL2_VERSION})
    else()
        set(SDL2_VERSION "2.30.3")
    endif()

    # Fetch SDL2 on windows
    FetchContent_Declare(
        sdl2
        URL https://github.com/libsdl-org/SDL/releases/download/release-${SDL2_VERSION}/SDL2-devel-${SDL2_VERSION}-VC.zip
    )
    FetchContent_MakeAvailable(sdl2)
    target_include_directories(DinoRecomp PRIVATE
        ${sdl2_SOURCE_DIR}/include
    )
    target_link_directories(DinoRecomp PRIVATE
        ${sdl2_SOURCE_DIR}/lib/x64
    )

    # Copy SDL2 and dxc DLLs to output folder as post build step
    add_custom_command(TARGET DinoRecomp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll"
            "${CMAKE_SOURCE_DIR}/lib/rt64/src/contrib/dxc/bin/x64/dxil.dll"
            "${CMAKE_SOURCE_DIR}/lib/rt64/src/contrib/dxc/bin/x64/dxcompiler.dll"
            $<TARGET_FILE_DIR:DinoRecomp>)

    set_target_properties(
        DinoRecomp
        PROPERTIES
            LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
            LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
            LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
            LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )

    #target_sources(DinoRecomp PRIVATE ${CMAKE_SOURCE_DIR}/icons/app.rc)
endif()

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(SDL2 REQUIRED)
    find_package(X11 REQUIRED)

    # Generate icon_bytes.c from the app icon PNG.
    #add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/icon_bytes.c ${CMAKE_CURRENT_BINARY_DIR}/icon_bytes.h
    #    COMMAND file_to_c ${CMAKE_SOURCE_DIR}/icons/512.png icon_bytes ${CMAKE_CURRENT_BINARY_DIR}/icon_bytes.c ${CMAKE_CURRENT_BINARY_DIR}/icon_bytes.h 
    #    DEPENDS ${CMAKE_SOURCE_DIR}/icons/512.png
    #)
    #target_sources(DinoRecomp PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/icon_bytes.c)

    message(STATUS "SDL2_FOUND = ${SDL2_FOUND}")
    message(STATUS "SDL2_INCLUDE_DIRS = ${SDL2_INCLUDE_DIRS}")

    target_include_directories(DinoRecomp PRIVATE ${SDL2_INCLUDE_DIRS})

    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_Xrandr_FOUND = ${X11_Xrandr_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

    target_include_directories(DinoRecomp PRIVATE ${X11_INCLUDE_DIR} ${X11_Xrandr_INCLUDE_PATH})
    target_link_libraries(DinoRecomp PRIVATE ${X11_LIBRARIES} ${X11_Xrandr_LIB})

    find_package(Freetype REQUIRED)

    message(STATUS "FREETYPE_FOUND = ${FREETYPE_FOUND}")
    message(STATUS "FREETYPE_INCLUDE_DIRS = ${FREETYPE_INCLUDE_DIRS}")
    message(STATUS "FREETYPE_LIBRARIES = ${FREETYPE_LIBRARIES}")

    include_directories(${FREETYPE_LIBRARIES})
    target_link_libraries(DinoRecomp PRIVATE ${FREETYPE_LIBRARIES})

    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)

    target_link_libraries(DinoRecomp PRIVATE "-latomic -static-libstdc++" ${CMAKE_DL_LIBS} Threads::Threads)
endif()

target_link_libraries(DinoRecomp PRIVATE
    RecompiledFuncs
    SDL2
    librecomp
    ultramodern
    rt64
)

target_sources(DinoRecomp PRIVATE ${SOURCES})

set_property(TARGET DinoRecomp PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
