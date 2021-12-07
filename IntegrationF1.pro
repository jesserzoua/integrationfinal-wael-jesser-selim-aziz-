QT       += core gui sql printsupport multimedia multimediawidgets serialport dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino_bouton.cpp \
    chat.cpp \
    connection.cpp \
    gestion_participant.cpp \
    gestion_tickets.cpp \
    main.cpp \
    mainwindow.cpp \
    match.cpp \
    qcustomplot.cpp \
    stade.cpp \
    statistique.cpp \
    statmans.cpp \
    window.cpp \
    windowmatch.cpp \
    windowparticipants.cpp \
    windowticket.cpp

HEADERS += \
    arduino_bouton.h \
    chat.h \
    connection.h \
    gestion_participant.h \
    gestion_tickets.h \
    mainwindow.h \
    match.h \
    qcustomplot.h \
    stade.h \
    statistique.h \
    statmans.h \
    window.h \
    windowmatch.h \
    windowparticipants.h \
    windowticket.h


FORMS += \
    chatmainwindow.ui \
    chatsetnickname.ui \
    mainwindow.ui \
    statistique.ui \
    statmans.ui \
    window.ui \
    windowmatch.ui \
    windowparticipants.ui \
    windowticket.ui

DBUS_ADAPTORS += org.example.chat.xml
DBUS_INTERFACES += org.example.chat.xml

# install
target.path = $$[QT_INSTALL_EXAMPLES]/dbus/chat
INSTALLS += target

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    org.example.chat.xml
