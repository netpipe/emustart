#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtXml>
#include <QDebug>
#include <QXmlStreamReader>



QString resolveRelativePath(const QString &relativePath) {
    // Base directory where the files are located
    QString baseDirectory = QDir::currentPath()+"/roms/superconsole/";//  "/home/Desktop/test/snes/";
    // Remove leading "./" if present
    QString cleanedPath = relativePath;
    if (cleanedPath.startsWith("./")) {
        cleanedPath.remove(0, 2);
    }

    // Resolve the relative path against the base directory
    QString absolutePath = QDir(baseDirectory).filePath(cleanedPath);

    return absolutePath;
}

QListWidgetItem* createGameItem(const QString &title, const QString &imagePath) {
    QIcon icon(imagePath);
    QListWidgetItem *item = new QListWidgetItem(icon, title);
    return item;
}

Game MainWindow::parseXML(const QString &filePath, int index,bool countenable) {
    Game game;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Cannot open file";
        return game;
    }

    QXmlStreamReader xmlReader(&file);
    int currentIndex = -1;

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == QString("game")) {
                ++currentIndex;
                game.gamecount=currentIndex;
                if (!countenable){
                if (currentIndex == index) {
                    while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == QString("game"))) {
                        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
                            if (xmlReader.name() ==  QString("path")) {
                                xmlReader.readNext();
                                game.path = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("name")) {
                                xmlReader.readNext();
                                game.name = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("desc")) {
                                xmlReader.readNext();
                                game.desc = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("image")) {
                                xmlReader.readNext();
                                game.image = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("video")) {
                                xmlReader.readNext();
                                game.video = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("marquee")) {
                                xmlReader.readNext();
                                game.marquee = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("thumbnail")) {
                                xmlReader.readNext();
                                game.thumbnail = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("releasedate")) {
                                xmlReader.readNext();
                                game.releasedate = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("developer")) {
                                xmlReader.readNext();
                                game.developer = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("publisher")) {
                                xmlReader.readNext();
                                game.publisher = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("genre")) {
                                xmlReader.readNext();
                                game.genre = xmlReader.text().toString();
                            } else if (xmlReader.name() ==  QString("players")) {
                                xmlReader.readNext();
                                game.players = xmlReader.text().toString();
                            }
                        }

                        xmlReader.readNext();
                    }

                    file.close();
                    return game; // Return immediately when the game is found
                }
                }
            }
        }
    }

    file.close();
   // qDebug() << "Game not found at index" << index;
    return game; // Return empty game if not found
}

//void MainWindow::parseXML(const QString &filePath) {
//    QFile file(filePath);
//    if (!file.open(QFile::ReadOnly | QFile::Text)) {
//        qDebug() << "Error: Cannot open file";
//        return;
//    }

//    QDomDocument doc;
//    if (!doc.setContent(&file)) {
//        qDebug() << "Error: Failed to parse XML";
//        file.close();
//        return;
//    }
//    file.close();

//    QDomElement root = doc.documentElement();
//    QDomNodeList gameNodes = root.elementsByTagName("game");

//    //for (int i = 0; i < gameNodes.size(); ++i) {
//     for (int i = 0; i <= 3; ++i) {
//        QDomNode gameNode = gameNodes.item(i);
//        if (gameNode.isElement()) {
//            QDomElement gameElement = gameNode.toElement();
//            QString title = gameElement.attribute("title");
//            QString description = gameElement.attribute("description");
//            QString videoPath = gameElement.attribute("video");
//            QString imagePath = gameElement.attribute("image");
//            videofile=videoPath;
//            gameimage=imagePath;
//            QListWidgetItem *item = createGameItem(title, imagePath);
//            ui->gamelistwidget->addItem(item);
//        }
//    }
//}
void MainWindow::loadGameData(QString filePath) {
   // QString filePath = test.toLatin1(); // Path to your XML file
    Game gameslist =  parseXML(filePath,1,1);
    qDebug() << "gamecount " << gameslist.gamecount+1 << endl;
    qDebug() << "testing " << endl;
    int i=0;
    Game gameslist2;
    while(i<=gameslist.gamecount){
        gameslist2 = parseXML ("./"+ui->emulist->currentText()+"/gamelist.xml",i,0);
        ui->gamelistwidget->addItem(gameslist2.name);
     //   stuff << gameslist2.name;
        i++;
    }
    //append games to list
   // qDebug() << stuff.at(1);
}


void MainWindow::displayGameInfo(int index) {
    // Retrieve game information based on the selected index
    // Display title and description
    // Play video and display image
}

void MainWindow::playVideo(const QString &videoPath) {
    //mediaPlayer->setMedia(QUrl::fromLocalFile(videoPath));
    //mediaPlayer->play();
}

void MainWindow::displayImage(const QString &imagePath) {
    QPixmap pixmap(imagePath);
    ui->imageLabel->setPixmap(pixmap);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
      mediaPlayer = new QMediaPlayer(this);
      mediaPlayer->setVideoOutput(ui->vidwid);
     // QDir::setCurrent(QStringLiteral("./snes/"));

      QDirIterator it("roms", QDir::AllDirs | QDir::NoDotAndDotDot);
      while (it.hasNext()) {
          qDebug() << it.next();
ui->emulist->addItem(it.filePath());
      }

     // resolveRelativePath(

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_runbtn_clicked()
{
    m_process = new QProcess();
    //m_process->setReadChannelMode(QProcess::MergedChannels);
   // connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(showOutput()));

    QString program = ui->pathtxt->text();
    m_process->start(program);

}


void MainWindow::on_runbtn_2_clicked()
{

   // loadGameData();
    //qDebug() << ui->emulist->currentText()+"/gamelist.xml";
    Game gameslist = parseXML ("./"+ui->emulist->currentText()+"/gamelist.xml",1,0);
    //qDebug() << "testing" << gameslist.video ;
    //playVideo (gameslist.video);
    qDebug() << resolveRelativePath(gameslist.image);
ui->boximage->setPixmap(QPixmap(resolveRelativePath(gameslist.image)));
    playVideo (resolveRelativePath(gameslist.video));

    loadGameData(ui->emulist->currentText()+"/gamelist.xml");
}

