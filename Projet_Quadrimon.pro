QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


equals(QT_MAJOR_VERSION, 5) {
        QT += opengl widgets
} else:equals(QT_MAJOR_VERSION, 6) {
        QT += openglwidgets
}

TEMPLATE  = app


# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
} else:macx {
        LIBS     += -framework OpenGL
} else {
        LIBS     += -lGL -lGLU
}


SOURCES += \
    joueur.cpp \
    main.cpp \
    mainwindow.cpp \
    quadrimon.cpp \
    quadrimon_affiche.cpp \
    reco_carte.cpp \
    reco_terrain.cpp \
    scene.cpp \
    terrain.cpp \
    terrain_affiche.cpp

HEADERS += \
    joueur.h \
    mainwindow.h \
    quadrimon.h \
    quadrimon_affiche.h \
    reco_carte.h \
    reco_terrain.h \
    scene.h \
    terrain.h \
    terrain_affiche.h

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

FORMS += \
    mainwindow.ui \
    reco_carte.ui \
    reco_terrain.ui

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

RESOURCES += \
    res.qrc
