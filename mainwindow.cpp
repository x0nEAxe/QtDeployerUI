#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setVisible (false);
    ui->pushButton_5->setVisible (false);
    QSettings settings("myconf.conf", QSettings::IniFormat);
    qmakePath = settings.value("QMAKE").toString();
    if (qmakePath.isEmpty ())
    {
        QMessageBox::warning (this, "Error", "Wrong QMAKE Path");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked() //deploy folder
{
    deployDir = QFileDialog::getExistingDirectory ();
    if (!deployDir.isEmpty ()) ui->pushButton_3->setStyleSheet ("QPushButton {background-color: rgb(48, 255, 2);}");
}

void MainWindow::on_pushButton_2_clicked() //deploy
{
    if(!sourceExe.isEmpty () && !deployDir.isEmpty ())
    {
        command = "cqtdeployer";
        args << "-qmake" << qmakePath;
        args << "-bin" << sourceExe;
        args << "-targetDir" << deployDir;
        if (ui->checkBox_3->isChecked () && !sourceDir.isEmpty ()) args << "-qmlDir" << sourceDir;
        if (ui->checkBox_2->isChecked () && !extLibs.isEmpty ()) args << "-libDir" << extLibs << "-recursiveDepth" << QString::number(10);
        QProcess *bash = new QProcess;
        connect(bash, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, [&](){QMessageBox::information (this, "", "Deploy has finished"); delete bash;});
        bash->start(command, args);
        bash->waitForFinished ();
    }
    else
    {
        QMessageBox::warning (this, "Error", "Wrong paths");
        if(sourceExe.isEmpty ()) ui->pushButton_4->setStyleSheet ("QPushButton {background-color: rgb(234, 0, 4);}");
        if(deployDir.isEmpty ()) ui->pushButton_3->setStyleSheet ("QPushButton {background-color: rgb(234, 0, 4);}");
        if(sourceDir.isEmpty ()) ui->pushButton->setStyleSheet ("QPushButton {background-color: rgb(234, 0, 4);}");
        if(extLibs.isEmpty ()) ui->pushButton_5->setStyleSheet ("QPushButton {background-color: rgb(234, 0, 4);}");
    }
}

void MainWindow::on_pushButton_4_clicked() //source app
{
    sourceExe = QFileDialog:: getOpenFileName ();
    if (!sourceExe.isEmpty ()) ui->pushButton_4->setStyleSheet ("QPushButton {background-color: rgb(48, 255, 2);}");
}

void MainWindow::on_checkBox_3_stateChanged(int arg1) //qml state
{
    ui->pushButton->setVisible (arg1);
}

void MainWindow::on_pushButton_clicked() //qml dir
{
    sourceDir = QFileDialog::getExistingDirectory ();
    if (!sourceDir.isEmpty ()) ui->pushButton->setStyleSheet ("QPushButton {background-color: rgb(48, 255, 2);}");
}

void MainWindow::on_pushButton_5_clicked() //ext libs
{
    extLibs = QFileDialog::getExistingDirectory ();
    if (!extLibs.isEmpty ()) ui->pushButton_5->setStyleSheet ("QPushButton {background-color: rgb(48, 255, 2);}");
}
void MainWindow::on_checkBox_2_stateChanged(int arg1) //ext libs state
{
    ui->pushButton_5->setVisible (arg1);
}

