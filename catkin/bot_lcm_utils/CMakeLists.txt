cmake_minimum_required(VERSION 2.8.3)
project(bot_lcm_utils)

find_package(catkin REQUIRED COMPONENTS
lcm_catkin
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 glib-2.0)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bot_lcm_utils
  CATKIN_DEPENDS lcm_catkin
  DEPENDS GLIB2
)

set(src ../../bot2-lcm-utils/src)

include_directories(${src}/who ${src}/tunnel ${GLIB2_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

# Log filter
add_executable(bot-lcm-logfilter ${src}/logfilter/lcm-logfilter.c)
target_link_libraries(bot-lcm-logfilter ${catkin_LIBRARIES} ${GLIB2_LIBRARIES})

# Log splice
add_executable(bot-lcm-logsplice  ${src}/logsplice/lcm-logsplice.c)
target_link_libraries(bot-lcm-logsplice  ${catkin_LIBRARIES} ${GLIB2_LIBRARIES})

# Who
add_executable(bot-lcm-who ${src}/who/lcm-who.c ${src}/who/signal_pipe.c)
target_link_libraries(bot-lcm-who  ${catkin_LIBRARIES} ${GLIB2_LIBRARIES})


set(ldpc_sources 
    ${src}/tunnel/ldpc/getopt.cpp
    ${src}/tunnel/ldpc/ldpc_create_pchk.cpp
    ${src}/tunnel/ldpc/ldpc_fec.cpp
    ${src}/tunnel/ldpc/ldpc_fec_iterative_decoding.cpp
    ${src}/tunnel/ldpc/ldpc_matrix_sparse.cpp
    ${src}/tunnel/ldpc/ldpc_rand.cpp
    ${src}/tunnel/ldpc/ldpc_scheme.cpp
    ${src}/tunnel/ldpc/ldpc_wrapper.cpp
    ${src}/tunnel/ldpc/tools.cpp
    )

# Tunnel
add_executable(bot-lcm-tunnel
    ${src}/tunnel/introspect.c
    ${src}/tunnel/lcm_tunnel_params_t.c
    ${src}/tunnel/lcm_tunnel_sub_msg_t.c
    ${src}/tunnel/lcm_tunnel_udp_msg_t.c
    ${src}/tunnel/lcm_tunnel_disconnect_msg_t.c
    ${src}/tunnel/ssocket.c
    ${src}/tunnel/lcm_tunnel.cpp
    ${src}/tunnel/lcm_tunnel_server.cpp
    ${src}/tunnel/signal_pipe.c 
    ${src}/tunnel/lcm_util.c
    ${src}/tunnel/timestamp.c
    ${ldpc_sources}
    )
target_link_libraries(bot-lcm-tunnel ${catkin_LIBRARIES} ${GLIB2_LIBRARIES})

# LDPC wrapper test
add_executable(ldpc-wrapper-test
    ${src}/tunnel/ldpc/ldpc_wrapper_test.cpp
    ${ldpc_sources}
    )

set_source_files_properties(${src}/tunnel/introspect.c ${src}/tunnel/lcm_tunnel_params_t.c ${src}/tunnel/ssocket.c ${src}/tunnel/signal_pipe.c ${src}/tunnel/lcm_util.c ${src}/tunnel/timestamp.c
    PROPERTIES COMPILE_FLAGS "-std=gnu99")

# Install executables
install(TARGETS bot-lcm-logfilter bot-lcm-logsplice bot-lcm-who bot-lcm-tunnel ldpc-wrapper-test
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
# Install bot spy
install(PROGRAMS src/bot-spy
        DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

# Install python modules
install(DIRECTORY ../../bot2-lcm-utils/python/src/ DESTINATION ${CATKIN_GLOBAL_PYTHON_DESTINATION})
