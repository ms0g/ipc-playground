project(posix_sem)

add_executable(posix_sem posix_sem.c)
target_link_libraries(posix_sem pthread)