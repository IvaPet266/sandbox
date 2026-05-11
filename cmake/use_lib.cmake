function(
  use_lib
  LIB_TARGET
  RESULT_VAR
)
  set(SOURCE_DIR  "${CMAKE_SOURCE_DIR}/src/${LIB_TARGET}")
  set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/${LIB_TARGET}")

  file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp")

  if(NOT SOURCE_FILES)

    set(${RESULT_VAR} "" PARENT_SCOPE)
    message(FATAL_ERROR "В ${SOURCE_DIR} не найдены .cpp файлы")
    return()
    
  endif()

  add_library(${LIB_TARGET} STATIC ${SOURCE_FILES})
  target_include_directories(${LIB_TARGET} PUBLIC ${INCLUDE_DIR})
  
  message(STATUS "Статическая библиотека ${LIB_TARGET} создана из ${SOURCE_DIR}, include: ${INCLUDE_DIR}")
  
  set(${RESULT_VAR} ${LIB_TARGET} PARENT_SCOPE)

endfunction()