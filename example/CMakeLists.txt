set (PROJECT_SOURCES
    # rc
    res.qrc

    mainwindow.h
    mainwindow.cpp
    main.cpp
    

    )


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Example
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Example SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Example
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Example PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Example PRIVATE qscintilla)