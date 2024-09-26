cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(
	minisim
	VERSION 0.1
	DESCRIPTION "A Basic C++ Solar Car Physics Simulator"
	LANGUAGES
		CXX
)

# We Use C++20 Whenever Possible
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# We don't want compiler-specific extensions be be accessible
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(minisim minisim.cpp)
