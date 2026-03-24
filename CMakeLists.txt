cmake_minimum_required(VERSION 3.16)
project(io_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodaj katalog include/ do ścieżek nagłówkowych
include_directories(include)

# Zbierz wszystkie pliki źródłowe z katalogu src/
file(GLOB SOURCES CMAKE_CONFIGURE_DEPENDS src/*.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Utwórz plik wykonywalny o nazwie "io"
add_executable(io ${SOURCES})
target_link_libraries(io ${SDL2_LIBRARIES})

# Testy
include(CTest)
#add_subdirectory(tests)
