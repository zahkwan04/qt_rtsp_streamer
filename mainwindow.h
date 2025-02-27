#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

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

private:
    Ui::MainWindow *ui;
    QProcess *gstProcess;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
};

#endif // MAINWINDOW_H
