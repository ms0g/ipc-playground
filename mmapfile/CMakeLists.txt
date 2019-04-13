project(mmapfile)

configure_file(test.txt test.txt COPYONLY)
add_executable(mmapfile mmapfile.c)
target_link_libraries(mmapfile pthread)