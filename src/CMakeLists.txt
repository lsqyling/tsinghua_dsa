# add all cpp files
file(GLOB_RECURSE src_list
        LIST_DIRECTORIES false
        CONFIGURE_DEPENDS *.cpp
)

target_sources(dsa
        PRIVATE
        ${src_list}
)