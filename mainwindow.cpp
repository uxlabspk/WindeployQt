#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUI()
{    
    configDir = QDir::homePath()+"/windeployConfig.appconfig";

    setFixedSize(542, 242);

    readConfig();

    if (WindeployQtLocation == "")
        ui->stackedWidget->setCurrentIndex(0);
    else
        ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::readConfig()
{
    QFile file(configDir);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        WindeployQtLocation = "";
        return;
    }
    QTextStream in(&file);
    WindeployQtLocation = in.readAll();
    file.close();
}

void MainWindow::writeConfig()
{
    QFile file(configDir);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream out(&file);
    QString text = ui->windeploySource->text();
    out << text;
    file.close();
}

void MainWindow::on_continueBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_browseBtn_clicked()
{
    WindeployQtLocation = QFileDialog::getOpenFileName(this, "Select the Location");
    ui->windeploySource->setText(WindeployQtLocation);
}

void MainWindow::on_continueBtn2_clicked()
{
    if (ui->windeploySource->text() == "")
        QMessageBox::warning(this, "Warning", "You are about to leaving environment unset. Browse the windeployqt location.");
    else
    {
        ui->stackedWidget->setCurrentIndex(2);
        writeConfig();
    }
}

void MainWindow::on_projectBrowseBtn_clicked()
{
    if (ui->stackedWidget->currentIndex() == 2)
    {
        ProjectSource = QFileDialog::getOpenFileName(this, "Select exe");
        ui->projectSource->setText(ProjectSource);

        QFileInfo f;
        f.setFile(ProjectSource);
        if (f.canonicalPath().endsWith("/release"))
        {
            ui->qmlRelease->setChecked(true);
        }
        else if (f.canonicalPath().endsWith("/debug"))
        {
            ui->qmlDebug->setChecked(true);
        }

    }
    else
    {
        ui->stackedWidget->setCurrentIndex(2);
        on_projectBrowseBtn_clicked();
    }
}

void MainWindow::on_generateBtn_clicked()
{
    QString l = "\"";
    QString fil = WindeployQtLocation + " " + l + ui->projectSource->text() + l;
    const char* cmd = fil.toLocal8Bit().constData();
    int i = system(cmd);

    (i == 0)? ui->errorString->setText("<p style=\"color: #009B34\">Generated Successfully!</p>") : ui->errorString->setText("<p style=\"color: #FF0000\">Generate failed! Check the path and try again</p>");

}

void MainWindow::on_actionBrowse_triggered()
{
    on_projectBrowseBtn_clicked();
}

void MainWindow::on_actionQuit_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionSettings_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionReset_triggered()
{
    QString l = "\"";
    QString fil =  "del " + l + configDir + l;
    const char* cmd = fil.toLocal8Bit().constData();
    system(cmd);
}

void MainWindow::on_actionMinimize_triggered()
{
    MainWindow::showMinimized();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::on_generateQmlBtn_clicked()
{
    QString l = "\"";
    QString type = (ui->qmlDebug->isChecked())? "--debug" : "--release"; //"--debug";
    QString dir = " --qmldir C:/Qt/5.15.2/mingw81_64/qml ";
    QString fil = WindeployQtLocation + " " + type + dir + l + ui->projectSource->text() + l;
    const char* cmd = fil.toLocal8Bit().constData();
    int i = system(cmd);

    (i == 0)? ui->errorString->setText("<p style=\"color: #009B34\">Generated Successfully!</p>") : ui->errorString->setText("<p style=\"color: #FF0000\">Generate failed! Check the path and try again</p>");
}

void MainWindow::on_label_6_linkActivated()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionFollow_me_on_twitter_triggered()
{
    QUrl url;
    url.setUrl("https://twitter.com/prog_naveed");
    QDesktopServices::openUrl(url);
}
