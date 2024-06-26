cmake_minimum_required(VERSION 3.16)

project(untitled1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appuntitled1
    main.cpp
)

qt_add_qml_module(appuntitled1
    URI untitled1
    VERSION 1.0
    QML_FILES
    Main.qml
        SOURCES Client.h
        SOURCES Client.cpp
        SOURCES imagesignalsender.h imagesignalsender.cpp
        RESOURCES qml.qrc
        SOURCES
        RESOURCES
        RESOURCES
        SOURCES Client_Connection.cpp
        SOURCES Client_Connection.h
        SOURCES FileHandler.cpp
        SOURCES FileHandler.h
        SOURCES
        SOURCES labelhandler.cpp
        SOURCES labelhandler.h
        RESOURCES ../Downloads/download.png
        RESOURCES ../Downloads/download.png
        RESOURCES
        RESOURCES
        SOURCES textfieldhandler.h textfieldhandler.cpp
        RESOURCES mouseBoth.png mouseLeft.png mouseRight.png mouseStandart.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appuntitled1 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appuntitled1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appuntitled1
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appuntitled1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
