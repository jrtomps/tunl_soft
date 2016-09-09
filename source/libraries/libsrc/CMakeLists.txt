
set(src_SOURCES
  evio.c
  evioswap.c
  evio_util.c
  swap_util.c
  xml_util.c)

set(src_HEADERS 
  evio.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${EXPAT_INCLUDE_DIRS})

add_library(src SHARED ${src_SOURCES})
target_link_libraries(src ${EXPAT_LIBRARIES})

install(TARGETS src LIBRARY DESTINATION lib)
install(FILES ${src_HEADERS} DESTINATION include)
