# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/QLion_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/QLion_autogen.dir/ParseCache.txt"
  "QLion_autogen"
  )
endif()
