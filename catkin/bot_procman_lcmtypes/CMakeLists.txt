cmake_minimum_required(VERSION 2.8.3)
project(bot_procman_lcmtypes)

find_package(catkin REQUIRED COMPONENTS
lcm_catkin
)

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS lcm_catkin
)

FindLCM(../../bot2-procman/)

AddLCM(
bot_procman_command2_t
bot_procman_deputy_cmd2_t
bot_procman_deputy_cmd_t
bot_procman_discovery_t
bot_procman_info2_t
bot_procman_info_t
bot_procman_orders2_t
bot_procman_orders_t
bot_procman_printf_t
bot_procman_sheriff_cmd2_t
bot_procman_sheriff_cmd_t
)

GenerateLCM()
