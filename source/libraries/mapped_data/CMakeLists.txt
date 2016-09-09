
set(mapped_data_SOURCES 
  MappedData.cc)

set(mapped_data_HEADERS
  MappedData.hh)

include_directories(${CMAKE_SOURCE_DIR}/source/libraries/data_structure
                    ${CMAKE_SOURCE_DIR}/source/libraries/config_manager)

add_library(mapped_data SHARED ${mapped_data_SOURCES})

install(TARGETS mapped_data LIBRARY DESTINATION lib)
install(FILES ${mapped_data_HEADERS} DESTINATION include)
