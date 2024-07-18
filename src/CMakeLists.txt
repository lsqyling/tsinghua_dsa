# add all cpp files
file(GLOB_RECURSE src_list
        LIST_DIRECTORIES false
        CONFIGURE_DEPENDS *.cpp
)

target_sources(dsa_objs
        PRIVATE
        ${src_list}
)