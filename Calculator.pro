QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/Mainwindow.cpp \
    src/Interface.cpp \
    src/MathOperation.cpp \

HEADERS+= \
    src/Mainwindow.h \
    src/Interface.h \
    src/MathOperation.h \

CONFIG += lrelease

RESOURCES += resource/resource.qrc

# Default rules for deployment.
qnx: target.path = $${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
