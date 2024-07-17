# Set the project name
# Create a library
#Generate the static library from the library sources
# Add a library with the above sources
set(linear_src)
add_library(linear_src STATIC
        src/InfixExpression.cpp
        src/Josephus.cpp
        src/ListTesting.cpp
        src/OJ.cpp
        src/Fib.cpp
        src/QueueTesting.cpp
        src/ReviewLiner.cpp
        src/StackTesting.cpp
        src/VectorTesting.cpp
        src/chapter_1_introduction.cpp
        src/chapter_2_vector.cpp
        src/chapter_3_list.cpp
        src/chapter_4_stack_queue.cpp
        )
add_library(ds::linear ALIAS linear_src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(OJ src/OJ.cpp)
add_executable(VectorTesting src/VectorTesting.cpp)
add_executable(ListTesting src/ListTesting.cpp)
add_executable(StackTesting src/StackTesting.cpp)
target_link_libraries(StackTesting
        PRIVATE
        ds::linear)
add_executable(QueueTesting src/QueueTesting.cpp)
add_executable(ReviewLiner src/ReviewLiner.cpp)
target_link_libraries(ReviewLiner
        PRIVATE
        ds::linear)
add_executable(chapter_1_introduction src/chapter_1_introduction.cpp)
target_link_libraries(chapter_1_introduction
        PRIVATE
        ds::linear)

add_executable(chapter_2_vector src/chapter_2_vector.cpp)
target_link_libraries(chapter_2_vector
        PRIVATE
        ds::linear)

add_executable(chapter_3_list src/chapter_3_list.cpp)
target_link_libraries(chapter_3_list
        PRIVATE
        ds::linear)

add_executable(chapter_4_stack_queue src/chapter_4_stack_queue.cpp)
target_link_libraries(chapter_4_stack_queue
        PRIVATE
        ds::linear)



