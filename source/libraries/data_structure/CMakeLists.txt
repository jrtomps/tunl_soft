
set(data_structure_SOURCES
  DataStructure.cc
  DataStructureDict.cxx)

set(data_structure_HEADERS
  DataStructure.hh)

ROOT_GENERATE_DICTIONARY(DataStructureDict ${data_structure_HEADERS} LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/DataStructureLinkDef.h OPTIONS -c)

add_library(data_structure SHARED ${data_structure_SOURCES})

install(TARGETS data_structure LIBRARY DESTINATION lib)
install(FILES ${data_structure_HEADERS} DESTINATION include)
install(FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/libDataStructureDict_rdict.pcm
  ${CMAKE_CURRENT_BINARY_DIR}/libDataStructureDict.rootmap 
  DESTINATION lib)
