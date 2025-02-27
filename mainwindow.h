#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QCamera>
#include <QCameraViewfinder>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startStreaming();
    void stopStreaming();
    void readGstOutput();  // ✅ New: Reads stdout from GStreamer
    void readGstError();   // ✅ New: Reads stderr from GStreamer
    void gstProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);  // ✅ New: Handles process exit

private:
    Ui::MainWindow *ui;
    QProcess *gstProcess;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
};

#endif // MAINWINDOW_H
