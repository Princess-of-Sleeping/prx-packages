cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(SceLibCapstone)
include("${VITASDK}/share/vita.cmake" REQUIRED)
include(ExternalProject)

set(CMAKE_C_FLAGS "-Wl,-q -Wall -O2 -nostdlib -fno-inline")

# set(VITA_ELF_CREATE_FLAGS "${VITA_ELF_CREATE_FLAGS} -vvv")
# set(VITA_MAKE_FSELF_FLAGS "${VITA_MAKE_FSELF_FLAGS} -a 0x2808000000000000")

enable_language(C ASM)

ExternalProject_add(capstone_download
  GIT_REPOSITORY https://github.com/capstone-engine/capstone
  GIT_TAG "0a29bf80017b8422c79ba51e3ad5c34ba5ee6142"
  DOWNLOAD_DIR ""
  PATCH_COMMAND patch -d <SOURCE_DIR> -p3 -t -N < ${PROJECT_SOURCE_DIR}/libcapstone.patch
  PATCH_COMMAND
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

set(CAPSTONE_SRC
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/cs.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/SStream.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/MCInst.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/MCInstrDesc.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/Mapping.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/MCRegisterInfo.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/MCInstPrinter.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/utils.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/arch/ARM/ARMBaseInfo.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/arch/ARM/ARMDisassembler.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/arch/ARM/ARMDisassemblerExtension.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/arch/ARM/ARMInstPrinter.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/arch/ARM/ARMMapping.c
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/arch/ARM/ARMModule.c
)

add_custom_command(
  OUTPUT ${CAPSTONE_SRC}
  DEPENDS ${capstone_download}
)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/capstone_download-prefix/src/capstone_download/include
)

link_directories(
  # ../kernel/build/stubs/
)

add_executable(${PROJECT_NAME}
  src/main.c
  src/libc_bridge.s
  ${CAPSTONE_SRC}
)

target_link_libraries(${PROJECT_NAME}
  SceLibKernel_stub
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-D__PSP2_USER__ -DNDEBUG -DCAPSTONE_DEBUG -DCAPSTONE_HAS_ARM"
)

vita_create_self(libcapstone.suprx ${PROJECT_NAME}
  CONFIG exports.yml
  UNSAFE
  STRIPPED
  REL_OPTIMIZE
)

vita_create_stubs(stubs_${PROJECT_NAME} ${PROJECT_NAME} exports.yml)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libSceLibCapstone_stub.a ${CMAKE_CURRENT_BINARY_DIR}/libSceLibCapstone_stub_weak.a
  DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libcapstone.suprx
  DESTINATION ${VITASDK}/prx
)
