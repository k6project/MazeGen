cmake_minimum_required(VERSION 3.1.3)
project (MazeGen CXX)

set(SourceDir "${CMAKE_CURRENT_LIST_DIR}/Source")
set(ExtLibDir "${CMAKE_CURRENT_LIST_DIR}/3rdParty")

file(GLOB_RECURSE SourceFiles LIST_DIRECTORIES false "${SourceDir}/*.*")

#Set XCode to use C++11, otherwise undefined nullptr
set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")

add_executable(MazeGen WIN32 MACOSX_BUNDLE "${SourceFiles}")
target_link_libraries(MazeGen "${LinkLibs}")

include_directories(AFTER "${SourceDir}")
include_directories(AFTER "${ExtLibDir}/Include")

#Setup IDE subfolders for all sources and headers
foreach(SourceFile IN ITEMS ${SourceFiles})
    get_filename_component(FilePath "${SourceFile}" PATH)
    file(RELATIVE_PATH FilePathRel ${SourceDir} ${FilePath})
    string(REPLACE "/" "\\" GroupPath "${FilePathRel}")
    source_group("${GroupPath}" FILES "${SourceFile}")
endforeach()
