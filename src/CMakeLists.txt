file(GLOB SOURCE_FILES
        *.cpp *.h
        datastructure/*.cpp datastructure/*.h
        util/*.cpp util/*.h
)

find_package(Eigen3 REQUIRED)
find_package(TBB REQUIRED)

#========================MPM Dynamic Library============================
add_library(mpm SHARED ${SOURCE_FILES})
target_link_libraries(mpm Eigen3::Eigen TBB::tbb)
target_include_directories(mpm
        PRIVATE Eigen3::Eigen
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


