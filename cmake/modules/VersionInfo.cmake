# The version declared in the top-level CMakeLists.txt is authoritative.
# Using git describe here previously imported unrelated LMMS tags and emitted
# "fatal: No names found" in shallow, tagless CI checkouts.
# Release engineering can deliberately override with -DFORCE_VERSION=0.4.0-rc.1.
if(DEFINED FORCE_VERSION AND NOT "${FORCE_VERSION}" STREQUAL "" AND NOT "${FORCE_VERSION}" STREQUAL "internal")
    if(NOT FORCE_VERSION MATCHES "^([0-9]+)\\.([0-9]+)\\.([0-9]+)([-+][0-9A-Za-z.+-]+)?$")
        message(FATAL_ERROR "Invalid FORCE_VERSION '${FORCE_VERSION}'; expected semantic version such as 0.4.0 or 0.4.0-rc.1")
    endif()
    set(VERSION_MAJOR "${CMAKE_MATCH_1}")
    set(VERSION_MINOR "${CMAKE_MATCH_2}")
    set(VERSION_RELEASE "${CMAKE_MATCH_3}")
    set(VERSION "${FORCE_VERSION}")
    set(VERSION_STAGE "")
    set(VERSION_BUILD "")
    if(FORCE_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+-([^+]+)")
        set(VERSION_STAGE "${CMAKE_MATCH_1}")
    endif()
    if(FORCE_VERSION MATCHES "\\+([0-9A-Za-z.-]+)$")
        set(VERSION_BUILD "${CMAKE_MATCH_1}")
    endif()
endif()

message(STATUS "Configuring ${PROJECT_NAME_UCASE} ${VERSION}")
message(STATUS "Version: major=${VERSION_MAJOR}, minor=${VERSION_MINOR}, patch=${VERSION_RELEASE}, stage=${VERSION_STAGE}, build=${VERSION_BUILD}")
message(STATUS "Version authority: CMakeLists.txt (override with -DFORCE_VERSION=x.y.z[-stage][+metadata])")
