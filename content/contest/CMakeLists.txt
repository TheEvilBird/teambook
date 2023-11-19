set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -g -fsanitize=address,undefined,bounds -D_GLIBCXX_DEBUG")

file(GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach(sourcefile ${APP_SOURCES})
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file} ${sourcefile})
endforeach(sourcefile ${APP_SOURCES})