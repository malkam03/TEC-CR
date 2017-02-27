cmake_minimum_required(VERSION 3.5)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.36.0 COMPONENTS program_options)
find_package( OpenCV REQUIRED )
if(Boost_FOUND AND OpenCV_FOUND)
	include_directories(${Boost_INCLUDE_DIRS}  	
						${OpenCV_INCLUDE_DIRS})
	add_executable(problem3 Problem3.cpp)
	target_link_libraries(problem3  ${Boost_LIBRARIES}
									${OpenCV_LIBS})
endif()