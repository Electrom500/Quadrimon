QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    joueur.cpp \
    main.cpp \
    mainwindow.cpp \
    quadrimon.cpp \
    reco_carte.cpp \
    terrain.cpp

HEADERS += \
    joueur.h \
    mainwindow.h \
    quadrimon.h \
    reco_carte.h \
    terrain.h

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

FORMS += \
    mainwindow.ui \
    reco_carte.ui

LIBS += -L$$(OPENCV_DIR)\lib \
        -lopencv_core455 \
        -lopencv_highgui455 \
        -lopencv_imgproc455 \
        -lopencv_imgcodecs455 \
        -lopencv_videoio455 \
        -lopencv_features2d455
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
