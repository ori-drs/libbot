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

# Deputy
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_BCK ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(bot-procman-deputy
    ../../bot2-procman/src/deputy/lcm_util.c
    ../../bot2-procman/src/deputy/timestamp.c
    ../../bot2-procman/src/deputy/procinfo.c
    ../../bot2-procman/src/deputy/procman.c
    ../../bot2-procman/src/deputy/procman_deputy.c
    ../../bot2-procman/src/deputy/signal_pipe.c)
target_link_libraries(bot-procman-deputy util ${GLIB2_LIBRARIES} ${catkin_LIBRARIES})
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_BCK})


add_executable(bot-procman-deputy-test-active
    ../../bot2-procman/src/deputy/test-deputy-active.cpp)
target_link_libraries(bot-procman-deputy-test-active util ${GLIB2_LIBRARIES} ${catkin_LIBRARIES})
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_BCK})


# Build prefix for locating glide files
file(WRITE ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_PYTHON_DESTINATION}/bot_procman/build_prefix.py "import inspect, os\nBUILD_PREFIX=os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))), '..', '..', '..', '..'))\n")
file(WRITE ${PROJECT_BINARY_DIR}/python/build_prefix.py "BUILD_PREFIX='${PROJECT_BINARY_DIR}'\n")

function(install_python_script script_name python_module_or_file)
    find_package(PythonInterp REQUIRED)

    # which python version?
    execute_process(COMMAND
        ${PYTHON_EXECUTABLE} -c "import sys; sys.stdout.write(sys.version[:3])"
        OUTPUT_VARIABLE pyversion)

    # where do we install .py files to?
    set(python_install_dir
        ${PROJECT_BINARY_DIR}/lib/python${pyversion}/dist-packages)
    set(python_old_install_dir #todo: when do we get rid of this?
        ${PROJECT_BINARY_DIR}/lib/python${pyversion}/site-packages)

    if (python_module_or_file MATCHES ".+\\.py") #ends with a .py
        get_filename_component(py_file ${python_module_or_file} ABSOLUTE)

        if (NOT EXISTS ${py_file})
            message(FATAL_ERROR "${python_module_or_file} is not an absolute or relative path to a python script")
        endif()

        #get the directory where we'll install the script ${sanitized_POD_NAME}_scripts
        string(REGEX REPLACE "[^a-zA-Z0-9]" "_" __sanitized_pod_name "${POD_NAME}")
        set(pods_scripts_dir "${python_install_dir}/${__sanitized_pod_name}_scripts")

        # install the python script file
        file(COPY ${py_file}  DESTINATION "${pods_scripts_dir}")

        get_filename_component(py_script_name ${py_file} NAME)
        # write the bash script file
        file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${script_name}
            "#!/bin/sh\n"
            "export PYTHONPATH=${python_install_dir}:${python_old_install_dir}:\${PYTHONPATH}\n"
            "exec ${PYTHON_EXECUTABLE} ${pods_scripts_dir}/${py_script_name} $*\n")
    else()
        get_filename_component(py_module ${python_module_or_file} NAME) #todo: check whether module exists?
        # write the bash script file
        file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${script_name}
            "#!/bin/sh\n"
            "export PYTHONPATH=${python_install_dir}:${python_old_install_dir}:\${PYTHONPATH}\n"
            "exec ${PYTHON_EXECUTABLE} -m ${py_module} $*\n")
    endif()
    # install it...
    file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${script_name} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
    # Install python modules
    file(COPY ${PROJECT_BINARY_DIR}/python/build_prefix.py DESTINATION ${PROJECT_BINARY_DIR}/lib/python${pyversion}/dist-packages/bot_procman)
    #Copy files from devel to build
    file(GLOB PROCMAN_DEPS "${CATKIN_DEVEL_PREFIX}/../../${CATKIN_PACKAGE_PYTHON_DESTINATION}/*")
    file(COPY ${PROCMAN_DEPS} DESTINATION ${PROJECT_BINARY_DIR}/lib/python${pyversion}/dist-packages/bot_procman)
    #
    file(COPY ../../bot2-procman/python/src/ DESTINATION ${PROJECT_BINARY_DIR}/lib/python${pyversion}/dist-packages)
endfunction()
install_python_script(bot-procman-sheriff bot_procman.sheriff_gtk.sheriff_gtk)
# Install glade file and it's prefix path generator
file(COPY ../../bot2-procman/python/procman-sheriff.glade DESTINATION ${PROJECT_BINARY_DIR}/share/bot_procman)


