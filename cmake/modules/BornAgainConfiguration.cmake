# BornAgain project general configuration

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lib)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

set(bindir $BORNAGAINSYS/bin)
set(libdir $BORNAGAINSYS/lib)

if(WIN32)
  set(libprefix lib)
  set(libsuffix .dll)
elseif(APPLE)
  set(libprefix lib)
  set(libsuffix .so)
else()
  set(libprefix lib)
  set(libsuffix .so)
endif()

# --- installation destinations ---
set(destination_bin bin)
set(destination_lib lib)
set(destination_include include/BornAgain)
set(destination_examples share/BornAgain/Examples)
set(destination_images share/BornAgain/Images)
if(WIN32)
    set(destination_lib bin)
    set(destination_include include)
    set(destination_examples Examples)
endif()

# --- configure user setup script
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/thisbornagain.sh.in" "${CMAKE_BINARY_DIR}/bin/thisbornagain.sh" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/thisbornagain.csh.in" "${CMAKE_BINARY_DIR}/bin/thisbornagain.csh" @ONLY)

if(BORNAGAIN_RELEASE)
    # --- configure a header file to pass CMake settings to the source code
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAVersion.h.in"  "${CMAKE_SOURCE_DIR}/Core/Samples/inc/BAVersion.h")

    # --- configure deployment script for release
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/release.sh.in" "${CMAKE_BINARY_DIR}/bin/release.sh")

    # --- configure Doxyfile
    configure_file("${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile.in" "${CMAKE_SOURCE_DIR}/Doc/Doxygen/Doxyfile" @ONLY)
endif()

# --- configure project paths
#configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAConfigure.h.in" "${CMAKE_SOURCE_DIR}/Core/Tools/inc/BAConfigure.h" @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/BAConfigure.h.in" "${CMAKE_BINARY_DIR}/BAConfigure.h" @ONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_BINARY_DIR}")


# --- installation
if(NOT WIN32)
    install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.sh
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.csh
            PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
            GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
            DESTINATION bin)
endif()

if(APPLE AND CREATE_BUNDLE)
  include(DarwinSetup)
endif(APPLE AND CREATE_BUNDLE)
