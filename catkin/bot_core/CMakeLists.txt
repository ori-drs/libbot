cmake_minimum_required(VERSION 2.8.3)
project(bot_core)
find_package(catkin REQUIRED COMPONENTS
bot_core_lcmtypes
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 glib-2.0)

catkin_package(
  INCLUDE_DIRS ../../bot2-core/src ${GLIB2_INCLUDE_DIRS}
  LIBRARIES bot_core
  CATKIN_DEPENDS bot_core_lcmtypes
  DEPENDS GLIB2
  CFG_EXTRAS bot-core-includes.cmake
)

add_definitions(-std=gnu99)

file(GLOB c_files ../../bot2-core/src/bot_core/*.c)
file(GLOB h_files ../../bot2-core/src/bot_core/*.h)

include_directories(../../bot2-core/src/bot_core/ ${GLIB2_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_library(bot_core SHARED ${c_files})
target_link_libraries(bot_core ${catkin_LIBRARIES} ${GLIB2_LIBRARIES} m)
set_property(TARGET bot_core APPEND_STRING PROPERTY COMPILE_FLAGS -Wno-unused-result )

install(TARGETS bot_core
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(FILES ${h_files}
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})