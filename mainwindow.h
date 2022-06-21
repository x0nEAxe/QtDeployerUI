#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>

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
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_checkBox_3_stateChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QString sourceExe;
    QString sourceDir;
    QString deployDir;
    QString qmakePath;
    QString extLibs;
    QString command;
    QStringList args;

};
#endif // MAINWINDOW_H
