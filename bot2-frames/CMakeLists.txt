cmake_minimum_required(VERSION 2.6.0)

# pull in the pods macros. See cmake/pods.cmake for documentation
set(POD_NAME bot2-frames)

include(cmake/pods.cmake)

include(cmake/lcmtypes.cmake)
lcmtypes_build()

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

option(USE_BOT_VIS "Build bot2-frames with bot2-vis dependency." ON)

list(APPEND OPENGL_LIBRARIES GL)
set(GLUT_CFLAGS "")
set(GLUT_LIBRARIES -lglut)


pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(LCM REQUIRED lcm)
pkg_check_modules(BOT2_CORE REQUIRED bot2-core)
pkg_check_modules(BOT2_PARAM REQUIRED bot2-param-client)

add_subdirectory(src)
add_subdirectory(src/test)


if(USE_BOT_VIS)
  add_subdirectory(src/renderer)
else()
  message("USE_BOT_VIS is OFF.  Not building libbot2 renderer.")
endif()
