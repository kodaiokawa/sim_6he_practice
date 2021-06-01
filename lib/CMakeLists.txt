cmake_minimum_required(VERSION 3.20)
project(lise_lib
    VERSION 1.0.0
    DESCRIPTION "okawa practice"
    # URL関係のライブラリをインストールしないと動かないことがあるので
    # コメントアウトしておきます(2019/12/02 修正)
    # (参照 "https://kamino.hatenablog.com/entry/cmake_tutorial2")
    # HOMEPAGE_URL "https://example.com"
    LANGUAGES CXX)

add_library(refer STATIC 
    ./source/function.cpp)

target_link_libraries(refer PUBLIC ROOT::Hist ROOT::Physics)
target_compile_features(refer PUBLIC cxx_std_11)
target_include_directories(refer INTERFACE ./include)
set_target_properties(refer
    PROPERTIES
    VERSION ${PROJECT_VERSION})





