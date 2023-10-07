QT       += core gui
QT   += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/calculator_controller.cc \
    main.cc \
    model/calculate_credit.cc \
    model/calculate_deposit.cc \
    model/polish_notation.cc \
    view/calculator_view.cc \
    view/qcustomplot.cc

HEADERS += \
    controller/calculator_controller.h \
    model/calculate_credit.h \
    model/calculate_deposit.h \
    model/polish_notation.h \
    view/calculator_view.h \
    view/qcustomplot.h

FORMS += \
    view/calculator_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
