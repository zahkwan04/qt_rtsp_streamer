#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gstProcess(nullptr), camera(nullptr), viewfinder(nullptr) {
    ui->setupUi(this);

    // Initialize Camera
    camera = new QCamera(this);
    viewfinder = new QCameraViewfinder(this);
    camera->setViewfinder(viewfinder);

    // Embed viewfinder in UI
    ui->cameraLayout->addWidget(viewfinder);
    camera->start(); // Start camera preview

    // Connect buttons
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startStreaming);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopStreaming);
}

MainWindow::~MainWindow() {
    if (camera) {
        camera->stop();
        delete camera;
    }
    delete ui;
}

void MainWindow::startStreaming() {
    if (gstProcess) {
        qDebug() << "GStreamer process is already running.";
        return;
    }

    QString pipeline = "gst-launch-1.0 -v v4l2src ! video/x-raw,width=1280,height=720,framerate=30/1 "
                       "! videoconvert ! x264enc tune=zerolatency bitrate=500 speed-preset=ultrafast "
                       "! rtph264pay config-interval=1 pt=96 ! udpsink host=0.0.0.0 port=8554";

    gstProcess = new QProcess(this);
    gstProcess->start(pipeline);

    if (!gstProcess->waitForStarted()) {
        qDebug() << "Failed to start GStreamer pipeline.";
        delete gstProcess;
        gstProcess = nullptr;
        ui->statusLabel->setText("Status: Failed to Start");
    } else {
        qDebug() << "GStreamer pipeline started.";
        ui->statusLabel->setText("Status: Streaming...");
    }
}

void MainWindow::stopStreaming() {
    if (gstProcess) {
        gstProcess->terminate();
        gstProcess->waitForFinished();
        delete gstProcess;
        gstProcess = nullptr;
        qDebug() << "Streaming stopped.";
        ui->statusLabel->setText("Status: Not Streaming");
    } else {
        qDebug() << "No active streaming process.";
    }
}
