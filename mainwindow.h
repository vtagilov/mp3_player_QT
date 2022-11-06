#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QMediaPlayer>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_verticalSlider_sliderMoved(int position);

    void on_pushButton_3_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_choosepath_clicked();

    void on_next_track_clicked();
    void start_track();
    void edit_textBrowser();


    void on_previous_track_clicked();

private:
    Ui::MainWindow *ui;
    QStringList paths;
    QStringList music_names;
    qint16 index = 0;
    QString musicnames = "";
    QString trackname;
    QMediaPlayer *player = new QMediaPlayer;
    QString filename;
    qint64 durr;
};
#endif // MAINWINDOW_H
