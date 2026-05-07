cmake_minimum_required(VERSION 3.23)

add_executable(nudny_base_UT
	src/nudny_base_test.cpp
)

target_include_directories(nudny_base_UT
	PUBLIC	
		${CMAKE_CURRENT_SOURCE_DIR}/${INC_DIR}
		include
)

target_link_libraries(
	nudny_base_UT
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(nudny_base_UT)
