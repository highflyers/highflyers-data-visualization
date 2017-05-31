#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T18:41:25
#
#-------------------------------------------------
QT += core websockets
QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport positioning network

TARGET = DataVisualization
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        MainWindow.cpp \
    MapWidget.cpp \
    Message.cpp \
    GUI/ServerStatus.cpp \
    GUI/TimeStatus.cpp \
    GUI/VehicleWidget.cpp \
    GUI/VehicleContainer.cpp \
    MapImageManipulation/ColorMapOverlay.cpp \
    MapImageManipulation/FileMapProvider.cpp \
    MapImageManipulation/ImageMixer.cpp \
    MapImageManipulation/PathOverlay.cpp \
    WebSocketServer/WebSocketServer.cpp \
    qcustomplot.cpp \
    MapImageManipulation/DisplayImage.cpp \
    MapImageManipulation/MapFragment.cpp \
    GUI/CoordinateDisplay.cpp

HEADERS  += MainWindow.h \
    MapWidget.h \
    Message.h \
    GUI/ServerStatus.h \
    GUI/TimeStatus.h \
    ServerStatus.h \
    GUI/VehicleWidget.h \
    GUI/VehicleContainer.h \
    MapImageManipulation/ColorMapOverlay.h \
    MapImageManipulation/FileMapProvider.h \
    MapImageManipulation/ImageMixer.h \
    MapImageManipulation/MapFragment.h \
    MapImageManipulation/MapOverlay.h \
    MapImageManipulation/PathOverlay.h \
    MapImageManipulation/MapProvider.h \
    WebSocketServer/WebSocketServer.h \
    qcustomplot.h \
    MapImageManipulation/DisplayImage.h \
    GUI/CoordinateDisplay.h \
    MapImageManipulation/MapProvider.h

FORMS    += MainWindow.ui \
    GUI/ServerStatus.ui \
    GUI/TimeStatus.ui \
    GUI/VehicleWidget.ui \
    GUI/VehicleContainer.ui \
    GUI/CoordinateDisplay.ui

