cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(SceLibJpeg)
include("${VITASDK}/share/vita.cmake" REQUIRED)
include(ExternalProject)

set(CMAKE_C_FLAGS "-Wl,-q -Wall -Os -nostdlib -fno-inline -I${CMAKE_CURRENT_SOURCE_DIR}/src/")

# set(VITA_ELF_CREATE_FLAGS "${VITA_ELF_CREATE_FLAGS} -vvv")
# set(VITA_MAKE_FSELF_FLAGS "${VITA_MAKE_FSELF_FLAGS} -a 0x2808000000000000")

enable_language(C ASM)

# set(JPEG_LIB_VERSION 100)

ExternalProject_add(libjpeg_download
  GIT_REPOSITORY https://github.com/libjpeg-turbo/libjpeg-turbo
  GIT_TAG "2.1.5.1"
  DOWNLOAD_DIR ""
  PATCH_COMMAND patch -d <SOURCE_DIR> -p3 -t -N < ${PROJECT_SOURCE_DIR}/libjpeg.patch
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/jpeglib.h <SOURCE_DIR>/jmorecfg.h <SOURCE_DIR>/jerror.h ${CMAKE_CURRENT_SOURCE_DIR}/src/jconfig.h ${VITASDK}/arm-vita-eabi/include/
)

set(LIBJPEG_SRC
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcapimin.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcapistd.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jccoefct.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jccolor.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcdctmgr.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jchuff.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcicc.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcinit.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcmainct.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcmarker.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcmaster.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcomapi.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcparam.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcphuff.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcprepct.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcsample.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jctrans.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdapimin.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdapistd.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdatadst.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdatasrc.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdcoefct.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdcolor.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jddctmgr.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdhuff.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdicc.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdinput.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdmainct.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdmarker.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdmaster.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdmerge.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdphuff.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdpostct.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdsample.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdtrans.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jerror.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jfdctflt.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jfdctfst.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jfdctint.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jidctflt.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jidctfst.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jidctint.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jidctred.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jquant1.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jquant2.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jutils.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jmemmgr.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jmemnobs.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jsimd_none.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jcarith.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jdarith.c
  ${CMAKE_CURRENT_BINARY_DIR}/libjpeg_download-prefix/src/libjpeg_download/jaricom.c
)

add_custom_command(
  OUTPUT ${LIBJPEG_SRC}
  DEPENDS ${libjpeg_download}
)

link_directories(
  # ../kernel/build/stubs/
)

add_executable(${PROJECT_NAME}
  src/main.c
  ${LIBJPEG_SRC}
)

target_link_libraries(${PROJECT_NAME}
  SceLibc_stub
  SceRtabi_stub
  SceLibKernel_stub
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-D__PSP2_USER__ -DNO_GETENV -DNO_PUTENV"
)

vita_create_self(libjpeg.suprx ${PROJECT_NAME}
  CONFIG exports.yml
  UNSAFE
  STRIPPED
  REL_OPTIMIZE
)

vita_create_stubs(stubs_${PROJECT_NAME} ${PROJECT_NAME} exports.yml)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libSceLibJpeg_stub.a ${CMAKE_CURRENT_BINARY_DIR}/libSceLibJpeg_stub_weak.a
  DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libjpeg.suprx
  DESTINATION ${VITASDK}/prx
)
