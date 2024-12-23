cmake_minimum_required(VERSION 3.16)
project(cellls LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.1)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
				src/main.cpp
				src/Screen.hpp
				src/Screen.cpp
				src/world/World.hpp
				src/world/World.cpp	
				src/world/Cell.hpp
				src/world/Cell.cpp	
				src/world/Organella.hpp
				src/world/Organella.cpp		
				src/math/math.hpp
				src/math/math.cpp
				)
				
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()