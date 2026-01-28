cmake_minimum_required(VERSION 3.16)

project(NotepadPP VERSION 1.0.2 LANGUAGES CXX)

set(TGT "NotepadPP")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core5Compat)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core5Compat)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    if (MSVC_IDE)
	message(STATUS "Qt6Widgets_LIBRARIES: ${Qt6Widgets_LIBRARIES}")
	get_target_property(V_LOCATION ${Qt6Widgets_LIBRARIES} IMPORTED_LOCATION)
	message(STATUS "V_LOCATION: ${V_LOCATION}")
	cmake_path(GET V_LOCATION PARENT_PATH V_RUN_PATH)
	message(STATUS "V_RUN_PATH: ${V_RUN_PATH}")
	set(CMAKE_VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${V_RUN_PATH}")
	message(STATUS "CMAKE_VS_DEBUGGER_ENVIRONMENT: ${CMAKE_VS_DEBUGGER_ENVIRONMENT}")
endif()
endif()

set(PROJECT_SOURCES
    src/AboutNotePP.cpp
    src/AboutNotePP.h
    src/App.cpp
    src/CompareMode.cpp
    src/CompareMode.h
    src/ConfigUtils.cpp
    src/ConfigUtils.h
    src/DirFindPage.cpp
    src/DirFindPage.h
    src/EnCode.cpp
    src/EnCode.h
    src/FileListView.cpp
    src/FileListView.h
    src/FileListViewDock.cpp
    src/FileListViewDock.h
    src/FileListViewItem.cpp
    src/FileListViewItem.h
    src/FileManager.cpp
    src/FileManager.h
    src/FindPage.cpp
    src/FindPage.h
    src/FindRecords.cpp
    src/FindRecords.h
    src/FindReplaceDlg.cpp
    src/FindReplaceDlg.h
    src/FindResultsDock.cpp
    src/FindResultsDock.h
    src/FindResultsView.cpp
    src/FindResultsView.h
    src/HtmlStyledItemDelegate.cpp
    src/HtmlStyledItemDelegate.h
    src/ISorter.cpp
    src/ISorter.h
    src/LineEndComboBox.cpp
    src/LineEndComboBox.h
    src/MarkPage.cpp
    src/MarkPage.h
    src/NotepadPP.cpp 
    src/NotePadPP.h
    src/ReplacePage.cpp
    src/ReplacePage.h
    src/ScintillaEditView.cpp
    src/ScintillaEditView.h
    src/SettingsPage.cpp
    src/SettingsPage.h
    src/ShortcutKeyDlg.cpp
    src/ShortcutKeyDlg.h
    src/ShortcutKeySt.h
    src/StyleSheetUtils.cpp
    src/StyleSheetUtils.h
    src/TreeView.cpp
    src/TreeView.h
)

## Set res files;
set (RES_FILES
    ### i18n
    "./res/i18n/zh-CN.qm"
    "./res/i18n/en-US.qm"
    ### imgs
    "./res/imgs/needsave.png"
    "./res/imgs/noneedsave.png"
    ### StyleSheets
    "./res/StyleSheet/AboutNotePP.qss"
    "./res/StyleSheet/FileListView.qss" 
    "./res/StyleSheet/FileListViewDock.qss"
    "./res/StyleSheet/FindResultsDock.qss"
    "./res/StyleSheet/LineEndComboBox.qss"
    "./res/StyleSheet/NotepadPP.qss"
    "./res/StyleSheet/ScintillaEditView.qss"
    "./res/StyleSheet/TabWidget.qss"
    "./res/StyleSheet/TreeView.qss"
    )

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${RES_FILES})

add_subdirectory("3rdparty")
# add_subdirectory("example")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${TGT}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_add_resources(${TGT} "resfile"
        PREFIX "/"
        BASE "./"
        FILES 
        ${RES_FILES})
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${TGT} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${TGT} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${TGT}
            ${PROJECT_SOURCES}
        )

        qt5_add_resources(${TGT} "resfile"
            PREFIX "/"
            BASE "./"
            FILES 
            ${RES_FILES})
    endif()
endif()

target_link_libraries(${TGT} PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets 
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Core5Compat
    qscintilla
    libuchardet_static
    libucd_static
    )

set_target_properties(${TGT} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

set(CPACK_PACKAGE_FILE_NAME ${TGT})
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "ZIP")
include(CPack)
include(GNUInstallDirs)
install(TARGETS ${TGT}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(${QT_VERSION} VERSION_GREATER 6.3.0)
qt_generate_deploy_app_script(
     TARGET ${TGT}
     OUTPUT_SCRIPT deploy_script
     NO_UNSUPPORTED_PLATFORM_ERROR
 )
 install(SCRIPT ${deploy_script})
 endif()
