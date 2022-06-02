
#include <iostream>
#include <cstdlib>

// Librerías de OpenCV
#include <opencv2/core/core.hpp> // Contiene las definiciones base de matrices y estructuras
#include <opencv2/highgui/highgui.hpp> // Interfaz gráfica de usuario
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer los distintos formatos de imágenes (JPG, PNG, etc.)
#include <opencv2/video/video.hpp> // Lectura de vídeos
#include <opencv2/videoio/videoio.hpp> // Lectura y escritura de videos

//#include <opencv2/opencv.hpp> // Permite cargar todas las librerías de OpenCV

using namespace std;
using namespace cv; // Espacio de nombres de OpenCV para llamar a los métodos de forma más directa

int main(int argc, char *argv[]){

    // Creamos una ventana vacía
    namedWindow("Imagen", WINDOW_AUTOSIZE);

    // Lectura de la Imagen
    Mat imagen = imread("./catedral-san-basilio-moscu-rusia.jpg");

    // Como obtener las caracteristicas de la imagen
    cout << "Ancho Imagen: " << imagen.cols << " Alto Imagen: " << imagen.rows << " Canales: " << imagen.channels() << endl;

    // Como acceder a un pixel de la imagen
    Vec3b pixel = imagen.at<Vec3b>(93, 123);

    // Recordar que en OpenCV la imagen normalmente viene en formato BGR
    cout << "Rojo: " << (int) pixel[2] << " Verde: " << (int) pixel[1] << " Azul: " << (int) pixel[0] << endl;

    // Manipulación de Pixeles
    for(int i=100;i<123;i++){
        for(int j=100;j<123;j++){
            imagen.at<Vec3b>(i,j) = Vec3b(52, 230, 233);
        }
    }

    // Creación de una imagen vacía
    //Mat gris = Mat::zeros(Size(imagen.cols, imagen.rows),CV_8UC1);
    Mat gris = Mat(Size(imagen.cols, imagen.rows), CV_8UC1, Scalar(123));

    double promedio = 0.0;
    // Convertimos la imagen a colores en escala de grises usando un simple promedio
    for(int i=0;i<imagen.rows;i++){
        for(int j=0;j<imagen.cols;j++){
            pixel = imagen.at<Vec3b>(i,j);
            promedio = (pixel[0]+pixel[1]+pixel[2])/3.0;
            gris.at<uchar>(i,j) = (int) promedio;
        }
    }

    Mat grisCV;
    // Usamos el método propio de OpenCV para conversión entre espacios de color:
    cvtColor(imagen, grisCV, COLOR_BGR2GRAY);

    // Restamos las dos imágenes para ver las diferencias en las opciones de conversión en escala de grises
    Mat resta;
    absdiff(gris, grisCV, resta);

    // Resaltamos las zonas de la imagen que son distintas
    // Cómo crear un clon de una imagen
    int pixG = 0;
    Mat copia = Mat::zeros(Size(resta.cols, resta.rows), CV_8UC3);//resta.clone();
    for(int i=0;i<resta.rows;i++){
        for(int j=0;j<resta.cols;j++){
            pixG = resta.at<uchar>(i,j);
            if(pixG>0){
                //copia.at<uchar>(i,j) = 255;
                copia.at<Vec3b>(i,j) = Vec3b(1,1,200);
            }
        }
    }

    // Leer una imagen directo en escala de grises
    Mat grisLectura = imread("./catedral-san-basilio-moscu-rusia.jpg", IMREAD_GRAYSCALE);

    namedWindow("Gris", WINDOW_AUTOSIZE);
    namedWindow("GrisCV", WINDOW_AUTOSIZE);
    namedWindow("Resta", WINDOW_AUTOSIZE);
    namedWindow("Resta Resaltada", WINDOW_AUTOSIZE);

    // Mostramos la imagen en la ventana
    imshow("Imagen", imagen);
    imshow("Gris", gris);
    imshow("GrisCV", grisCV);
    imshow("Resta", resta);
    imshow("Resta Resaltada", copia);

    // Comando para generar una pausa hasta que se presione cualquier tecla
    waitKey();

    // Liberar recursos (destruir las ventanas de memoria)
    destroyAllWindows();

    return 0;
}


