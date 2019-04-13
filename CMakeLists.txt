cmake_minimum_required(VERSION 3.0)

project(ipc)

add_subdirectory(fifo)
add_subdirectory(file_locking)
add_subdirectory(message_queue)
add_subdirectory(mmapfile)
add_subdirectory(pipe)
add_subdirectory(posix_sem)
add_subdirectory(shared_memory)
add_subdirectory(signal)
add_subdirectory(uds)
add_subdirectory(xsi_sem)