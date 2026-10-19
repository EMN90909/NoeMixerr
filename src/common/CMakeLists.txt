set(COMMON_SRCS
	RemotePluginBase.cpp
	SharedMemory.cpp
	SystemSemaphore.cpp
)

foreach(SRC ${COMMON_SRCS})
	list(APPEND NoeMixerr_COMMON_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/${SRC}")
endforeach()

set(NoeMixerr_COMMON_SRCS ${NoeMixerr_COMMON_SRCS} PARENT_SCOPE)
