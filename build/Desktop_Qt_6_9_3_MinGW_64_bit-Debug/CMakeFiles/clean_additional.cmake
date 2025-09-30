# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Homework_1_Computer_Graphic_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Homework_1_Computer_Graphic_autogen.dir\\ParseCache.txt"
  "Homework_1_Computer_Graphic_autogen"
  )
endif()
