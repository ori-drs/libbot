cmake_minimum_required(VERSION 2.8.3)
project(bot_procman)

add_definitions(-std=gnu99)

find_package(catkin REQUIRED COMPONENTS
bot_procman_lcmtypes
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)

catkin_package(
  CATKIN_DEPENDS bot_procman_lcmtypes
  DEPENDS GLIB2
)

include_directories(include ../../bot2-procman/src ../../bot2-procman/src/deputy ${GLIB2_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_executable(bot-procman-deputy
    ../../bot2-procman/src/deputy/lcm_util.c
    ../../bot2-procman/src/deputy/timestamp.c
    ../../bot2-procman/src/deputy/procinfo.c
    ../../bot2-procman/src/deputy/procman.c
    ../../bot2-procman/src/deputy/procman_deputy.c
    ../../bot2-procman/src/deputy/signal_pipe.c)
target_link_libraries(bot-procman-deputy util ${GLIB2_LIBRARIES} ${catkin_LIBRARIES})
file(WRITE ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_PYTHON_DESTINATION}/bot_procman/build_prefix.py "import inspect, os\nBUILD_PREFIX=os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))), '..', '..', '..', '..'))\n")
file(WRITE ${PROJECT_BINARY_DIR}/python/build_prefix.py "BUILD_PREFIX='${CMAKE_INSTALL_PREFIX}'\n")
catkin_python_setup()

install(TARGETS bot-procman-deputy
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
install(PROGRAMS ../../bot2-procman/python/scripts/bot-procman-sheriff
        DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
install(DIRECTORY ../../bot2-procman/python/src/ DESTINATION ${CATKIN_GLOBAL_PYTHON_DESTINATION})
install(FILES ../../bot2-procman/python/procman-sheriff.glade DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
install(FILES ${PROJECT_BINARY_DIR}/python/build_prefix.py DESTINATION ${CATKIN_PACKAGE_PYTHON_DESTINATION})

