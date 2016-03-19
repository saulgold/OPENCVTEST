#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgproc/types_c.h"
#include <QPicture>
#include<iostream>
#include <QtCore>
#include <time.h>
#include<QTime>
#include<qtimer.h>

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
int const mapSize = 50;

QTime myTimer;
cv::Scalar scalarArray[3*mapSize][3*mapSize];
//int array[mapSize][mapSize] = {

//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//        { 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 1, 0, 0, 0, 0, 0, 0  },
//        { 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 1, 0, 1, 0, 0, 0, 0  },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 1, 1, 0, 0, 0, 0, 0  },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 1, 0, 0  },
//        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 1, 0  },
//        { 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 1, 1, 1, 0  },
//        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
//        { 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
//    };

    //initialise arrayNExt with zeros
    int arrayNext[3*mapSize][3*mapSize];

    //int goastArray[30][30];
    //for (int i = 0; i < 30; ++i){
    //	for (int j = 0; j < 30; ++){
    //		if (i/3 =10)
    //		goastArray[i][j] = array[i][j]
    //	}
    //}
    //0-10, 0-10
    int ghostArray[3*mapSize][3*mapSize];
    int array[mapSize][mapSize];


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    for (int i = 0; i < 3*mapSize; ++i){
        for (int j = 0; j < 3*mapSize; ++j){
            arrayNext[i][j] = 0;
        }

    }


    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGUI()));
     timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateGUI(){
//  myTimer.start();

    //set ghoast array to current array

    for (int i = 0; i < mapSize; ++i){
        for (int j = 0; j < mapSize; ++j)
            ghostArray[i][j] = array[i][j];
    }
    //10-2*mapSize, 0-10
    for (int i = mapSize; i < 2*mapSize; ++i){
        for (int j = 0; j < mapSize; ++j)
            ghostArray[i][j] = array[i-mapSize][j];
    }
    //0-3*mapSize, 0-10
    for (int i = mapSize; i < 2*mapSize; ++i){
        for (int j = 0; j < mapSize; ++j)
            ghostArray[i][j] = array[i - mapSize][j];
    }
    //2*mapSize-3*mapSize, 0-10
    for (int i = 2*mapSize; i < 3*mapSize; ++i){
        for (int j = 0; j < mapSize; ++j)
            ghostArray[i][j] = array[i - 2*mapSize][j];
    }
    //0-10, 10-2*mapSize
    for (int i = 0; i < mapSize; ++i){
        for (int j = mapSize; j < 2*mapSize; ++j)
            ghostArray[i][j] = array[i][j - mapSize];
    }
    //0-10, 2*mapSize-3*mapSize
    for (int i = 0; i < mapSize; ++i){
        for (int j = 2*mapSize; j < 3*mapSize; ++j)
            ghostArray[i][j] = array[i][j - 2*mapSize];
    }
    //2*mapSize-3*mapSize, 2*mapSize-3*mapSize
    for (int i = 2*mapSize; i < 3*mapSize; ++i){
        for (int j = 2*mapSize; j < 3*mapSize; ++j)
            ghostArray[i][j] = array[i-2*mapSize][j - 2*mapSize];
    }
    //10-2*mapSize, 10-2*mapSize
    for (int i = mapSize; i < 2*mapSize; ++i){
        for (int j = mapSize; j < 2*mapSize; ++j)
            ghostArray[i][j] = array[i - mapSize][j - mapSize];
    }
    //10-2*mapSize, 2*mapSize-3*mapSize
    for (int i = mapSize; i < 2*mapSize; ++i){
        for (int j = 2*mapSize; j < 3*mapSize; ++j)
            ghostArray[i][j] = array[i - mapSize][j - 2*mapSize];
    }
    //2*mapSize-3*mapSize, 2*mapSize-3*mapSize
    for (int i = 2*mapSize; i < 3*mapSize; ++i){
        for (int j = 2*mapSize; j < 3*mapSize; ++j)
            ghostArray[i][j] = array[i - 2*mapSize][j - 2*mapSize];
    }
    //2*mapSize-3*mapSize, mapSize-2*mapSize
    for (int i = 2*mapSize; i < 3*mapSize; ++i){
        for (int j = mapSize; j < 2*mapSize; ++j)
            ghostArray[i][j] = array[i - 2*mapSize][j - mapSize];
    }





    //apply rules
    int neighbours;
    for (int i = mapSize; i <2*mapSize; ++i){
        for (int j = mapSize; j <2*mapSize; ++j){
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
                arrayNext[i][j] =1;
            }
            else if (neighbours==2)
            {
                arrayNext[i][j] = ghostArray[i][j];
                //arrayNext[i][j] =0;
            }
            }

        }
    //display new array
    for (int i = mapSize; i < 2*mapSize; ++i){
        for (int j = mapSize; j < 2*mapSize; ++j){


            array[i-mapSize][j-mapSize] = arrayNext[i][j];

        }

    }
//convert to colour

    for (int i = mapSize; i < 2*mapSize; ++i){
        for (int j = mapSize; j < 2*mapSize; ++j){
            if(arrayNext[i][j]==1){
                arrayNext[i][j]=255;
                scalarArray[i][j]=(255,0,255);
            }
            else if(arrayNext[i][j]==0){
                scalarArray[i][j]=(0,0,0);
                 arrayNext[i][j]=0;}
             else if(arrayNext[i][j]==2)
                  arrayNext[i][j]=0;
        }

    }


   frame =  cv::Mat(3*mapSize,3*mapSize,CV_32F, scalarArray);
   cv::Mat mask;
   cv::inRange(frame, cv::Scalar(0,0,255), cv::Scalar(0,0,255), mask);
   frame.setTo(cv::Scalar(100,0,100), mask);

//    for (int i = mapSize; i < 2*mapSize; ++i){
//        for (int j = mapSize; j < 2*mapSize; ++j){

//            qDebug() << arrayNext[i][j];
//            array[i-mapSize][j-mapSize] = arrayNext[i][j];
//            qDebug() << " ";
//        }
//        qDebug() << endl;
//    }
//    qDebug() << endl;

   // std::string filename = "filename" +std::to_string(count)+".jpg";

  //  cv::imwrite(filename,frame);
   //cv::cvtColor(frame, frame, CV_RGB2GRAY);
   // cv::invert(frame,frame);
    //cv::resize(frame,frame,cv::Size(),2,2);
//    cv::resize(frame,frame,Size(ui->label->width(),ui->label->height()));
   // frame = frame *255;
 QImage img = QImage((uchar*) frame.data,frame.cols,frame.rows,frame.step, QImage::Format_BGR30);
   QPixmap pix = QPixmap::fromImage(img);

  ui->label->setPixmap(pix.scaled(500, 500, Qt::IgnoreAspectRatio, Qt::FastTransformation));
//    frame = cv::Mat(10,10,int)
//cv::imshow("game of life",frame);
//qDebug()<<count;

//ui->label->update();
count++;
//qDebug()<<myTimer.elapsed();
//qDebug()<<myTimer;



}
void MainWindow::on_pushButton_clicked()
{
   // cv::VideoCapture cap;
    //cap.open(0);
    //cv::Mat vid;

    for (int i =0; i<mapSize;++i){
        for(int j=0; j<mapSize; ++j){
            if(rand()&100 >50){
            array[i][j]=1;  }
            else(array[i][j]=0);
        }
    }




}

