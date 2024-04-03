#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QProcess>
#include <QListWidgetItem>
#include <QSqlDatabase>

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

    void updateEntry();
    void loadSelectedApplication(QListWidgetItem*);
    void initializeDatabase();
     void loadApplications();

private slots:
    void on_runbtn_clicked();

    void on_runbtn_2_clicked();

    void on_addemu_clicked();

    void on_removeemu_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer;
    QProcess *m_process;
        QSqlDatabase m_database;
};
#endif // MAINWINDOW_H
