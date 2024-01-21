#!/bin/bash

build_prx () {
  if [ ! -d build_$1 ]; then
    mkdir build_$1
  fi

  cd build_$1
  cmake ../$1
  make install

  if [ $? != 0 ]; then
    exit 1
  fi

  cd ../
}

build_prx SceZlib
build_prx SceLibPng
build_prx SceLibJpeg
build_prx SceLibVita2d
build_prx SceLibYaml
