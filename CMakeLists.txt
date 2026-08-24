cmake_minimum_required(VERSION 3.16)

project(manga-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(manga-cli
    main.cpp
    cli.cpp
    manga.h manga.cpp
    cli.h
    manga.h
)