#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/types_c.h"
#include <QPicture>
#include<iostream>
#include <QtCore>
int count = 0;
//   timer = new QTimer(this);
//   connect(timer,SIGNAL(timeout()),this,SLOT(on_pushButton_clicked());
//cv::namedWindow("game of life",cv::WINDOW_AUTOSIZE);
//cv::namedWindow("video",cv::WINDOW_AUTOSIZE);
// cv::Mat frame;


//initialise arrayNExt with zeros

//for (int i = 0; i < 30; ++i){
//    for (int j = 0; j < 30; ++j){
//        arrayNext[i][j] = 0;
//    }

//}
cv::Mat frame;
int array[10][10] = {

        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };
    //initialise arrayNExt with zeros
    int arrayNext[30][30];

    //int goastArray[30][30];
    //for (int i = 0; i < 30; ++i){
    //	for (int j = 0; j < 30; ++){
    //		if (i/3 =10)
    //		goastArray[i][j] = array[i][j]
    //	}
    //}
    //0-10, 0-10
    int ghostArray[30][30];
int mapSize = 10;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    for (int i = 0; i < 30; ++i){
        for (int j = 0; j < 30; ++j){
            arrayNext[i][j] = 0;
        }

    }


    ui->setupUi(this);
    timer = new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(updateGUI()));
     timer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateGUI(){

    //set ghoast array to current array

    for (int i = 0; i < 10; ++i){
        for (int j = 0; j < 10; ++j)
            ghostArray[i][j] = array[i][j];
    }
    //10-20, 0-10
    for (int i = 10; i < 20; ++i){
        for (int j = 0; j < 10; ++j)
            ghostArray[i][j] = array[i-10][j];
    }
    //0-30, 0-10
    for (int i = 10; i < 20; ++i){
        for (int j = 0; j < 10; ++j)
            ghostArray[i][j] = array[i - 10][j];
    }
    //20-30, 0-10
    for (int i = 20; i < 30; ++i){
        for (int j = 0; j < 10; ++j)
            ghostArray[i][j] = array[i - 20][j];
    }
    //0-10, 10-20
    for (int i = 0; i < 10; ++i){
        for (int j = 10; j < 20; ++j)
            ghostArray[i][j] = array[i][j - 10];
    }
    //0-10, 20-30
    for (int i = 0; i < 10; ++i){
        for (int j = 20; j < 30; ++j)
            ghostArray[i][j] = array[i][j - 20];
    }
    //20-30, 20-30
    for (int i = 20; i < 30; ++i){
        for (int j = 20; j < 30; ++j)
            ghostArray[i][j] = array[i-20][j - 20];
    }
    //10-20, 10-20
    for (int i = 10; i < 20; ++i){
        for (int j = 10; j < 20; ++j)
            ghostArray[i][j] = array[i - 10][j - 10];
    }
    //10-20, 20-30
    for (int i = 10; i < 20; ++i){
        for (int j = 20; j < 30; ++j)
            ghostArray[i][j] = array[i - 10][j - 20];
    }
    //20-30, 20-30
    for (int i = 20; i < 30; ++i){
        for (int j = 20; j < 30; ++j)
            ghostArray[i][j] = array[i - 20][j - 20];
    }
    //20-30, 10-20
    for (int i = 20; i < 30; ++i){
        for (int j = 10; j < 20; ++j)
            ghostArray[i][j] = array[i - 20][j - 10];
    }



    //shou ghost array middle
    for (int i = 10; i < 20; ++i){
        for (int j = 10; j < 20; ++j){
            std::cout << ghostArray[i][j];

            std::cout << " ";
        }
        std::cout << endl;
    }
    std::cout << endl;

    //apply rules
    int neighbours;
    for (int i = 10; i <20; ++i){
        for (int j = 10; j <20; ++j){
            neighbours = ghostArray[i + 1][j] + ghostArray[i][j + 1] + ghostArray[i + 1][j + 1] + ghostArray[i - 1][j - 1] + ghostArray[i - 1][j] + ghostArray[i][j - 1] + ghostArray[i + 1][j - 1]+ghostArray[i-1][j + 1];


            //lonely rule
            if (neighbours <2){

                arrayNext[i][j] =0;
            }
            else if(neighbours > 3)
            {
                arrayNext[i][j] = 0;
            }
            else if (neighbours == 3){
                arrayNext[i][j] = 1;
            }
            else if (neighbours==2)
            {
                arrayNext[i][j] = ghostArray[i][j];
            }
            }

        }
    //display new array
    for (int i = 10; i < 20; ++i){
        for (int j = 10; j < 20; ++j){

            std::cout << arrayNext[i][j];
            array[i-10][j-10] = arrayNext[i][j];
            std::cout << " ";
        }
        std::cout << endl;
    }
    std::cout << endl;

    for (int i = 10; i < 20; ++i){
        for (int j = 10; j < 20; ++j){
            if(arrayNext[i][j]==1){
                arrayNext[i][j]=255;
            }


        }

    }



   frame =  cv::Mat(30,30,CV_32S, arrayNext);

//    for (int i = 10; i < 20; ++i){
//        for (int j = 10; j < 20; ++j){

//            qDebug() << arrayNext[i][j];
//            array[i-10][j-10] = arrayNext[i][j];
//            qDebug() << " ";
//        }
//        qDebug() << endl;
//    }
//    qDebug() << endl;

    std::string filename = "filename" +std::to_string(count)+".jpg";

    cv::imwrite(filename,frame);
   //cv::cvtColor(frame, frame, CV_RGB2GRAY);
   // cv::invert(frame,frame);
    //cv::resize(frame,frame,cv::Size(),2,2);
//    cv::resize(frame,frame,Size(ui->label->width(),ui->label->height()));
   // frame = frame *255;
 QImage img = QImage((uchar*) frame.data,frame.cols,frame.rows,frame.step, QImage::Format_BGR30);
   QPixmap pix = QPixmap::fromImage(img);

  ui->label->setPixmap(pix.scaled(640, 640, Qt::IgnoreAspectRatio, Qt::FastTransformation));
//    frame = cv::Mat(10,10,int)
//cv::imshow("game of life",frame);
qDebug()<<count;

//ui->label->update();
count++;



}
void MainWindow::on_pushButton_clicked()
{
   // cv::VideoCapture cap;
    //cap.open(0);
    //cv::Mat vid;






}
