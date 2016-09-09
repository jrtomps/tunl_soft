
set(config_manager_SOURCES 
  ConfigElements.cc
  ConfigManager.cc)

set(config_manager_HEADERS
  ConfigElements.hh
  ConfigManager.hh)

find_package(ROOT CONFIG REQUIRED COMPONENTS XMLIO)
include(${ROOT_USE_FILE})

add_library(config_manager SHARED ${config_manager_SOURCES})
target_link_libraries(config_manager ${ROOT_LIBRARIES})

install(TARGETS config_manager LIBRARY DESTINATION lib)
install(FILES ${config_manager_HEADERS} DESTINATION include)
