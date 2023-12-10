# Build a version number into the binary library
configure_file(version.h.in version.h @ONLY)

# Create the STF library and the alias for consistent usage with
# both installed an installed library and FetchContent
add_library(stf STATIC stf.cpp)
add_library(STF::stf ALIAS stf)

# Specify the internal and public include directories
target_include_directories(stf
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Specify the C++ standard to observe
set_target_properties(stf
    PROPERTIES
        CXX_STANDARD ${stf_CPP_STD}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

# Use the following compile options
target_compile_options(stf
    PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wpedantic -Wextra -Wall>
        $<$<CXX_COMPILER_ID:MSVC>: >)

# Install target and associated include files
if(stf_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS stf EXPORT stfTargets ARCHIVE)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ TYPE INCLUDE)
    install(EXPORT stfTargets
            FILE stfConfig.cmake
            NAMESPACE STF::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stf)
endif()
