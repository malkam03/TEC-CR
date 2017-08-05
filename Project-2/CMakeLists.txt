cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )
if( OpenCV_FOUND)
	include_directories(
						${OpenCV_INCLUDE_DIRS})
	add_executable(run main.cpp)
	target_link_libraries(run  
									${OpenCV_LIBS})
endif()