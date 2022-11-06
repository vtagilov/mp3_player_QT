#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <chrono>
#include <thread>
#include <QTimer>
#include <QTime>
#include <QDir>
#include <QtCore>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_3->hide();
    player->setVolume(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("mp3 (*.mp3)"));
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly))
    {

        filename = fileName;
    }
    player->setMedia(QUrl::fromLocalFile(filename));
    connect(player, &QMediaPlayer::durationChanged, this, [&](qint64 dur) {
        durr = dur;
        int min = dur/60000;
        int sec = ( dur - min*60000 ) / 1000;
        QString s = QString::number(min) + ":" + QString::number(sec);
        ui->label_2->setText(s);
    });
    MainWindow::on_pushButton_3_clicked();
}



void MainWindow::on_pushButton_2_clicked()
{
    player->play();
    ui->pushButton_2->hide();
    ui->pushButton_3->show();
}


void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    player->setVolume(position);
}


void MainWindow::on_pushButton_3_clicked()
{
    player->pause();
    ui->pushButton_3->hide();
    ui->pushButton_2->show();
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    player->setVolume(value);
}


void MainWindow::on_choosepath_clicked()
{
    paths = QFileDialog::getOpenFileNames(this,tr("Открыть файлы"),"C://Music","Музыка (*.mp3)");
    QStringList filesName;
    QString newDir = QString(QDir::currentPath()+"/%1");
    QDir().mkdir(newDir);

    for (int i=0; i<paths.size();i++) {
        filesName.append(QFileInfo(paths.at(i)).fileName());
        QFile::copy(paths.at(i),newDir+"/"+QFileInfo(paths.at(i)).fileName());
    }
    music_names = filesName;
    filename = paths[index];
    start_track();
    edit_textBrowser();

}

void MainWindow::edit_textBrowser()
{
    musicnames = "";
    for(int i=0;i<music_names.length();i++)
    {
        if(music_names[i] == trackname+".mp3")
            musicnames += "►";
        musicnames += music_names[i] + "\n";
    }
    ui->textBrowser->setText(musicnames);
}
void MainWindow::start_track()
{
    QFileInfo fi(filename);
    trackname = fi.baseName();
    player->setMedia(QUrl::fromLocalFile(filename));
    connect(player, &QMediaPlayer::durationChanged, this, [&](qint64 dur) {
        durr = dur;
        int min = dur/60000;
        int sec = ( dur - min*60000 ) / 1000;
        QString s = QString::number(min) + ":" + QString::number(sec);
        ui->label_2->setText(s);
    });
    MainWindow::on_pushButton_2_clicked();

}

void MainWindow::on_next_track_clicked()
{
    if(index == paths.length()-1)
    {
        index = 0;
    }
    else
    {
        index++;
    }
    filename = paths[index];
    start_track();
    edit_textBrowser();
}


void MainWindow::on_previous_track_clicked()
{
    if(index == 0)
    {
        index = paths.length()-1;
    }
    else
    {
        index--;
    }
    filename = paths[index];
    start_track();
    edit_textBrowser();
}

