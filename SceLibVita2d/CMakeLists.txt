cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(SceLibVita2d)
include("${VITASDK}/share/vita.cmake" REQUIRED)
include(ExternalProject)

set(CMAKE_C_FLAGS "-Wl,-q -Wall -O2 -nostdlib -fno-inline -I${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/include")

enable_language(C ASM)

ExternalProject_add(libvita2d_download
  GIT_REPOSITORY https://github.com/xerpi/libvita2d
  GIT_TAG "master"
  DOWNLOAD_DIR ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  COMMAND ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/libvita2d/include/vita2d.h ${VITASDK}/arm-vita-eabi/include/vita2d.h
)

set(libvita2d_src
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d_texture.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d_draw.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/utils.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d_image_png.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d_image_jpeg.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d_image_bmp.c
  #${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d_font.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d_pgf.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/vita2d_pvf.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/bin_packing_2d.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/texture_atlas.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/source/int_htab.c
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/shader/compiled/clear_v_gxp.o
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/shader/compiled/clear_f_gxp.o
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/shader/compiled/color_v_gxp.o
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/shader/compiled/color_f_gxp.o
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/shader/compiled/texture_v_gxp.o
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/shader/compiled/texture_f_gxp.o
  ${CMAKE_CURRENT_BINARY_DIR}/libvita2d_download-prefix/src/libvita2d_download/libvita2d/shader/compiled/texture_tint_f_gxp.o
)

add_custom_command(
  OUTPUT ${libvita2d_src}
  DEPENDS ${libvita2d_download}
  COMMAND ""
)

link_directories(
  ${CMAKE_INSTALL_PREFIX}/lib
)

add_executable(${PROJECT_NAME}
  src/main.c
  ${libvita2d_src}
)

target_link_libraries(${PROJECT_NAME}
  SceLibPng_stub
  SceLibJpeg_stub
  SceSysmem_stub
  SceCommonDialog_stub
  SceDisplay_stub
  SceAppMgr_stub
  ScePgf_stub
  ScePvf_stub
  SceGxm_stub
  SceLibKernel_stub
  SceSysmodule_stub
  SceIofilemgr_stub
  SceLibc_stub
  SceRtabi_stub
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-D__PSP2_USER__"
)

vita_create_self(libvita2d.suprx ${PROJECT_NAME}
  CONFIG exports.yml
  UNSAFE
  STRIPPED
  REL_OPTIMIZE
)

vita_create_stubs(stubs_${PROJECT_NAME} ${PROJECT_NAME} exports.yml)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libSceLibVita2d_stub.a ${CMAKE_CURRENT_BINARY_DIR}/libSceLibVita2d_stub_weak.a
  DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libvita2d.suprx
  DESTINATION ${VITASDK}/prx
)
