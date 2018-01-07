SET(
  SOURCES

  Camera.cpp
  Engine.cpp
  Exception.cpp
  Shader.cpp
)


add_library(libSolarSystem STATIC ${SOURCES})

target_include_directories(libSolarSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})