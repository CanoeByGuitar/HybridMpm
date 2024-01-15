file( GLOB SOURCE_FILES *.cpp *.h )

find_package(Eigen3 REQUIRED)

#========================Mpm Dynamic Library============================
add_library(mpm SHARED ${SOURCE_FILES})
target_link_libraries(mpm Eigen3::Eigen)
target_include_directories(mpm
        PRIVATE Eigen3::Eigen
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


