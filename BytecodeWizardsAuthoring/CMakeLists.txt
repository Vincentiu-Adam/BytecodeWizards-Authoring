cmake_minimum_required(VERSION 3.5)

project(BytecodeWizardsAuthoring VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#no idea how to make this work globally so I am just adding them
set(PROJECT_SOURCES
        main.cpp
        authoringwindow.cpp
        authoringwindow.h
        authoringwindow.ui
        Widgets/Base/Iauthoringwidget.h
        Widgets/Base/simpleinstruction.h Widgets/Base/simpleinstruction.cpp
        Widgets/Base/wizardinstruction.h Widgets/Base/wizardinstruction.cpp
        Widgets/Base/singlevalueinstruction.h Widgets/Base/singlevalueinstruction.cpp
        Widgets/Base/singlevaluewizardinstruction.h Widgets/Base/singlevaluewizardinstruction.cpp
        Widgets/Base/baseinstructionwidget.h Widgets/Base/baseinstructionwidget.cpp
        Widgets/Instructions/setliteral.h Widgets/Instructions/setliteral.cpp
        Widgets/Instructions/add.h Widgets/Instructions/add.cpp
        Widgets/Instructions/subtract.h Widgets/Instructions/subtract.cpp
        Widgets/Instructions/multiply.h Widgets/Instructions/multiply.cpp
        Widgets/Instructions/divide.h Widgets/Instructions/divide.cpp
        Widgets/Instructions/gethealth.h Widgets/Instructions/gethealth.cpp
        Widgets/Instructions/sethealth.h Widgets/Instructions/sethealth.cpp
        Widgets/Instructions/getwisdom.h Widgets/Instructions/getwisdom.cpp
        Widgets/Instructions/setwisdom.h Widgets/Instructions/setwisdom.cpp
        Widgets/Instructions/playanim.h Widgets/Instructions/playanim.cpp
        Misc/linesegment.h Misc/linesegment.cpp
        canvaswidget.h canvaswidget.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BytecodeWizardsAuthoring
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BytecodeWizardsAuthoring APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BytecodeWizardsAuthoring SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BytecodeWizardsAuthoring
            ${SOURCES}
        )
    endif()
endif()

target_link_libraries(BytecodeWizardsAuthoring PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(BytecodeWizardsAuthoring PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS BytecodeWizardsAuthoring
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BytecodeWizardsAuthoring)
endif()
