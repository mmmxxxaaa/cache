project(Cache)

include_directories(include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(lru_simple src/main.cpp src/tests.cpp)
