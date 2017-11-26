cmake_minimum_required(VERSION 2.8.3)
project(bot_vis)
find_package(catkin REQUIRED COMPONENTS
bot_core
)

set(ENV{PKG_CONFIG_PATH} "/usr/lib/x86_64-linux-gnu/pkgconfig/:$ENV{PKG_CONFIG_PATH}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(GTK REQUIRED gtk+-2.0)
pkg_check_modules(OPENGL REQUIRED gl)
pkg_check_modules(GLUT REQUIRED glu)
pkg_check_modules(ZLIB REQUIRED zlib)
pkg_check_modules(X11 REQUIRED x11)

catkin_package(
  INCLUDE_DIRS ../../bot2-vis/src ${JPEG_INCLUDE_DIR}
  LIBRARIES bot_vis
  CATKIN_DEPENDS bot_core
  DEPENDS GLIB2 OPENGL GLUT JPEG ZLIB X11 GTK
)

include_directories(include ../../bot2-vis/src ${JPEG_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLIB2_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} ${X11_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

# Vis library
file(GLOB bot_vis_c_files ../../bot2-vis/src/bot_vis/*.c)
file(GLOB bot_vis_h_files ../../bot2-vis/src/bot_vis/*.h)
list(REMOVE_ITEM bot_vis_h_files glm.h) # Keep the GLM library out of the public API
add_library(bot_vis SHARED ${bot_vis_c_files})
target_link_libraries(bot_vis ${JPEG_LIBRARIES} ${GLUT_LIBRARIES} ${GTK_LIBRARIES} ${GLIB2_LIBRARIES} ${ZLIB_LIBRARIES} ${X11_LIBRARIES} ${catkin_LIBRARIES} ${OPENGL_LIBRARIES} -lglut -ljpeg)
set_property(TARGET bot_vis APPEND_STRING PROPERTY COMPILE_FLAGS -Wno-unused-result )

# RWX viewer (possibly unused)
add_executable(bot-rwx-viewer ../../bot2-vis/src/rwx-viewer/main.c ../../bot2-vis/src/rwx-viewer/renderer_rwx.c)
target_link_libraries(bot-rwx-viewer bot_vis)

# OBJ viewer (possibly unused)
add_executable(bot-wavefront-viewer ../../bot2-vis/src/wavefront-viewer/main.c ../../bot2-vis/src/wavefront-viewer/renderer_wavefront.c)
target_link_libraries(bot-wavefront-viewer bot_vis)

# Drawing teste
add_executable(gl_drawing_area_tester ../../bot2-vis/src/testers/gl_drawing_area_tester.c)
target_link_libraries(gl_drawing_area_tester bot_vis)

# Image test
add_executable(gl_image_area_tester ../../bot2-vis/src/testers/gl_image_area_tester.c)
target_link_libraries(gl_image_area_tester bot_vis)

# Widget test
add_executable(param_widget_tester ../../bot2-vis/src/testers/param_widget_tester.c)
target_link_libraries(param_widget_tester bot_vis)

# Install the library and all executables
install(TARGETS bot_vis bot-rwx-viewer bot-wavefront-viewer gl_drawing_area_tester gl_image_area_tester param_widget_tester
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
# Install the header files
install(FILES ${bot_vis_h_files}
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
