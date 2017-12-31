#-------------------------------------------------
#
# Project created by QtCreator 2017-10-21T22:58:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FTSDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ./cppjieba/include
INCLUDEPATH += ./cppjieba/deps

DEFINES += SQLITE_ENABLE_FTS4 USE_FTS
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    SQLiteCPP/sample/MyTokenizer.cpp \
    SQLiteCPP/Tokenizer.cpp \
    SQLiteCPP/sqlite3.c \
    resulttablemodel.cpp \
    resultitemdelegate.cpp \
    SQLiteCPP/sample/rankfunc.c

HEADERS += \
        mainwindow.h \
    SQLiteCPP/sample/MyTokenizer.h \
    SQLiteCPP/DB.h \
    SQLiteCPP/Exception.h \
    SQLiteCPP/fts3_tokenizer.h \
    SQLiteCPP/sqlite3.h \
    SQLiteCPP/Statement.h \
    SQLiteCPP/Tokenizer.h \
    mainwindow.h \
    resulttablemodel.h \
    resultitemdelegate.h \
    SQLiteCPP/sample/rankfunc.h

FORMS += \
        mainwindow.ui
