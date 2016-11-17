cmake_minimum_required(VERSION 2.8.3)
project(bot_frames)

add_definitions(-std=gnu99)

find_package(catkin REQUIRED COMPONENTS
bot_core
bot_param
bot_vis
bot_lcmgl
bot_frames_lcmtypes
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 glib-2.0)
pkg_check_modules(OPENGL opengl)

catkin_package(
  LIBRARIES bot_frames bot-frames-renderers
  CATKIN_DEPENDS bot_core bot_param bot_vis bot_lcmgl bot_frames_lcmtypes
  DEPENDS GLIB2
)

include_directories(include ../../bot2-frames/src/ ../../bot2-frames/src/bot_frames ../../bot2-frames/src/test ../../bot2-frames/src/renderer ${GLIB2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_library(bot-frames SHARED ../../bot2-frames/src/bot_frames.c)
target_link_libraries(bot-frames ${catkin_LIBRARIES} ${GLIB2_LIBRARIES})
set_target_properties(bot-frames PROPERTIES SOVERSION 2)

add_library(bot-frames-renderers SHARED ../../bot2-frames/src/renderer/coord_frames_renderer.c ../../bot2-frames/src/renderer/articulated_body_renderer.c ../../bot2-frames/src/renderer/frame_modifier_renderer.c)
target_link_libraries(bot-frames-renderers bot-frames ${catkin_LIBRARIES} ${OPENGL_LIBRARIES})

add_executable(test-viewer ../../bot2-frames/src/renderer/test_viewer.c)
target_link_libraries(test-viewer bot-frames-renderers ${catkin_LIBRARIES} -lglut)

add_executable(coord-frames-test ../../bot2-frames/src/test/coord_frames_test.c)
target_link_libraries(coord-frames-test bot-frames)

install(TARGETS bot-frames bot-frames-renderers coord-frames-test test-viewer
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
install(FILES ../../bot2-frames/src/bot_frames/bot_frames.h ../../bot2-frames/src/bot_frames/bot_frames_renderers.h
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
install(FILES ../../bot2-frames/src/test/test_params.cfg
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
