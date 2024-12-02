cmake_minimum_required(VERSION 3.10)
project(AdventOfCode)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add utility library
add_library(utils STATIC utils/utils.cpp)
target_include_directories(utils PUBLIC utils)

# Check if DAY and PART parameters are provided, otherwise give an error
if(NOT DAY OR NOT PART)
  message(FATAL_ERROR "Both DAY and PART must be specified!")
endif()

# Add a function to compile the specific part of a day
function(compile_day_part day part)
  set(SOURCE_FILE "day${day}/part${part}.cpp")

  # Add the executable target for the day and part
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/day${day})
  add_executable(day${day}_part${part} ${SOURCE_FILE})

  # Link the executable with the utility library
  target_link_libraries(day${day}_part${part} utils)

  file(GLOB TXT_FILES "day${day}/*.txt")
  foreach(txt_file ${TXT_FILES})
    get_filename_component(txt_filename ${txt_file} NAME)
    add_custom_command(TARGET day${day}_part${part} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${txt_file} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${txt_filename}
    )
  endforeach()
endfunction()

# Compile the specific day and part based on parameters
compile_day_part(${DAY} ${PART})
