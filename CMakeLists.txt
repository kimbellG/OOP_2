cmake_minimum_required(VERSION 3.0)	  #Указываем версию сmake
project(result VERSION 1 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_executable(${PROJECT_NAME} main.cpp src/gym.cpp)  #Указываем результат работы и все исходники

set_target_properties(${PROJECT_NAME} 
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/debug"
) #Устанавливаю директорию с исполняемым файлом

include_directories(bprinter-master/include)

add_library(bprinter STATIC
  bprinter-master/include/bprinter/table_printer.h
  bprinter-master/include/bprinter/impl/table_printer.tpp.h
  bprinter-master/src/table_printer.cpp
)


target_link_libraries(result bprinter)
include_directories(bprinter-master/include)
include_directories(include/)


