#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gstProcess(nullptr) {
    ui->setupUi(this);

    // Connect buttons
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startStreaming);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopStreaming);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startStreaming() {
    if (gstProcess) {
        qDebug() << "GStreamer process is already running.";
        return;
    }

    QString pipeline = "gst-launch-1.0 -v mfvideosrc device-index=0 "
                       "! video/x-raw,width=1280,height=720,framerate=30/1 "
                       "! videoconvert ! x264enc tune=zerolatency bitrate=500 speed-preset=ultrafast "
                       "! rtph264pay config-interval=1 pt=96 ! udpsink host=0.0.0.0 port=8554";

    gstProcess = new QProcess(this);
    gstProcess->setProcessChannelMode(QProcess::MergedChannels);  // ✅ Capture both stdout & stderr
    connect(gstProcess, &QProcess::readyReadStandardOutput, this, &MainWindow::readGstOutput);
    connect(gstProcess, &QProcess::readyReadStandardError, this, &MainWindow::readGstError);
    connect(gstProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MainWindow::gstProcessFinished);

    gstProcess->start("cmd", QStringList() << "/c" << pipeline);  // ✅ Start in cmd

    if (!gstProcess->waitForStarted()) {
        qDebug() << "❌ Failed to start GStreamer pipeline.";
        delete gstProcess;
        gstProcess = nullptr;
        ui->statusLabel->setText("Status: Failed to Start");
    } else {
        qDebug() << "✅ GStreamer pipeline started.";
        ui->statusLabel->setText("Status: Streaming...");
    }
}

void MainWindow::readGstOutput() {
    qDebug() << "GStreamer Output: " << gstProcess->readAllStandardOutput();
}

void MainWindow::readGstError() {
    qDebug() << "GStreamer Error: " << gstProcess->readAllStandardError();
}

void MainWindow::gstProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "GStreamer process exited with code:" << exitCode << "Status:" << exitStatus;
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
