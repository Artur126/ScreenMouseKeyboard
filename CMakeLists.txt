cmake_minimum_required(VERSION 3.16)
project(io_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodaj katalog include/ do ścieżek nagłówkowych
include_directories(include)

# Zbierz wszystkie pliki źródłowe z katalogu src/
file(GLOB SOURCES CMAKE_CONFIGURE_DEPENDS src/*.cpp)


# ---------------------------------------------------------
#  SDL2 / SDL2_ttf / SDL2_gfx – wykrywanie zależne od OS
# ---------------------------------------------------------

if (WIN32)
    # -----------------------------------------
    # WINDOWS (MSYS2 / MinGW64) → pkg-config
    # -----------------------------------------
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

    add_definitions(-DSDL_MAIN_HANDLED)

    include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_GFX_INCLUDE_DIRS}
    )

    link_directories(
        ${SDL2_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS}
        ${SDL2_GFX_LIBRARY_DIRS}
    )

    set(SDL2_LIBS
        SDL2main
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_GFX_LIBRARIES}
    )
else()
    # -----------------------------------------
    # LINUX → find_package (działa idealnie)
    # -----------------------------------------
    find_package(SDL2 REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_gfx REQUIRED)

    include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_GFX_INCLUDE_DIRS}
    )

    set(SDL2_LIBS
        ${SDL2_LIBRARIES}
        SDL2_ttf::SDL2_ttf
        SDL2_gfx::SDL2_gfx
    )
endif()


# Utwórz plik wykonywalny o nazwie "io"
add_executable(io ${SOURCES})

target_link_libraries(io ${SDL2_LIBS})


# Testy
include(CTest)
#add_subdirectory(tests)
