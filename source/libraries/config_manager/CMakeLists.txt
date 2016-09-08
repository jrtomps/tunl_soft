
set(config_manager_SOURCES 
  ConfigElements.cc
  ConfigManager.cc)

set(config_manager_HEADERS
  ConfigElements.hh
  ConfigManager.hh)

add_library(config_manager SHARED ${config_manager_SOURCES})

install(TARGETS config_manager LIBRARY DESTINATION lib)
install(FILES ${config_manager_HEADERS} DESTINATION include)
