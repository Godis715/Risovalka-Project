TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../Include

SOURCES += \
    ../Src/ID.cpp \
    ../Src/Logger.cpp \
    ../Src/main.cpp \
    ../Src/Mode.cpp \
    ../Src/Model.cpp \
    ../Src/Presenter.cpp \
    ../Src/Primitives.cpp \
    ../Src/Requirement.cpp \
    ../Src/type.cpp \
    ../Src/Vector2.cpp \
    ../Src/View.cpp

HEADERS += \
    ../Include/Array.h \
    ../Include/Copmilator.h \
    ../Include/Data.h \
    ../Include/Dequeue.h \
    ../Include/Dictionary.h \
    ../Include/Hash-Table.h \
    ../Include/Header.h \
    ../Include/ID.h \
    ../Include/IDGenerator.h \
    ../Include/INumerable.h \
    ../Include/IView.h \
    ../Include/List.h \
    ../Include/Logger.h \
    ../Include/Mode.h \
    ../Include/Model.h \
    ../Include/Pair-Tree.h \
    ../Include/Point.h \
    ../Include/Presenter.h \
    ../Include/Primitives.h \
    ../Include/Queue.h \
    ../Include/Requirement.h \
    ../Include/Type.h \
    ../Include/Vector2.h \
    ../Include/View.h \
    ../Include/ViewFLTK.h
