ADD_SUBDIRECTORY(3rdparty)

CONFIGURE_FILE("noemixerrconfig.h.in"        "${CMAKE_BINARY_DIR}/noemixerrconfig.h")

# Provide config flags to noemixerrversion.h
get_cmake_property(_define_vars VARIABLES)
foreach (_define_var ${_define_vars})
    if(_define_var MATCHES "^WANT|NoeMixerr_(HAVE|DEBUG)" )
        list(APPEND NoeMixerr_BUILD_OPTIONS "${_define_var}='${${_define_var}}'")
    endif()
endforeach()

# Format for readability
string(REPLACE ";" " " NoeMixerr_BUILD_OPTIONS "${NoeMixerr_BUILD_OPTIONS}")

CONFIGURE_FILE("noemixerrversion.h.in"       "${CMAKE_BINARY_DIR}/noemixerrversion.h")

SET(NoeMixerr_SRCS "")

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Enable C++20
SET(CMAKE_CXX_STANDARD 20)

IF(NoeMixerr_BUILD_APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
ENDIF()

ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(gui)
ADD_SUBDIRECTORY(tracks)

LIST(APPEND NoeMixerr_SRCS ${NoeMixerr_COMMON_SRCS})

IF(WANT_QT6)
	QT6_WRAP_UI(NoeMixerr_UI_OUT ${NoeMixerr_UIS})
ELSE()
	QT5_WRAP_UI(NoeMixerr_UI_OUT ${NoeMixerr_UIS})
ENDIF()

INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_BINARY_DIR}"
	"${CMAKE_BINARY_DIR}/include"
	"${CMAKE_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}/include"
)

IF(WIN32 AND MSVC)
	SET(WINRC "${CMAKE_BINARY_DIR}/noemixerr.rc")
ELSEIF(WIN32)
	SET(WINRC "${CMAKE_BINARY_DIR}/noemixerrrc.obj")
	ADD_CUSTOM_COMMAND(OUTPUT "${WINRC}"
				COMMAND "${CMAKE_RC_COMPILER}"
					"-I\"${CMAKE_SOURCE_DIR}\""
					"-o\"${CMAKE_BINARY_DIR}/noemixerrrc.obj\""
					"-i\"${CMAKE_BINARY_DIR}/noemixerr.rc\""
				DEPENDS "${CMAKE_BINARY_DIR}/noemixerr.rc")
ENDIF()

INCLUDE(GenQrc)
ADD_GEN_QRC(NoeMixerr_RCC_OUT noemixerr.qrc
	"${CMAKE_SOURCE_DIR}/doc/AUTHORS"
	"${CMAKE_SOURCE_DIR}/LICENSE.txt"
	"${CONTRIBUTORS}"
)

# Paths relative to noemixerr executable
FILE(RELATIVE_PATH LIB_DIR_RELATIVE "/${BIN_DIR}" "/${LIB_DIR}")
FILE(RELATIVE_PATH PLUGIN_DIR_RELATIVE "/${BIN_DIR}" "/${PLUGIN_DIR}")
ADD_DEFINITIONS(-DLIB_DIR="${LIB_DIR_RELATIVE}" -DPLUGIN_DIR="${PLUGIN_DIR_RELATIVE}" ${PULSEAUDIO_DEFINITIONS})
include_directories(SYSTEM
	${JACK_INCLUDE_DIRS}
	${SNDIO_INCLUDE_DIRS}
	${FFTW3F_INCLUDE_DIRS}
)

IF(PULSEAUDIO_INCLUDE_DIR)
	include_directories(SYSTEM "${PULSEAUDIO_INCLUDE_DIR}")
ENDIF()

IF(LV2_INCLUDE_DIRS)
	include_directories(SYSTEM ${LV2_INCLUDE_DIRS})
ENDIF()

IF(Lilv_INCLUDE_DIRS)
	include_directories(SYSTEM ${Lilv_INCLUDE_DIRS})
ENDIF()

IF(SUIL_INCLUDE_DIRS)
	include_directories(SYSTEM ${SUIL_INCLUDE_DIRS})
ENDIF()

# Use libraries in non-standard directories (e.g., another version of Qt)
IF(NoeMixerr_BUILD_LINUX)
	LINK_LIBRARIES(-Wl,--enable-new-dtags)
	SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
ENDIF()
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

ADD_LIBRARY(noemixerrobjs OBJECT
	${NoeMixerr_SRCS}
	${NoeMixerr_INCLUDES}
	${NoeMixerr_RCC_OUT}
)

GENERATE_EXPORT_HEADER(noemixerrobjs
	BASE_NAME noemixerr
)

ADD_EXECUTABLE(noemixerr
	core/main.cpp
	"${WINRC}"
)
TARGET_INCLUDE_DIRECTORIES(noemixerr
	PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)
target_static_libraries(noemixerr PUBLIC noemixerrobjs)

# Enable updated C++ language standards
IF(MSVC)
	TARGET_COMPILE_OPTIONS(noemixerrobjs PUBLIC "/Zc:__cplusplus" "/permissive-")
ENDIF()

# CMake doesn't define target_EXPORTS for OBJECT libraries.
# See the documentation of DEFINE_SYMBOL for details.
# Also add NOEMIXERR_STATIC_DEFINE for targets linking against it.
TARGET_COMPILE_DEFINITIONS(noemixerrobjs
	PRIVATE -Dnoemixerrobjs_EXPORTS
)
target_static_definitions(noemixerrobjs NOEMIXERR_STATIC_DEFINE)

# Set Visual Studio startup project to noemixerr
# https://stackoverflow.com/a/37994396/8166701
IF(NOT CMAKE_VERSION VERSION_LESS 3.6)
	SET_PROPERTY(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT noemixerr)
ENDIF()

SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${NoeMixerr_RCC_OUT} noemixerrconfig.h")

IF(NoeMixerr_HAVE_WINMM)
	SET(EXTRA_LIBRARIES "winmm")
ENDIF()

IF(NoeMixerr_BUILD_APPLE)
	SET(EXTRA_LIBRARIES "-framework CoreMIDI -framework CoreFoundation")
ENDIF()

IF(NoeMixerr_BUILD_HAIKU)
	SET(EXTRA_LIBRARIES "-lnetwork")
ENDIF()

if(NoeMixerr_HAVE_LIBRT)
	list(APPEND EXTRA_LIBRARIES "rt")
endif()

if(NoeMixerr_HAVE_PORTAUDIO)
	list(APPEND EXTRA_LIBRARIES portaudio::portaudio)
endif()

if(NoeMixerr_HAVE_MP3LAME)
	list(APPEND EXTRA_LIBRARIES mp3lame::mp3lame)
endif()

if(NoeMixerr_HAVE_OGGVORBIS)
	list(APPEND EXTRA_LIBRARIES Vorbis::vorbisenc Vorbis::vorbisfile)
endif()

if(NoeMixerr_HAVE_LV2)
	list(APPEND EXTRA_LIBRARIES Lilv::lilv)
endif()

SET(NoeMixerr_REQUIRED_LIBS ${NoeMixerr_REQUIRED_LIBS}
	${CMAKE_THREAD_LIBS_INIT}
	${QT_LIBRARIES}
	${ASOUND_LIBRARY}
	${SDL_LIBRARY}
	${SDL2_LIBRARY}
	${SNDIO_LIBRARIES}
	${PULSEAUDIO_LIBRARIES}
	${JACK_LIBRARIES}
	${SUIL_LIBRARIES}
	${FFTW3F_LIBRARIES}
	SampleRate::samplerate
	SndFile::sndfile
	${EXTRA_LIBRARIES}
)

target_link_libraries(noemixerrobjs
	${NoeMixerr_REQUIRED_LIBS}
)
target_static_libraries(noemixerrobjs ringbuffer)

set_target_properties(noemixerr PROPERTIES
	ENABLE_EXPORTS ON
	WIN32_EXECUTABLE $<NOT:$<CONFIG:DEBUG>>
)

set_target_properties(noemixerrobjs PROPERTIES AUTOUIC_SEARCH_PATHS "gui/modals")

IF(NOT WIN32 AND NOT NoeMixerr_BUILD_APPLE)
	if(CMAKE_INSTALL_MANDIR)
		SET(INSTALL_MANDIR ${CMAKE_INSTALL_MANDIR})
	ELSE(CMAKE_INSTALL_MANDIR)
		SET(INSTALL_MANDIR share/man)
	ENDIF(CMAKE_INSTALL_MANDIR)
	INSTALL(FILES "${CMAKE_SOURCE_DIR}/doc/noemixerr.1"
			DESTINATION "${INSTALL_MANDIR}/man1/"
			PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
ENDIF()

INSTALL(TARGETS noemixerr RUNTIME DESTINATION "${BIN_DIR}")
