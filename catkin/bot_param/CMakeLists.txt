cmake_minimum_required(VERSION 2.8.3)
project(bot_param)
find_package(catkin REQUIRED COMPONENTS
bot_core
bot_param_lcmtypes
)

add_definitions(-std=gnu99)

catkin_package(
  INCLUDE_DIRS  ../../bot2-param/src/param_client
  LIBRARIES bot_param_client
  CATKIN_DEPENDS bot_core bot_param_lcmtypes
)

include_directories(include ../../bot2-param/src/param_client ${catkin_INCLUDE_DIRS})

# Client
file(GLOB client_c_files ../../bot2-param/src/param_client/*.c)
file(GLOB client_h_files ../../bot2-param/src/param_client/bot_param/*.h)
add_library(bot_param_client SHARED ${client_c_files})
target_link_libraries(bot_param_client ${catkin_LIBRARIES} m)

# Server
add_executable(bot-param-server ../../bot2-param/src/param_server/param_server.c ../../bot2-param/src/param_server/lcm_util.c)
target_link_libraries(bot-param-server bot_param_client)
add_executable(bot-param-tool ../../bot2-param/src/param_server/param_tool.c)
target_link_libraries(bot-param-tool bot_param_client)

#Tester
add_executable(param-tester ../../bot2-param/src/param_tester/param_tester.c)
target_link_libraries(param-tester bot_param_client)
add_executable(bot-param-dump ../../bot2-param/src/param_tester/param_dump.c)
target_link_libraries(bot-param-dump bot_param_client)

# Install library and executables
install(TARGETS bot_param_client param-tester bot-param-dump bot-param-server bot-param-tool
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
# Install header files
install(FILES ${client_h_files}
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
