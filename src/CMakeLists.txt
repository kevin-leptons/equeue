file(GLOB EQUEUE_SRC_FILES lib/*.c)
add_library(equeue SHARED ${EQUEUE_SRC_FILES})

file(GLOB EXE_SRC_FILES imp/*.c)
foreach(EXE_SRC_FILE ${EXE_SRC_FILES})
    get_filename_component(EXE_DEST_FILE ${EXE_SRC_FILE} NAME_WE)
    add_executable(${EXE_DEST_FILE} ${EXE_SRC_FILE})
    target_link_libraries(${EXE_DEST_FILE} equeue)
endforeach()

install(TARGETS equeue DESTINATION /usr/lib)
