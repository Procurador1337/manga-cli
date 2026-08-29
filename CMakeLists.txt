cmake_minimum_required(VERSION 3.16)

project(manga-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Network)

add_executable(manga-cli
    main.cpp
    cli.cpp
    manga.h manga.cpp
    cli.h
    mangasearch.h mangasearch.cpp
    selection.h selection.cpp
    chapter.h chapter.cpp
    chaptersearch.h chaptersearch.cpp
    provider.h provider.cpp
    networkclient.h networkclient.cpp
    terminalutils.h terminalutils.cpp
    imagerender.h imagerender.cpp
    pageviewer.h pageviewer.cpp
)
find_package(Qt6 REQUIRED COMPONENTS Network Gui)
target_link_libraries(manga-cli PRIVATE Qt6::Network Qt6::Gui)