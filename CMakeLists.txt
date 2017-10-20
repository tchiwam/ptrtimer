cmake_minimum_required (VERSION 2.6)
project (ptrtimer)

set (ptrtimer_VERSION_MAJOR 1)
set (ptrtimer_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}"
                    "${PROJECT_SOURCE_DIR}/include")

add_library(ptrtimer lib/ptrtimer.c)
add_executable(Test1 test/Test1.c)
target_link_libraries (Test1  ptrtimer)

install (TARGETS ptrtimer DESTINATION lib)
install (FILES "${PROJECT_SOURCE_DIR}/include/ptrtimer.h" DESTINATION include)
