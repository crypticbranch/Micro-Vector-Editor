cmake_minimum_required(VERSION 3.19)
project(MicroVectorEditor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

qt_add_executable(MicroVectorEditor
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    src/svgparser.cpp
    src/getAttributeValue.cpp
    src/toInt.cpp
    src/Canvas.cpp
    src/Hexagon.cpp
    src/mousePressEvent.cpp
    src/mouseMoveEvent.cpp
    src/mouseReleaseEvent.cpp
    src/undo.cpp
    src/redo.cpp
    src/Circle.cpp
    src/Rectangle.cpp
    src/Line.cpp
    src/FreeHand.cpp
    src/Text.cpp
    src/Objects.cpp
    src/setupToolBar.cpp
    src/setupMenus.cpp
    src/roundedrectangle.cpp
    include/mainwindow.h
    include/svgparser.h
    include/getAttributeValue.h
    include/toInt.h
    include/Objects.h
    include/Rectangle.h
    include/Circle.h
    include/Line.h
    include/Text.h
    include/Canvas.h
    include/Hexagon.h
    include/FreeHand.h
    include/roundedrectangle.h
    ui/mainwindow.ui
)
target_link_libraries(MicroVectorEditor
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_include_directories(MicroVectorEditor PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/MicroVectorEditor_autogen/include
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
