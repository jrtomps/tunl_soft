
set(coda2root_SOURCES
  coda2root.cc
  DataManager.cc
  NodeProcessor.cc)

include_directories(${CMAKE_SOURCE_DIR}/source/libraries/libsrc
${CMAKE_SOURCE_DIR}/source/libraries/libsrc++
${CMAKE_SOURCE_DIR}/source/libraries/mapped_data
${CMAKE_SOURCE_DIR}/source/libraries/config_manager
${CMAKE_SOURCE_DIR}/source/libraries/data_structure
${CMAKE_CURRENT_SOURCE_DIR}
${ROOT_INCLUDE_DIRS})

add_executable(coda2root ${coda2root_SOURCES})
target_link_libraries(coda2root src src++ mapped_data config_manager data_structure ${ROOT_LIBRARIES})

install(TARGETS coda2root RUNTIME DESTINATION bin)
