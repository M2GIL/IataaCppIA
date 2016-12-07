cmake_minimum_required(VERSION 3.6)
project(checkers_rest_ia_c)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp domain/enumeration/State.h domain/Beach.cpp domain/Beach.h domain/enumeration/State.cpp DTO/AbstractDTO.h DTO/StatusDTO.h DTO/AbstractDTO.cpp domain/tools/randomTextGenerator.h domain/enumeration/FalseEnum.h domain/enumeration/Difficulty.cpp domain/enumeration/Difficulty.h domain/enumeration/Player.cpp domain/enumeration/Player.h)
add_executable(checkers_rest_ia_c ${SOURCE_FILES})
target_link_libraries(checkers_rest_ia_c net_static pthread)