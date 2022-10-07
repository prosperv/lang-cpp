CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# set the project name
PROJECT(ThreadsProject)

find_package( Threads )

# add the executable
ADD_EXECUTABLE(threadproject main.cpp)
target_link_libraries(threadproject ${CMAKE_THREAD_LIBS_INIT})

target_compile_features(threadproject PUBLIC cxx_std_17 )
