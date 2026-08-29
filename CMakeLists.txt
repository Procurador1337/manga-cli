cmake_minimum_required(VERSION 3.16)

project(manga-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Network Gui)

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
    pageviewer.h pageviewer.cpp
    mpvviewer.h mpvviewer.cpp
)

target_link_libraries(manga-cli PRIVATE Qt6::Network Qt6::Gui)

install(TARGETS manga-cli
    RUNTIME DESTINATION bin
)
