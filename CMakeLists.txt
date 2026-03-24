cmake_minimum_required(VERSION 3.16)
project(io_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodaj katalog include/ do ścieżek nagłówkowych
include_directories(include)

# Zbierz wszystkie pliki źródłowe z katalogu src/
file(GLOB SOURCES CMAKE_CONFIGURE_DEPENDS src/*.cpp)

# SDL2 + SDL2_ttf normalnie
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})


# SDL2_gfx przez pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

include_directories(${SDL2_GFX_INCLUDE_DIRS})
link_directories(${SDL2_GFX_LIBRARY_DIRS})



# Utwórz plik wykonywalny o nazwie "io"
add_executable(io ${SOURCES})

target_link_libraries(io 
    ${SDL2_LIBRARIES} 
    SDL2_ttf::SDL2_ttf
    ${SDL2_GFX_LIBRARIES}
)

# Testy
include(CTest)
#add_subdirectory(tests)
