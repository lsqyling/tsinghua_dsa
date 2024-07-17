project(tree)

add_library(${PROJECT_NAME} STATIC
        src/AVLTreeTesting.cpp
        src/BinarySearchTreeTesting.cpp
        src/BinaryTreeTesting.cpp
        src/DeductionTest.cpp
        src/TreeReview.cpp
        src/Widget.cpp
        src/huffman.cpp
        )
add_library(ds::tree ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )


add_executable(BinaryTreeTesting src/BinaryTreeTesting.cpp)
add_executable(TreeReview src/TreeReview.cpp)
add_executable(DeductionTest src/DeductionTest.cpp)
add_executable(Widget src/Widget.cpp)
target_link_libraries(Widget TreeStructure pthread rt)
add_executable(BinarySearchTreeTesting src/BinarySearchTreeTesting.cpp)
add_executable(AVLTreeTesting src/AVLTreeTesting.cpp)

add_executable(chapter_5_7_8_binary_tree src/chapter_5_7_8_binary_tree.cpp)
target_link_libraries(chapter_5_7_8_binary_tree
        PRIVATE
        ds::tree)





