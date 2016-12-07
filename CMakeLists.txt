cmake_minimum_required(VERSION 3.6)
project(iataa_c++)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp domain/enumeration/State.h domain/Beach.cpp domain/Beach.h domain/enumeration/State.cpp DTO/AbstractDTO.h DTO/StatusDTO.h DTO/AbstractDTO.cpp domain/tools/RandomTextGenerator.h domain/enumeration/FalseEnum.h domain/enumeration/Difficulty.cpp domain/enumeration/Difficulty.h domain/enumeration/Player.cpp domain/enumeration/Player.h domain/enumeration/CodeEndGame.cpp domain/enumeration/CodeEndGame.h domain/enumeration/BoardSquareType.cpp domain/enumeration/BoardSquareType.h domain/tools/Converter.cpp domain/tools/Converter.h DTO/MoveDTO.h REST/AIHandler.cpp)
add_executable(iataa_c++ ${SOURCE_FILES})
target_link_libraries(iataa_c++ net_static pthread)