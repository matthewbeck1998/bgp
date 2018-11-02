cmake_minimum_required(VERSION 3.7)
project(Project)

set(CMAKE_CXX_STANDARD 11)

# Symbol Table

set(SYMBOL_TABLE funcTest.cpp SymbolNode.cpp SymbolNode.h SymbolTable.cpp SymbolTable.h)
add_executable(SymbolTable ${SYMBOL_TABLE})

# Scanner/Parser

find_package(BISON)
find_package(FLEX)
BISON_TARGET(MyParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(MyScanner scanner.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
add_executable(bgp SymbolTable.cpp SymbolTable.h SymbolNode.cpp SymbolNode.h AST.cpp AST.h ASTNode.cpp ASTNode.h
${BISON_MyParser_OUTPUTS}
${FLEX_MyScanner_OUTPUTS}
)