cmake_minimum_required(VERSION 3.0.2)
project(drone_localisation)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a") # This is to fix the issue with finding the libav libraries on the Jetson
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages




find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  std_srvs
  sensor_msgs
  geometry_msgs
  octomap_msgs
  visualization_msgs
  cmake_modules
  tf
  message_filters
  octomap_ros
  pcl_ros
  pcl_conversions
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#  FILES
#   Message2.msg
#)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 #generate_messages(
 #  DEPENDENCIES
 #  std_msgs  # Or other packages containing msgs
 #)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
 INCLUDE_DIRS "include" "lib/humanoid_localization/include"
 LIBRARIES localisation_models
 CATKIN_DEPENDS roscpp nodelet
#  DEPENDS system_lib
)

###########
## Build ##
###########

# set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/humanoid_localization/src)
add_library(localisation_models
  "lib/humanoid_localization/src/EndpointModel.cpp"
  "lib/humanoid_localization/src/MapModel.cpp"
  "lib/humanoid_localization/src/MotionModel.cpp"
  "lib/humanoid_localization/src/RaycastingModel.cpp"
  "lib/humanoid_localization/src/ObservationModel.cpp"
  )
set_target_properties(localisation_models PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(localisation_models PUBLIC
${catkin_INCLUDE_DIRS}
"lib/humanoid_localization/include"
)
target_link_libraries(localisation_models
  ${catkin_LIBRARIES}
)


add_library(drone_localisation
  "src/drone_localisation.cpp"
  "src/localisation_node.cpp"
)
target_link_libraries(drone_localisation
  ${catkin_LIBRARIES}
  localisation_models
)
target_include_directories(drone_localisation PUBLIC
  ${catkin_INCLUDE_DIRS}
  "include"
)







add_executable(drone_localisation_nodelet
  "src/localisation_nodelet.cpp"
)
target_include_directories(drone_localisation_nodelet PUBLIC
  ${catkin_INCLUDE_DIRS}
)
target_link_libraries(drone_localisation_nodelet
  ${catkin_LIBRARIES}
  drone_localisation
)

add_executable(drone_localisation_node
  "src/localisation_node.cpp"
)
target_link_libraries(drone_localisation_node
  ${catkin_LIBRARIES}
  drone_localisation
)

target_include_directories(drone_localisation_node PUBLIC
  ${catkin_INCLUDE_DIRS}
)
