#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QProcess>


struct Game {
    QString path;
    QString name;
    QString desc;
    QString image;
    QString video;
    QString marquee;
    QString thumbnail;
    QString releasedate;
    QString developer;
    QString publisher;
    QString genre;
    QString players;
    int gamecount;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString videofile;
    QString gameimage;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStringList stuff;
    Game parseXML(const QString &filePath,int,bool);
    void loadGameData(QString);
    void displayGameInfo(int index);
    void playVideo(const QString &videoPath);
    void displayImage(const QString &imagePath);
private slots:
    void on_runbtn_clicked();

    void on_runbtn_2_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer;
    QProcess *m_process;
};
#endif // MAINWINDOW_H
