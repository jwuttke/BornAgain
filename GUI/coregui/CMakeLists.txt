############################################################################
# CMakeLists.txt file for building libBornAgainGUI library
############################################################################
set(library_name BornAgainGUI)


file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

if(WIN32)
	add_definitions(-DQDESIGNER_UILIB_LIBRARY)
endif()

set(resource_files
    "coregui.qrc"
    "Views/SampleDesigner/SampleDesigner.qrc"
    "Views/MaskWidgets/MaskWidgets.qrc"
    "Views/widgetbox/widgetbox.qrc"
    "Views/AccordionWidget/accordionwidgeticons.qrc"
)

# --- Qt configuration ---------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
qt5_add_resources(RC_SRCS ${resource_files})

# --- definitions ------
if(BORNAGAIN_CRASHHANDLER)
    add_definitions(-DBORNAGAIN_CRASHHANDLER)
endif()

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()


# --- making library ---------

add_library(${library_name} SHARED ${sources} ${RC_SRCS})
set_target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


# --- dependencies ---------
target_include_directories(${library_name} PUBLIC ${QtAddOn_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(${library_name}
    ${QtAddOn_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${ba3d_LIBRARY}
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Designer
    Qt5::PrintSupport
    Qt5::Network
)

# --- Installation ---------
install (TARGETS ${library_name} DESTINATION ${destination_lib} COMPONENT Libraries)

if(WIN32)
    # --- Qt ---
    string(REGEX REPLACE "\\\\" "/" QTDIR $ENV{QTDIR} ) # Convert C:\Qt\ to C:/Qt/
    install(FILES
    ${QTDIR}/bin/Qt5Widgets.DLL
    ${QTDIR}/bin/Qt5Core.dll
    ${QTDIR}/bin/Qt5Gui.dll
    ${QTDIR}/bin/Qt5Designer.dll
    ${QTDIR}/bin/Qt5Xml.dll
    ${QTDIR}/bin/Qt5Svg.dll
    ${QTDIR}/bin/Qt5Network.dll
    ${QTDIR}/bin/Qt5PrintSupport.dll
    DESTINATION ${destination_lib} COMPONENT Libraries)

    install(FILES
    ${QTDIR}/plugins/platforms/qwindows.dll
    DESTINATION bin/platforms COMPONENT Libraries)

    install(FILES
    ${QTDIR}/plugins/iconengines/qsvgicon.dll
    DESTINATION bin/iconengines COMPONENT Libraries)

    install(FILES
    ${QTDIR}/plugins/imageformats/qjpeg.dll
    ${QTDIR}/plugins/imageformats/qsvg.dll
    DESTINATION bin/imageformats COMPONENT Libraries)

    install(FILES
    ${QTDIR}/bin/libEGL.dll
    ${QTDIR}/bin/libGLESv2.dll
    DESTINATION ${destination_lib} COMPONENT Libraries)

    set(QT_VISTA_STYLE "${QTDIR}/plugins/styles/qwindowsvistastyle.dll")
    if(EXISTS "${QT_VISTA_STYLE}")
        install(FILES
		${QT_VISTA_STYLE}
                DESTINATION bin/styles COMPONENT Libraries)
    else(EXISTS "${QT_VISTA_STYLE}")
        MESSAGE(AUTHOR_WARNING "File ${QT_VISTA_STYLE} not found.")
    endif(EXISTS "${QT_VISTA_STYLE}")
    unset(QT_VISTA_STYLE)

endif()
