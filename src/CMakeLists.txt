cmake_minimum_required(VERSION 3.10)

project(Curse)

set(CMAKE_CXX_STANDARD 20)

set(DEP_PATH ${CMAKE_SOURCE_DIR}/../dep/)

include_directories(${DEP_PATH})

add_subdirectory(CurseLib)
include_directories( ${CMAKE_SOURCE_DIR} )

add_executable(Curse_docktests Curse_docktests.cpp)

target_link_libraries(Curse_docktests PUBLIC HexDec)
target_link_libraries(Curse_docktests PUBLIC OWS)
target_link_libraries(Curse_docktests PUBLIC Binary)

install(DIRECTORY ${DEP_PATH}/Input DESTINATION $<TARGET_FILE_DIR:Curse_docktests>)
install(DIRECTORY ${DEP_PATH}/Right_answers DESTINATION $<TARGET_FILE_DIR:Curse_docktests>)
install(FILES ${DEP_PATH}/Test_Table.tbl DESTINATION $<TARGET_FILE_DIR:Curse_docktests>)
install(DIRECTORY ${DEP_PATH}/Output DESTINATION $<TARGET_FILE_DIR:Curse_docktests>)