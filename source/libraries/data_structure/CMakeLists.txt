
set(data_structure_SOURCES
  DataStructure.cc
  )


set(data_structure_HEADERS
  DataStructure.hh
  )

add_library(data_structure SHARED ${data_structure_SOURCES})

install(TARGETS data_structure LIBRARY DESTINATION lib)
install(FILES ${data_structure_HEADERS} DESTINATION include)
