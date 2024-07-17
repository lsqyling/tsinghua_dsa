# Set the project name
#enable dynamic linking
set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

include_directories(${Boost_INCLUDE_DIR})

add_executable(sort_test SortReview.cpp)

target_link_libraries(sort_test Boost::unit_test_framework)












