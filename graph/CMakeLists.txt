project(graph)

add_library(${PROJECT_NAME} STATIC
        src/chapter_6_graph.cpp
        src/GraphReview.cpp
        )

add_library(ds::graph ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include)

add_executable(GraphReview src/GraphReview.cpp)

add_executable(chapter_6_graph src/chapter_6_graph.cpp)
target_link_libraries(chapter_6_graph
        PRIVATE
        ds::graph)


