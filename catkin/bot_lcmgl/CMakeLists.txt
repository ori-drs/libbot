cmake_minimum_required(VERSION 2.8.3)
project(bot_lcmgl)

add_definitions(-std=gnu99)

find_package(catkin REQUIRED bot_lcmgl_lcmtypes bot_vis)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(ZLIB REQUIRED zlib)
pkg_check_modules(OPENGL REQUIRED gl)

catkin_package(
  LIBRARIES bot2-lcmgl-client bot2-lcmgl-renderer
  CATKIN_DEPENDS bot_lcmgl_lcmtypes bot_vis
  DEPENDS GLIB2 ZLIB OPENGL
)

include_directories(include ../../bot2-lcmgl/src ../../bot2-lcmgl/src/bot_lcmgl_client ../../bot2-lcmgl/src/bot_lcmgl_renderer ${GLIB2_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_library(bot2-lcmgl-client SHARED ../../bot2-lcmgl/src/bot_lcmgl_client/lcmgl.c)
target_link_libraries(bot2-lcmgl-client ${ZLIB_LIBRARIES} ${GLIB2_LIBRARIES} ${catkin_LIBRARIES})

add_library(bot2-lcmgl-renderer SHARED ../../bot2-lcmgl/src/bot_lcmgl_render/lcmgl_bot_renderer.c ../../bot2-lcmgl/src/bot_lcmgl_render/lcmgl_decode.c)
target_link_libraries(bot2-lcmgl-renderer ${OPENGL_LIBRARIES} ${catkin_LIBRARIES})

add_executable(bot-lcmgl-viewer ../../bot2-lcmgl/src/lcmgl-viewer/main.c ../../bot2-lcmgl/src/lcmgl-viewer/udp_util.c ../../bot2-lcmgl/src/lcmgl-viewer/view_menu.c)
target_link_libraries(bot-lcmgl-viewer bot2-lcmgl-renderer -lglut)

install(TARGETS bot2-lcmgl-client bot2-lcmgl-renderer bot-lcmgl-viewer
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
install(FILES ../../bot2-lcmgl/src/bot_lcmgl_client/lcmgl.h
        DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/bot_lcmgl_client)
install(FILES ../../bot2-lcmgl/src/bot_lcmgl_render/lcmgl_decode.h ../../bot2-lcmgl/src/bot_lcmgl_render/lcmgl_bot_renderer.h
        DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/bot_lcmgl_render)

install(DIRECTORY ../../bot2-lcmgl/python/src/
  DESTINATION ${CATKIN_GLOBAL_PYTHON_DESTINATION}
  PATTERN ".svn" EXCLUDE)

