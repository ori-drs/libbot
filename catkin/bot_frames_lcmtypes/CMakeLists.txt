cmake_minimum_required(VERSION 2.8.3)
project(bot_frames_lcmtypes)

find_package(catkin REQUIRED COMPONENTS
lcm_catkin
)

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS lcm_catkin
)

FindLCM(../../bot2-frames/)

AddLCM(
bot_frames_update_t
)

GenerateLCM()

catkin_package(LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS lcm_catkin
  INCLUDE_DIRS ${CATKIN_DEVEL_PREFIX}/include)