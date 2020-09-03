# compiler

# Как установить:

 - Скачать Antlr.jar [с сайта](https://www.antlr.org/download/antlr-4.8-complete.jar)
 
# На Linux:

- Перейти на [гит](https://github.com/antlr/antlr4/tree/master/runtime/Cpp), скачать папку Cpp и следовать указаниям ниже

      cd /runtime/Cpp (где находится readme)
      mkdir build && mkdir run && cd build
      cmake .. -DANTLR_JAR_LOCATION=(путь)/antlr.jar -DWITH_DEMO=True
      make
      DESTDIR=(путь до или как у меня без)/Cpp/run make install
      
- Далее в папке [demo](https://github.com/antlr/antlr4/tree/master/runtime/Cpp/demo) выполнить дополнительные шаги

- Откорректировать файл generate.sh:

      #!/bin/bash
      set -o errexit

      # Created 2016, Mike Lischke (public domain)

      # This script is used to generate source files from the test grammars in the same folder. The generated files are placed
      # into a subfolder "generated" which the demo project uses to compile a demo binary.

      # 1) Running from jar. Use the given jar (or replace it by another one you built or downloaded) for generation.
      LOCATION=antlr.jar
      java -jar $LOCATION -Dlanguage=Cpp -listener -visitor -o generated/ -package antlrcpptest TLexer.g4 TParser.g4

      
- Перейти в папку cmake и следовать дальнейшим указаниям

      Создать source folder например ~/srcfolder/
      Создать подпапку cmake
      Скопировать файлы из cmake в srcfolder/cmake
      Код ниже вставить в srcfolder/CMakeLists.txt
      Взять main.cpp, TLexer.g4 and TParser.g4 to ./srcfolder/ в папке Cpp
      Создать build folder например  ~/build/
      И из нее (build), запусить cmake ~/srcfolder; make
      
- Код в srcfolder/CMakeLists.txt (внимание к путям и к имени проекта) :      

      # minimum required CMAKE version
      CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

      list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

      # compiler must be 11 or 14
      set(CMAKE_CXX_STANDARD 11)

      # required if linking to static library
      add_definitions(-DANTLR4CPP_STATIC)

      # using /MD flag for antlr4_runtime (for Visual C++ compilers only)
      set(ANTLR4_WITH_STATIC_CRT OFF)
      # add external build for antlrcpp
      include(ExternalAntlr4Cpp)
      # add antrl4cpp artifacts to project environment
      include_directories(${ANTLR4_INCLUDE_DIRS})

      # set variable pointing to the antlr tool that supports C++
      # this is not required if the jar file can be found under PATH environment

      
      set(ANTLR_EXECUTABLE /home/llen/antlr-4.8-complete.jar)
      # add macros to generate ANTLR Cpp code from grammar
      find_package(ANTLR REQUIRED)

      # Call macro to add lexer and grammar to your build dependencies.
      antlr_target(SampleGrammarLexer TLexer.g4 LEXER
                   PACKAGE antlrcpptest)
      antlr_target(SampleGrammarParser TParser.g4 PARSER
                   PACKAGE antlrcpptest
                   DEPENDS_ANTLR SampleGrammarLexer
                   COMPILE_FLAGS -lib ${ANTLR_SampleGrammarLexer_OUTPUT_DIR})

      # include generated files in project environment
      include_directories(${ANTLR_SampleGrammarLexer_OUTPUT_DIR})
      include_directories(${ANTLR_SampleGrammarParser_OUTPUT_DIR})

      # add generated grammar to demo binary target
      add_executable(demo main.cpp
                     ${ANTLR_SampleGrammarLexer_CXX_OUTPUTS}
                     ${ANTLR_SampleGrammarParser_CXX_OUTPUTS})
      target_link_libraries(demo antlr4_static)

- После последнего шага можно запустить пример в консоли или открыть папку srcfolder в CLion.
