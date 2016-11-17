cmake_minimum_required(VERSION 2.8.3)
project(bot_lcmgl_lcmtypes)

find_package(catkin REQUIRED COMPONENTS
lcm_catkin
)

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS lcm_catkin
)

FindLCM(../../bot2-lcmgl/)

AddLCM(
bot_lcmgl_data_t
)

AddJAVA(bot2-lcmgl ../../bot2-lcmgl/java/src/bot_lcmgl/LCMGL.java)

GenerateLCM()
