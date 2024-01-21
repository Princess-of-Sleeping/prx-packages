cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(SceZlib)
include("${VITASDK}/share/vita.cmake" REQUIRED)
include(ExternalProject)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O2 -fno-inline -fno-builtin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

enable_language(C ASM)

#
# PSP2 System uses version 1.2.5 zlib.
# but version 1.2.5 doesn't have inflateValidate function.
# So we need version 1.3 (for libpng etc).
#
ExternalProject_add(libz_download
  #URL https://www.zlib.net/fossils/zlib-1.2.5.tar.gz
  #URL_HASH SHA256=6064E52E513FACB0FBB7998C6413406CF253CFB986063D68F4771C2BF7A3F958
  URL https://zlib.net/zlib-1.3.1.tar.gz
  URL_HASH SHA256=9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23
  DOWNLOAD_DIR ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/zlib.h <SOURCE_DIR>/zconf.h ${VITASDK}/arm-vita-eabi/include/
)

set(libz_src
  libz_download-prefix/src/libz_download/adler32.c
  libz_download-prefix/src/libz_download/compress.c
  libz_download-prefix/src/libz_download/crc32.c
  libz_download-prefix/src/libz_download/deflate.c
  # libz_download-prefix/src/libz_download/gzclose.c
  # libz_download-prefix/src/libz_download/gzlib.c
  # libz_download-prefix/src/libz_download/gzread.c
  # libz_download-prefix/src/libz_download/gzwrite.c
  libz_download-prefix/src/libz_download/infback.c
  libz_download-prefix/src/libz_download/inffast.c
  libz_download-prefix/src/libz_download/inflate.c
  libz_download-prefix/src/libz_download/inftrees.c
  libz_download-prefix/src/libz_download/trees.c
  libz_download-prefix/src/libz_download/uncompr.c
  libz_download-prefix/src/libz_download/zutil.c
)

add_custom_command(
  OUTPUT ${libz_src}
  DEPENDS ${libz_download}
)

include_directories(
)

add_executable(${PROJECT_NAME}
  src/main.c
  ${libz_src}
)

target_link_libraries(${PROJECT_NAME}
  SceLibc_stub
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-D__PSP2_USER__"
)

vita_create_self(zlib.suprx ${PROJECT_NAME}
  CONFIG exports.yml
  STRIPPED
  REL_OPTIMIZE
)

vita_create_stubs(stub_${PROJECT_NAME} ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/exports.yml)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libSceZlib_stub.a ${CMAKE_CURRENT_BINARY_DIR}/libSceZlib_stub_weak.a
  DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/zlib.suprx
  DESTINATION ${VITASDK}/prx
)
