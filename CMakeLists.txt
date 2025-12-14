cmake_minimum_required(VERSION 3.16)

project(NotePadPP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core5Compat)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core5Compat)

set(PROJECT_SOURCES
    src/AboutNotePP.cpp
    src/AboutNotePP.h
    src/App.cpp
    src/CompareMode.cpp
    src/CompareMode.h
    src/DirFindPage.cpp
    src/DirFindPage.h
    src/EnCode.cpp
    src/EnCode.h
    src/FileManager.cpp
    src/FileManager.h
    src/FindDlg.cpp
    src/FindDlg.h
    src/FindPage.cpp
    src/FindPage.h
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
)

add_subdirectory("3rdparty")
add_subdirectory("example")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NotePadPP
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NotePadPP APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(NotePadPP SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NotePadPP
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(NotePadPP PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets 
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Core5Compat
    qscintilla
    libuchardet_static
    libucd_static
    )

# message(STATUS "-------------- ${UCHARDET_STATIC_LIBRARY}")

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.NotePadPP)
endif()
set_target_properties(NotePadPP PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS NotePadPP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NotePadPP)
endif()
