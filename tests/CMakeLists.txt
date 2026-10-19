include(CTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(NoeMixerr_TESTS
	src/core/ArrayVectorTest.cpp
	src/core/AudioBufferTest.cpp
	src/core/AutomatableModelTest.cpp
	src/core/MathTest.cpp
	src/core/ProjectVersionTest.cpp
	src/core/RelativePathsTest.cpp
	src/core/TimelineTest.cpp
	src/tracks/AutomationTrackTest.cpp
)

foreach(NoeMixerr_TEST_SRC IN LISTS NoeMixerr_TESTS)
	# TODO CMake 3.20: Use cmake_path
	get_filename_component(NoeMixerr_TEST_NAME ${NoeMixerr_TEST_SRC} NAME_WE)

	add_executable(${NoeMixerr_TEST_NAME} ${NoeMixerr_TEST_SRC})
	add_test(NAME ${NoeMixerr_TEST_NAME} COMMAND ${NoeMixerr_TEST_NAME})

	# TODO CMake 3.12: Propagate usage requirements by linking to noemixerrobjs
	target_include_directories(${NoeMixerr_TEST_NAME} PRIVATE $<TARGET_PROPERTY:noemixerrobjs,INCLUDE_DIRECTORIES>)

	target_static_libraries("${NoeMixerr_TEST_NAME}" PRIVATE noemixerrobjs)
	target_link_libraries(${NoeMixerr_TEST_NAME} PRIVATE
		${QT_LIBRARIES}
		${QT_QTTEST_LIBRARY}
	)

	target_compile_features(${NoeMixerr_TEST_NAME} PRIVATE cxx_std_20)
	target_compile_definitions(${NoeMixerr_TEST_NAME} PRIVATE NoeMixerr_TESTING)
endforeach()
