cmake_minimum_required(VERSION 3.20)

project(SearchEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(SearchEngine
        source/main.cpp

        source/Document.cpp
        header/Document.hpp

        source/Tokenizer.cpp
        header/Tokenizer.hpp

        source/InvertedIndex.cpp
        header/InvertedIndex.hpp

        source/SearchEngine.cpp
        header/SearchEngine.hpp

        source/ResultRanker.cpp
        header/ResultRanker.hpp

        source/HashMap.cpp
        header/HashMap.hpp

        header/SearchWindow.hpp
        source/SearchWindow.cpp

        header/QueryProcessor.hpp
        source/QueryProcessor.cpp
)

set_target_properties(SearchEngine PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_include_directories(SearchEngine PRIVATE header)

target_link_libraries(SearchEngine PRIVATE Qt6::Widgets)