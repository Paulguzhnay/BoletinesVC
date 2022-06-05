#include <iostream>
#include <cstdlib>
#include <filesystem>

// Librerías de OpenCV
#include <opencv2/core/core.hpp> // Contiene las definiciones base de matrices y estructuras
#include <opencv2/highgui/highgui.hpp> // Interfaz gráfica de usuario
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer los distintos formatos de imágenes (JPG, PNG, etc.)
#include <opencv2/video/video.hpp> // Lectura de vídeos
#include <opencv2/videoio/videoio.hpp> // Lectura y escritura de videos
#include "Modelo.hpp"
//#include <opencv2/opencv.hpp> // Permite cargar todas las librerías de OpenCV
#include<stdlib.h>

using namespace std;
using namespace cv; // Espacio de nombres de OpenCV para llamar a los métodos de forma más directa


int thresSal=50;
int thresPimienta=45;
//--------------------------------------------------------
VideoCapture video("./Messi.mp4");
Mat frameSal;
Mat frame;
Mat framePimienta;
Mat GaussSal;
Mat GaussPimienta;
Mat MedianaPimienta;
Mat MedianaSal;
Mat BlurSal;
Mat BlurPimienta;
///
Mat GrisSal;
Mat GrisPimienta;

// Variables Parte 2
Mat original;
Mat erosion;
Mat dilatacion;
Mat top;
Mat black;
Mat resta;
Mat final;

void eventoTrackSal(int v, void *data){
}

void eventoTrackPimienta(int v, void *data){
}
int main(int argc, char *argv[]){
        namedWindow("Video", WINDOW_AUTOSIZE);
        namedWindow("Video Sal", WINDOW_AUTOSIZE);
       namedWindow("Video Pimienta", WINDOW_AUTOSIZE);
        //SAL
        /*namedWindow("Gauss Sal", WINDOW_AUTOSIZE);
        namedWindow("Blur Sal", WINDOW_AUTOSIZE);
        namedWindow("Mediana Sal", WINDOW_AUTOSIZE);*/
        namedWindow("Laplace Gaus Sal", WINDOW_AUTOSIZE);
        namedWindow("Canny Mediana Sal", WINDOW_AUTOSIZE);
        namedWindow("Laplace Blur Sal", WINDOW_AUTOSIZE);
                


        //PIMIENTA
     /*   namedWindow("Gauss Pimienta", WINDOW_AUTOSIZE);
        namedWindow("Blur Pimienta", WINDOW_AUTOSIZE);
        namedWindow("Mediana Pimienta", WINDOW_AUTOSIZE);*/
        namedWindow("Laplace Gaus Pimienta", WINDOW_AUTOSIZE);
        namedWindow("Canny  Mediana Pimienta", WINDOW_AUTOSIZE);
        namedWindow("Laplace Blur Pimienta", WINDOW_AUTOSIZE);




    if(video.isOpened()){



        while(3==3){
            video >> frame;
            if(frame.empty()){
                frameSal = frame.clone();
                framePimienta = frame.clone();
                break;
            }

            frameSal=frame.clone();
            framePimienta=frame.clone();


            createTrackbar("Sal", "Video", &thresSal, 50, eventoTrackSal,NULL );
            createTrackbar("Pimienta", "Video", &thresPimienta, 50, eventoTrackPimienta,NULL );
            imshow("Video", frame);

            
            double valorSal = 50 - thresSal;
            double valorPimienta = 50 - thresPimienta;
            for (int i = 0; i < frameSal.rows; i++)
            {
                for (int j = 0; j < frameSal.cols; j++)
                {
                    //SAL
                    int numeroRandSal = rand()%(50-1);
                    if(valorSal>numeroRandSal){
                        frameSal.at<Vec3b>(i,j)[0]=255;
                        frameSal.at<Vec3b>(i,j)[1]=255;                        
                        frameSal.at<Vec3b>(i,j)[2]=255;                    
                    }
                    //PIMIENTA
                    int numeroRandPimienta =rand()%(50-1);
                    if(valorPimienta>numeroRandPimienta){
                        framePimienta.at<Vec3b>(i,j)=(0,0,0);
                                     
                    }

                }
                
            }
            //****************************************SAL*********************************************************
            imshow("Video Sal", frameSal);
            //FILTROS SAL
            GaussianBlur(frameSal, GaussSal, Size(5, 5), 0.7);
            blur(frameSal,BlurSal,Size(5,5));
            medianBlur(frameSal,MedianaSal,3);
            
            /*imshow("Gauss Sal",GaussSal);
            imshow("Blur Sal",BlurSal);
            imshow("Mediana Sal",MedianaSal);*/
            //****************************************PIMIENTA******************************************************
            imshow("Video Pimienta",framePimienta);
            //FILTROS PIMIENTA
            GaussianBlur(framePimienta, GaussPimienta, Size(5, 5), 0.7);
            blur(framePimienta,BlurPimienta,Size(5,5));
            medianBlur(framePimienta,MedianaPimienta,3);

           /* imshow("Gauss Pimienta",GaussPimienta);
            imshow("Blur Pimienta",BlurPimienta);
            imshow("Mediana Pimienta",MedianaPimienta);*/

            //****************************************BORDES SAL**********************************************************
            //LAPLACE
            Mat laplaceGauss;
            Mat laplaceGaussFinal;
            
            Mat laplaceBlur;
            Mat laplaceBlurFinal;


            Mat medianaGris;
            Mat blurGris;
            Mat GaussGriss;


            cvtColor(GaussSal, GaussGriss, COLOR_BGR2GRAY);
            cvtColor(BlurSal, blurGris, COLOR_BGR2GRAY);
     
            
            
            Laplacian(GaussGriss,laplaceGauss,CV_16S,3);
            convertScaleAbs(laplaceGauss,laplaceGaussFinal);
            imshow("Laplace Gauss Sal",laplaceGaussFinal);


            Laplacian(blurGris,laplaceBlur,CV_16S,3);
            convertScaleAbs(laplaceBlur,laplaceBlurFinal);
            imshow("Laplace Blur Sal",laplaceBlurFinal);

            //CANY
            Mat imgGaussSal;
            Mat cannySal;
            GaussianBlur(MedianaSal, medianaGris, Size(5, 5), 0.7);
            Canny(medianaGris, cannySal, 20, 20*3.0);
            imshow("Canny Mediana Sal",cannySal);
            //****************************************BORDES PIMIENTA**********************************************************
            //LAPLACE
            Mat laplaceGaussP;
            Mat laplaceGaussFinalP;
            
            Mat laplaceBlurP;
            Mat laplaceBlurFinalP;

            Mat medianaGrisP;
            Mat blurGrisP;
            Mat GaussGrissP;

            cvtColor(GaussPimienta, GaussGrissP, COLOR_BGR2GRAY);
            cvtColor(BlurPimienta, blurGrisP, COLOR_BGR2GRAY);

            
            
            Laplacian(GaussGrissP,laplaceGaussP,CV_16S,3);
            convertScaleAbs(laplaceGaussP,laplaceGaussFinalP);
            //imshow("Laplace Gauss Pimienta",laplaceGaussFinalP);


            Laplacian(blurGrisP,laplaceBlurP,CV_16S,3);
            convertScaleAbs(laplaceBlurP,laplaceBlurFinalP);
           // imshow("Laplace Blur Pimienta",laplaceBlurFinalP);

            //CANY
            Mat imgGaussPimienta;
            Mat cannyPimienta;
            GaussianBlur(MedianaPimienta, imgGaussPimienta, Size(5, 5), 0.7);
            Canny(imgGaussPimienta, cannyPimienta, 20, 20*3.0);
          //  imshow("Canny Mediana Pimienta",cannyPimienta);


            if(waitKey(23)==27){
                break;
            }
        }
        video.release();
        cv::destroyAllWindows();

        //-------------------------------PARTE 2------------------------------------
        original =  imread("./images/photo3.jpeg");

        namedWindow("Original", WINDOW_AUTOSIZE);
        namedWindow("Erosion", WINDOW_AUTOSIZE);
        namedWindow("Dilatacion", WINDOW_AUTOSIZE);
        namedWindow("Top-Hart", WINDOW_AUTOSIZE);
        namedWindow("Black-Hart", WINDOW_AUTOSIZE);
        namedWindow("Producto-Final", WINDOW_AUTOSIZE);

        cvtColor(original, original, COLOR_BGR2GRAY);
        resize(original, original, Size(350,400));

        imshow("Original", original);

        Mat mascara = getStructuringElement(MORPH_CROSS, Size(39,39));

        erode(original, erosion, mascara, Point(-1, -1), 5);
        imshow("Erosion", erosion);

        dilate(original, dilatacion, mascara, Point(-1, -1), 5);
        imshow("Dilatacion", dilatacion);

        morphologyEx(original, top, MORPH_TOPHAT, mascara, Point(-1, -1), 5);
        imshow("Top-Hart", top);

        morphologyEx(original, black, MORPH_BLACKHAT, mascara, Point(-1, -1), 5);
        imshow("Black-Hart", black);

        absdiff(top, black, resta);
        add(original, resta, final);
        imshow("Producto-Final", final);

        waitKey();
        destroyAllWindows();

    }
}

// pip install --upgrade youtube-dl

