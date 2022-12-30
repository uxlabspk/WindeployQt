#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void setUI();

    void readConfig();

    void writeConfig();

private slots:
    void on_continueBtn_clicked();

    void on_browseBtn_clicked();

    void on_continueBtn2_clicked();

    void on_projectBrowseBtn_clicked();

    void on_generateBtn_clicked();

    void on_actionBrowse_triggered();

    void on_actionQuit_triggered();

    void on_actionSettings_triggered();

    void on_actionReset_triggered();

    void on_actionMinimize_triggered();

    void on_actionAbout_app_triggered();

    void on_actionAbout_Qt_triggered();

    void on_generateQmlBtn_clicked();

    void on_label_6_linkActivated();

private:
    Ui::MainWindow *ui;
    QString configDir;
    QString WindeployQtLocation;
    QString ProjectSource;


};
#endif // MAINWINDOW_H
