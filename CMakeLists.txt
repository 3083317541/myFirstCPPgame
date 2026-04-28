cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

#配置变量，告诉脚本是生产构建还是开发构建
set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

if(MSVC)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_options(/arch:AVX2)#SIMD优化
else()
    add_compile_options(-mavx2 -mfma)#SIMD优化
endif()

#静态链接库
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as static libraries" FORCE)

project(mygame)

#子目录下搜索文件夹
add_subdirectory(thirdparty/raylib-5.0)

#添加源文件中的所有cpp文件
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

#再次将c++标准设置为C++17
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)


if(PRODUCTION_BUILD)

    #在生产版本中，资源路径宏是相对路径
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources")
    #定义一个生产版本宏，在生产版本中值为1
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)

else()

    #在开发版本中，资源路径宏是绝对路径
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    #定义一个其他版本宏，在其他版本中值为0
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)

endif()

#将源文件添加到可执行文件中
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )

#告诉编译器在生产版本中，不要创建控制台窗口
if(MSVC)

    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

    if(PRODUCTION_UBILD)
        set_target_properties("${CMAKE_PROJECT_NAME}"
        PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()

elseif(MINGW)
    if(PRODUCTION_BUILD)
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE 
            -mwindows
        )
    endif()

elseif(APPLE OR UNIX)
    if(PRODUCTION_BUILD)
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -s)
    endif()
endif()

#包含src中的所有头文件
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")

#链接库
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib_static)