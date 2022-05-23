cmake_minimum_required(VERSION 3.14)

project(Application LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

if(ANDROID)	
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")

    if(ANDROID_ABI STREQUAL "armeabi-v7a")
        set(ANDROID_EXTRA_LIBS
            ${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/arm/libcrypto_1_1.so
            ${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/arm/libssl_1_1.so
            ${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/arm64/libcrypto_1_1.so
            ${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/arm64/libssl_1_1.so
            #			${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/x86/libcrypto_1_1.so
            #			${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/x86/libssl_1_1.so
            #			${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/x86_64/libcrypto_1_1.so
            #			${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/x86_64/libssl_1_1.so

            #			${OPENCV_ANDROID}/sdk/native/libs/armeabi-v7a/libopencv_java4.so
            #			${OPENCV_ANDROID}/sdk/native/libs/arm64-v8a/libopencv_java4.so
            CACHE INTERNAL "")

        #		include_directories("${OPENCV_ANDROID}/sdk/native/jni/bi-armeabi-v7a")
    endif()

    set(OPENCV_ANDROID "${CMAKE_SOURCE_DIR}/lib/opencv-4.x-Android")
    set(ANDROID_NATIVE_API_LEVEL 21 CACHE STRING "" FORCE)
    set(OpenCV_DIR "${OPENCV_ANDROID}/sdk/native/jni")
else()
    set(OpenCV_DIR "D:/Programs/OpenCV/build/x64/vc15/lib")
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

find_package(OpenCV REQUIRED)
if(ANDROID)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Sql AndroidExtras REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Sql AndroidExtras REQUIRED)
else()
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Sql REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Sql REQUIRED)

endif()

#=================== INCLUSION OF Project Files ====================#
#set(OPENSSL_ROOT_DIR ${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/x86_64/libcrypto_1_1.so)
#set(OPENSSL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/ssl/no-asm/latest/x86_64/libssl_1_1.so)

set(OPENSSL_ROOT_DIR "C:/Qt/Tools/OpenSSL/Win_x64")
set(OPENSSL_INCLUDE_DIR "C:/Qt/Tools/OpenSSL/Win_x64/include")
set(OPENSSL_LIBRARIES "C:/Qt/Tools/OpenSSL/Win_x64/lib")

find_package(OpenSSL REQUIRED)

set(UI_DIR "${CMAKE_SOURCE_DIR}/src")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(ANDROID_DIR "${CMAKE_SOURCE_DIR}/src/android")

include_directories(${UI_DIR})
include_directories(${SOURCE_DIR})
include_directories(${LIB_DIR})
include_directories(${ANDROID_DIR})

file(GLOB_RECURSE PROJECT_SOURCES
    "${SOURCE_DIR}/android/AndroidManifest.xml"
    "${UI_DIR}/*.ui"
    "${UI_DIR}/*.qrc"
    "${SOURCE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"

    "${SOURCE_DIR}/Common/*.h"
    "${SOURCE_DIR}/Common/*.cpp"

    "${SOURCE_DIR}/Managements/*.h"
    "${SOURCE_DIR}/Managements/*.cpp"

    "${SOURCE_DIR}/Controllers/*.h"
    "${SOURCE_DIR}/Controllers/*.cpp"

    "${SOURCE_DIR}/Parsers/*.h"
    "${SOURCE_DIR}/Parsers/*.cpp"

    "${SOURCE_DIR}/*.cc"

    "${ANDROID_DIR}/src/*.jar"
)

if(EXISTS "${SOURCE_DIR}/Common/Cryptographic_PROTECTED.h")
    add_compile_definitions("PROTECTOR")
endif()


# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${UI_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()
endif()

#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Daviss")

target_include_directories(${PROJECT_NAME} PRIVATE ${UI_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

if(ANDROID)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::AndroidExtras ${OpenCV_LIBS})
else()
    target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Sql ${OpenCV_LIBS} OpenSSL::SSL)
endif()

