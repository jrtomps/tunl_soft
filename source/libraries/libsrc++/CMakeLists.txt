
set(src++_SOURCES
  evioUtil.cc)

set(src++_HEADERS 
  evioUtil.hxx)

include_directories(${CMAKE_SOURCE_DIR}/source/libraries/libsrc
                    ${CMAKE_CURRENT_SOURCE_DIR})


add_library(src++ SHARED ${src++_SOURCES})
target_link_libraries(src++ src)

install(TARGETS src++ LIBRARY DESTINATION lib)
install(FILES ${src++_HEADERS} DESTINATION include)
