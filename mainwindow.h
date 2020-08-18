#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "base64.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_Encode_clicked();

    void on_btn_Decode_clicked();

    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

private:
    void readFileToEdit(const QString& filename);

private:
    Ui::MainWindow *ui;

    base64 b64;
};
#endif // MAINWINDOW_H
