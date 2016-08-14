cmake_minimum_required(VERSION 3.1.3)
project(MazeGen CXX)

# -------- ENGINE CMAKE --------

#Set XCode to use C++11, otherwise undefined nullptr
set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")

set(EngineSourceDir "${CMAKE_CURRENT_LIST_DIR}/Engine/Source")
set(EngineExtLibDir "${CMAKE_CURRENT_LIST_DIR}/Engine/3rdParty")
file(GLOB_RECURSE EngineHeaders LIST_DIRECTORIES false "${EngineSourceDir}/*.h")
file(GLOB_RECURSE EngineSourceFiles LIST_DIRECTORIES false "${EngineSourceDir}/*.cpp")
set_source_files_properties(${EngineHeaders} PROPERTIES XCODE_EXPLICIT_FILE_TYPE sourcecode.cpp.h)
set(EngineFiles ${EngineHeaders} ${EngineSourceFiles})

if(APPLE)
    file(GLOB_RECURSE MMSourceFiles LIST_DIRECTORIES false "${EngineSourceDir}/*.mm")
    set(EngineFiles ${EngineFiles} ${MMSourceFiles})
    file(GLOB_RECURSE WindowsFiles LIST_DIRECTORIES false "${EngineSourceDir}/Engine/Platform/Windows/*.*")
    list(REMOVE_ITEM EngineFiles ${WindowsFiles})
    file(GLOB_RECURSE VulkanFiles LIST_DIRECTORIES false "${EngineSourceDir}/Engine/Graphics/Vulkan/*.*")
    list(REMOVE_ITEM EngineFiles ${VulkanFiles})
    find_library(OSXCocoaLib Cocoa)
    find_library(OSXOpenGLLib OpenGL)
    find_library(OSXCoreVideoLib CoreVideo)
    mark_as_advanced(OSXCocoaLib OSXOpenGLLib OSXCoreVideoLib)
    set(LinkLibs ${LinkLibs} ${OSXCocoaLib} ${OSXOpenGLLib} ${OSXCoreVideoLib})
endif(APPLE)

if(WIN32)
    file(GLOB_RECURSE MacOSXFiles LIST_DIRECTORIES false "${EngineSourceDir}/Engine/Platform/MacOSX/*.*")
    list(REMOVE_ITEM EngineFiles ${MacOSXFiles})
    find_package(OpenGL REQUIRED)
    set(LinkLibs ${LinkLibs} ${OPENGL_gl_LIBRARY})
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

foreach(SourceFile IN ITEMS ${EngineFiles})
    get_filename_component(FilePath "${SourceFile}" PATH)
    file(RELATIVE_PATH FilePathRel ${EngineSourceDir} ${FilePath})
    string(REPLACE "/" "\\" GroupPath "${FilePathRel}")
    source_group("${GroupPath}" FILES "${SourceFile}")
endforeach()

include_directories(AFTER "${EngineSourceDir}")
include_directories(AFTER "${EngineExtLibDir}/Include")

# -------- PROJECT CMAKE --------

set(SourceDir "${CMAKE_CURRENT_LIST_DIR}/Source")
set(ExtLibDir "${CMAKE_CURRENT_LIST_DIR}/3rdParty")
file(GLOB_RECURSE CPPHeaderFiles LIST_DIRECTORIES false "${SourceDir}/*.h")
set_source_files_properties(${CPPHeaderFiles} PROPERTIES XCODE_EXPLICIT_FILE_TYPE sourcecode.cpp.h)
file(GLOB_RECURSE CPPSourceFiles LIST_DIRECTORIES false "${SourceDir}/*.cpp")
include_directories(AFTER "${SourceDir}")
include_directories(AFTER "${ExtLibDir}/Include")
set(SourceFiles ${CPPHeaderFiles} ${CPPSourceFiles})
foreach(SourceFile IN ITEMS ${SourceFiles})
    get_filename_component(FilePath "${SourceFile}" PATH)
    file(RELATIVE_PATH FilePathRel ${SourceDir} ${FilePath})
    string(REPLACE "/" "\\" GroupPath "${FilePathRel}")
    source_group("${GroupPath}" FILES "${SourceFile}")
endforeach()
add_definitions(-DMAIN_APP_CLASS=MazeGen)
include_directories(AFTER "${SourceDir}")

# -------- EXECUTABLE --------

set(SourceFiles ${SourceFiles} ${EngineFiles})
add_executable(MazeGen WIN32 MACOSX_BUNDLE "${SourceFiles}")
target_link_libraries(MazeGen "${LinkLibs}")

if(APPLE)
    set_target_properties(MazeGen PROPERTIES MACOSX_BUNDLE_INFO_PLIST Resources/MacOSX/Info.plist.in)
endif()
