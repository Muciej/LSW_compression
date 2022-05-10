cmake_minimum_required(VERSION 3.16)
project(Lista_3)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-c
        -Wall
        -Wextra
        -Winit-self
        -Wold-style-cast
        -Woverloaded-virtual
        -Wuninitialized
        -pedantic
        -std=c++17
        -g)

add_executable(Coder
        Coder/Coder.cpp
        Coder/DigitCoders/DigitCoder.h
        Coder/DigitCoders/EliasDelta.h
        Coder/DigitCoders/EliasOmega.h
        Coder/DigitCoders/EliasGamma.h
        Coder/DigitCoders/FibbCoder.h
        Coder/DigitCoders/TestCoder.h)

add_executable(Decoder
        Decoder/Decoder.cpp
        Decoder/BitReader.h
        Decoder/DigitDecoders/DigitDecoder.h
        Decoder/DigitDecoders/EliasGamma.h
        Decoder/DigitDecoders/EliasDelta.h
        Decoder/DigitDecoders/EliasOmega.h
        Decoder/DigitDecoders/TestDecoder.h
        Decoder/DigitDecoders/FibbCoder.h
        )
