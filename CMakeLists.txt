cmake_minimum_required(VERSION 3.16)

project(ProductionWorkshop LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(production_workshop
    main.cpp
    src/event.cpp
    src/logger.cpp
    src/machine.cpp
    src/manufactory.cpp
    src/parser.cpp
    src/product.cpp
)

target_include_directories(production_workshop PUBLIC include)
