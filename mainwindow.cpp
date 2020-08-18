#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Base64");

    setWindowIcon(QIcon(":/Icons/doofnik.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_Encode_clicked()
{
    std::string input_text = ui->edit_Encode->toPlainText().toUtf8().constData();
    std::string encoded_text = b64.encode(input_text);
    ui->edit_Decode->setPlainText(QString::fromStdString(encoded_text));
}

void MainWindow::on_btn_Decode_clicked()
{
    std::string input_text = ui->edit_Encode->toPlainText().toStdString();
    std::string decoded_str = b64.decode(input_text);
    ui->edit_Decode->setPlainText(QString::fromStdString(decoded_str));
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename =
            QFileDialog::getOpenFileName(this, "Open a text file", QDir::homePath());
    readFileToEdit(filename);
}

void MainWindow::readFileToEdit(const QString& filename)
{
    QFile fin(filename);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->edit_Encode->setPlainText("");
        ui->edit_Encode->appendHtml("<font color = \"DarkRed\"><b>Could not open file</b></font>");

        ui->edit_Encode->appendHtml("<font color = \"FireBrick\"><pre>or you decided not to select it...</pre></font>");
        return;
    }

    ui->edit_Encode->setPlainText(fin.readAll());   // yeah.. yeah...

    fin.close();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox mAboutBox;
    mAboutBox.setWindowIcon(QIcon(":/Icons/doofnik.jpg"));
    mAboutBox.about(this, "About",
                       "The most necessary.");
}
