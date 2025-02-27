/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *statusLabel;
    QWidget *cameraViewContainer;
    QVBoxLayout *cameraLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(statusLabel);

        cameraViewContainer = new QWidget(centralwidget);
        cameraViewContainer->setObjectName(QString::fromUtf8("cameraViewContainer"));
        cameraLayout = new QVBoxLayout(cameraViewContainer);
        cameraLayout->setObjectName(QString::fromUtf8("cameraLayout"));
        cameraLayout->setContentsMargins(0, 0, 0, 0);

        mainLayout->addWidget(cameraViewContainer);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        mainLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        mainLayout->addWidget(stopButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "RTSP Webcam Streamer", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Not Streaming", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start Streaming", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop Streaming", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
