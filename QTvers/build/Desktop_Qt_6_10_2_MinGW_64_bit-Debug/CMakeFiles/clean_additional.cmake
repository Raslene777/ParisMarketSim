# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QTvers_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QTvers_autogen.dir\\ParseCache.txt"
  "QTvers_autogen"
  )
endif()
