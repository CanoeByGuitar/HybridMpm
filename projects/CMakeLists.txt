#======================Demos=======================

# Base Mpm
add_executable(MpmBase MpmBase.cpp)
target_link_libraries(MpmBase mpm)
target_include_directories(MpmBase PRIVATE ../src)





#======================Tests=======================

# LogTest
add_executable(LogTest tests/LogTest.cpp)
target_link_libraries(LogTest mpm)
target_include_directories(LogTest PRIVATE ../src)

# DataManager
add_executable(DataManagerTest tests/DataManagerTest.cpp)
target_link_libraries(DataManagerTest mpm)
target_include_directories(DataManagerTest PRIVATE ../src)