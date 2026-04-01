cmake_minimum_required(VERSION 3.19)
project(MicroVectorEditor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(MicroVectorEditor
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    svgparser.cpp
    getAttributeValue.cpp
    toInt.cpp
    Objects.h
    Rectangle.h
    Circle.h
    Line.h
    Text.h
    toInt.h
    getAttributeValue.h
    svgparser.h
    Canvas.cpp
    Canvas.h
    Hexagon.h
    Hexagon.cpp
    FreeHand.h
    mousePressEvent.cpp
    mouseMoveEvent.cpp
    mouseReleaseEvent.cpp
    undo.cpp
    redo.cpp
    Circle.cpp
    Rectangle.cpp
    Line.cpp
    FreeHand.cpp
    Text.cpp
    Objects.cpp
    setupToolBar.cpp
    setupMenus.cpp
    roundedrectangle.h roundedrectangle.cpp

)

target_link_libraries(MicroVectorEditor
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS MicroVectorEditor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MicroVectorEditor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
