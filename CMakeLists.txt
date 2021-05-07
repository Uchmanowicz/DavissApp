cmake_minimum_required(VERSION 3.14)

project(DavissApp VERSION 0.1.0)

add_compile_definitions(APP_VERSION="\\"${PROJECT_VERSION}\\"")

message(${CMAKE_SYSTEM_NAME})

if(ANDROID)
	message("MAM ANDROID")

else()
	message("MAM WINDOWS")
endif()

add_subdirectory(src)
#add_subdirectory(src/tests)

