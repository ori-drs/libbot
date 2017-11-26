cmake_minimum_required(VERSION 2.8.3)
project(bot_param_lcmtypes)

find_package(catkin REQUIRED COMPONENTS
lcm_catkin
)

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS lcm_catkin
)

FindLCM(../../bot2-param/)

AddLCM(
bot_param_entry_t
bot_param_request_t
bot_param_set_t
bot_param_update_t
)

GenerateLCM()

catkin_package(LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS lcm_catkin
  INCLUDE_DIRS ${CATKIN_DEVEL_PREFIX}/include)