
#include "Modelo.hpp"

//#include <opencv2/opencv.hpp> // Permite cargar todas las librerías de OpenCV

using namespace std;
using namespace cv;
using namespace std;

vector<string> listarDir(string d){
    vector<string> archivos;
    archivos.clear();
    for(auto &entrada: std::filesystem::directory_iterator(d)){
        archivos.push_back(entrada.path());
    }

    return archivos;
}
bool archivo_existe(string nombre)
{
	ifstream archivo(nombre.c_str());
	return archivo.good();
}

void CrearCarpeta(string ubicacion){
	if (archivo_existe(ubicacion))
	{}
	else
	{
        std::filesystem::create_directory(ubicacion);
	}
}


void Modelo::parte1(){
    time_t tiempoHG1, tiempoHG2, tiempoHC1,tiempoHC2,tiempoTG1,tiempoTG2;
    string pathNombreCarpetas = "/home/computacion/Documentos/Vision/Boletines/Practica01/Imagenes";
    vector<string> NombreCarpetas = listarDir(pathNombreCarpetas);
    int c=0;
            string pathGris="/home/computacion/Documentos/Vision/Boletines/Practica01/ImgGris";
            string pathHistogramaColor="/home/computacion/Documentos/Vision/Boletines/Practica01/ImgHistColor";
            string pathHIstogramaGris="/home/computacion/Documentos/Vision/Boletines/Practica01/ImgHistGris";
            CrearCarpeta(pathGris);
            CrearCarpeta(pathHistogramaColor);
            CrearCarpeta(pathHIstogramaGris);
    for (string nombre:NombreCarpetas)
    {
        vector<string> nombreImagenes = listarDir(nombre);
        for (string nombreI : nombreImagenes)
        {
            Mat imagen = imread(nombreI);
            //HIstograma de Color
            tiempoHC1=clock();
                int *histo = new int[256];
                for(int i=0;i<256;i++){
                    histo[i] = 0;
                }

                int pixel = 0;
                for(int i=0;i<imagen.rows;i++){
                    for(int j=0;j<imagen.cols;j++){
                        pixel = imagen.at<uchar>(i,j);
                        histo[pixel]++;
                    }
                }
                int maximo = 0;
                for(int i=0;i<256;i++){
                    if (maximo<histo[i]){
                        maximo = histo[i];
                    }
                }
                int ancho = 1024;
                int alto = 320;
                Mat histograma = Mat(Size(ancho, alto), CV_8UC3, Scalar(0,0,0));
                double escala = ((double)alto) / ((double) maximo);
                for(int i=0;i<256;i++){
                    line(histograma, Point(i*3,alto), Point(i*3, alto-escala*histo[i]), Scalar(0,0,255), 2);
                }
                string pathGuardarHistColor=pathHistogramaColor+"/ImgHistC-"+to_string(c)+".jpg";
                imwrite(pathGuardarHistColor, histograma);
            tiempoHC2=clock();
            // Transformacion de Color a Gris
            tiempoTG1=clock();
                Mat grisCV;
                cvtColor(imagen, grisCV, COLOR_BGR2GRAY);
                string pathGuardarGris=pathGris+"/imgGris-"+to_string(c)+".jpg";
                imwrite(pathGuardarGris,grisCV);
            tiempoTG2=clock();    
            //histogramaGris de Grises
            tiempoHG1=clock();
                int *histoG = new int[256];
                for(int i=0;i<256;i++){
                    histoG[i] = 0;
                }

                pixel = 0;
                for(int i=0;i<grisCV.rows;i++){
                    for(int j=0;j<grisCV.cols;j++){
                        pixel = grisCV.at<uchar>(i,j);
                        histoG[pixel]++;
                    }
                }
                maximo = 0;
                for(int i=0;i<256;i++){
                    if (maximo<histoG[i]){
                        maximo = histoG[i];
                    }
                }
                ancho = 1024;
                alto = 320;
                Mat histogramaGris = Mat(Size(ancho, alto), CV_8UC3, Scalar(0,0,0));
                escala = ((double)alto) / ((double) maximo);
                for(int i=0;i<256;i++){
                    line(histogramaGris, Point(i*3,alto), Point(i*3, alto-escala*histoG[i]), Scalar(0,0,255), 2);
                }
                string pathGuardarHistGris=pathHIstogramaGris+"/ImgHistG-"+to_string(c)+".jpg";
                imwrite(pathGuardarHistGris,histogramaGris);
            tiempoHG2=clock();
                c=c+1;

        }
        
    }
    double tiempoHistColor=(tiempoHC2-(double)tiempoHC1)/CLOCKS_PER_SEC;
    double tiempoHistGris=((double)tiempoHG2-(double)tiempoHG1)/CLOCKS_PER_SEC;
    double tiempoTransGris=((double)tiempoTG2-(double)tiempoTG1)/CLOCKS_PER_SEC;

    ofstream MyFile("Reporte.txt");
    // Write to the file
    MyFile << "El tiempo de transformacion de las imagenes de color a gris es: "+to_string(tiempoTransGris)+" seg"+'\n';
    MyFile << "El tiempo de generacion de los histogramas de color es: "+to_string(tiempoHistColor)+" seg"+'\n';
    MyFile << "El tiempo de generacion de los histogramas de escala de grises es: "+to_string(tiempoHistGris)+" seg"+'\n';    
    // Close the file
    MyFile.close();
    
}

//RUTAS TRAIN Y TEST
string ubiGeneral="./Parte2";
string ubiTest=ubiGeneral+"/Test";
string ubiTrain=ubiGeneral+"/Train";
//Interna COLOR Test
string ubiInternaTest1 = ubiTest+"/Test-Carp1";
string ubiInternaTest2 = ubiTest+"/Test-Carp2";
string ubiInternaTest3 = ubiTest+"/Test-Carp3";
string ubiInternaTest4 = ubiTest+"/Test-Carp4";
//Interna COLOR Train
string ubiInternaTrain1 = ubiTrain+"/Train-Carp1";
string ubiInternaTrain2 = ubiTrain+"/Train-Carp2";
string ubiInternaTrain3 = ubiTrain+"/Train-Carp3";
string ubiInternaTrain4 = ubiTrain+"/Train-Carp4";

//Interna GRIS Test
string ubiGrisInternaTest1 = ubiTest+"/TestGris-Carp1";
string ubiGrisInternaTest2 = ubiTest+"/TestGris-Carp2";
string ubiGrisInternaTest3 = ubiTest+"/TestGris-Carp3";
string ubiGrisInternaTest4 = ubiTest+"/TestGris-Carp4";
//Interna GRIS Train
string ubiGrisInternaTrain1 = ubiTrain+"/TrainGris-Carp1";
string ubiGrisInternaTrain2 = ubiTrain+"/TrainGris-Carp2";
string ubiGrisInternaTrain3 = ubiTrain+"/TrainGris-Carp3";
string ubiGrisInternaTrain4 = ubiTrain+"/TrainGris-Carp4";

//Creacion de Carpetas para el Train y Test
void Modelo::CarpetasParte2(){
//Carpeta general
CrearCarpeta(ubiGeneral);
// CARPETA GENERAL TRAIN Y TEST
CrearCarpeta(ubiTest);
CrearCarpeta(ubiTrain);
//INTERNA COLOR TEST
CrearCarpeta(ubiInternaTest1);
CrearCarpeta(ubiInternaTest2);
CrearCarpeta(ubiInternaTest3);
CrearCarpeta(ubiInternaTest4);
//INTERNA COLOR TRAIN
CrearCarpeta(ubiInternaTrain1);
CrearCarpeta(ubiInternaTrain2);
CrearCarpeta(ubiInternaTrain3);
CrearCarpeta(ubiInternaTrain4);

//INTERNA GRIS TEST
CrearCarpeta(ubiGrisInternaTest1);
CrearCarpeta(ubiGrisInternaTest2);
CrearCarpeta(ubiGrisInternaTest3);
CrearCarpeta(ubiGrisInternaTest4);
//INTERNA GRIS TRAIN
CrearCarpeta(ubiGrisInternaTrain1);
CrearCarpeta(ubiGrisInternaTrain2);
CrearCarpeta(ubiGrisInternaTrain3);
CrearCarpeta(ubiGrisInternaTrain4);
}



void TrainTest(string path, string ubiTrain,string ubiTest,string ubiGrisTrain,string ubiGrisTest){
    vector<string>nombre=listarDir(path);
    int TotalHP = nombre.size();
    int trainHP = TotalHP*0.80;
    int testHP = TotalHP-trainHP;

    int vectorTrain [trainHP];
    int vectorTest [testHP];
    int vectorTotal [TotalHP];
    int g;
    //TRAIN
    for(int i = 0; i < trainHP; i++)
    {
        g=i;
        int num = 1 + rand() % ((TotalHP+1) - 1);
        for (int j = 0; j <=g; j++)
        {
            if(num==vectorTrain[j]){
                g=g-g;
                i=i-1;
            }
            while ((g==i) && (num!=vectorTrain[j] &&(j==i)))
            {
                vectorTrain[i]=num;
            }   
        }
    }

    for (int i = 0; i < trainHP; i++)
    {
        int numero = vectorTrain[i];
        if(numero<10){
            string ruta = path+"/image_000"+to_string(numero)+".jpg";
            Mat imagen = imread(ruta);
            string pathGuardar = ubiTrain+"/image_000"+to_string(numero)+".jpg";
           imwrite(pathGuardar,imagen);
            //GRIS
            Mat grisCV;
            cvtColor(imagen, grisCV, COLOR_BGR2GRAY);
            string pathGuardarGris=ubiGrisTrain+"/image_000"+to_string(numero)+".jpg";
            imwrite(pathGuardarGris,grisCV);
        }else if (numero>9 && numero<100){
            string rutaHeadPhone = path+"/image_00"+to_string(numero)+".jpg";
            Mat imagen = imread(rutaHeadPhone);
            string pathGuardarHeahPhone = ubiTrain+"/image_00"+to_string(numero)+".jpg";
            imwrite(pathGuardarHeahPhone,imagen);
            //GRIS
            Mat grisCV;
            cvtColor(imagen, grisCV, COLOR_BGR2GRAY);
            string pathGuardarGris=ubiGrisTrain+"/image_00"+to_string(numero)+".jpg";
            imwrite(pathGuardarGris,grisCV);
        }else if (numero>99 && numero<1000){
            string rutaIbis = path+"/image_0"+to_string(numero)+".jpg";
            Mat imagen = imread(rutaIbis);
            string pathGuardarIbis = ubiTrain+"/image_0"+to_string(numero)+".jpg";
            imwrite(pathGuardarIbis,imagen);
            //GRIS
            Mat grisCV;
            cvtColor(imagen, grisCV, COLOR_BGR2GRAY);
            string pathGuardarGris=ubiGrisTrain+"/image_0"+to_string(numero)+".jpg";
            imwrite(pathGuardarGris,grisCV);            
        }
    }
    
//----------------------------------PROCESO DEL TEST----------------------------------------
    vector<string> nombreTrain = listarDir(ubiTrain);
    vector<string> nombreGeneral = listarDir(path);

    vector<string> nombreImgTrain;
    vector<string> nombreImgGeneral;
    string n1,n2,n3,n4,n5,n6,n7,n8,n9,n10;
    string t1,t2,t3,t4,t5;    
    for (string nombreG : nombreGeneral)
    {
        stringstream nombreG2(nombreG);
        getline(nombreG2,n1,'/');
        getline(nombreG2,n2,'/'); 
        getline(nombreG2,n3,'/');
        getline(nombreG2,n4,'/');
        getline(nombreG2,n5,'/');
        getline(nombreG2,n6,'/');
        getline(nombreG2,n7,'/');
        getline(nombreG2,n8,'/');
        getline(nombreG2,n9,'/');
        getline(nombreG2,n10,'/');
        nombreImgGeneral.push_back(n10);       
    }
        for (string nombreT: nombreTrain)
        {
            stringstream nombreT2(nombreT);
            getline(nombreT2,t1,'/');
            getline(nombreT2,t2,'/'); 
            getline(nombreT2,t3,'/');
            getline(nombreT2,t4,'/');
            getline(nombreT2,t5,'/');
            nombreImgTrain.push_back(t5);
        }
//---------------------------TEST---------------------------------
    int j;
    for (int i = 0; i < TotalHP; i++)
    {
        for (j = 0; j < trainHP; j++)
        {
            if(nombreImgGeneral[i]==nombreImgTrain[j]){
                break;
            }
        }
        if(j==trainHP){
            string nombrePosGeneral=nombreImgGeneral[i];
            string pathImagenGeneral= path+"/"+nombrePosGeneral;
            Mat imagen = imread(pathImagenGeneral);
            string pathTestHP=ubiTest+"/"+nombrePosGeneral;
            imwrite(pathTestHP,imagen); 
            //GRIS
            Mat grisCV;
            cvtColor(imagen, grisCV, COLOR_BGR2GRAY);
            string pathGuardarGris=ubiGrisTest+"/"+nombrePosGeneral;
            imwrite(pathGuardarGris,grisCV);


        }    
    }
}

void Modelo::parte2(){
    string pathMotorbikes ="/home/computacion/Documentos/Vision/Boletines/Practica01/Imagenes/Motorbikes";
    string pathAnt="/home/computacion/Documentos/Vision/Boletines/Practica01/Imagenes/ant";
    string pathSunflowers="/home/computacion/Documentos/Vision/Boletines/Practica01/Imagenes/sunflower";
    string pathWatch="/home/computacion/Documentos/Vision/Boletines/Practica01/Imagenes/watch";
    TrainTest(pathAnt,ubiInternaTrain1,ubiInternaTest1,ubiGrisInternaTrain1,ubiGrisInternaTest1);
    TrainTest(pathMotorbikes,ubiInternaTrain2,ubiInternaTest2,ubiGrisInternaTrain2,ubiGrisInternaTest2);
    TrainTest(pathSunflowers,ubiInternaTrain3,ubiInternaTest3,ubiGrisInternaTrain3,ubiGrisInternaTest3);        
    TrainTest(pathWatch,ubiInternaTrain4,ubiInternaTest4,ubiGrisInternaTrain4,ubiGrisInternaTest4);    
//---------------------------------------LISTADO IMAGENES COLOR TEST----------------------------------------------------------------------
    vector <string> ImgCarpTest1= listarDir(ubiInternaTest1);
    vector <string> ImgCarpTest2= listarDir(ubiInternaTest2);
    vector <string> ImgCarpTest3= listarDir(ubiInternaTest3);
    vector <string> ImgCarpTest4= listarDir(ubiInternaTest4);
//---------------------------------------LISTADO IMAGENES COLOR TRAIN----------------------------------------------------------------------
    vector <string> ImgCarpTrain1= listarDir(ubiInternaTrain1);
    vector <string> ImgCarpTrain2= listarDir(ubiInternaTrain2);
    vector <string> ImgCarpTrain3= listarDir(ubiInternaTrain3);
    vector <string> ImgCarpTrain4= listarDir(ubiInternaTrain4);
//---------------------------------------LISTADO IMAGENES GRIS TEST----------------------------------------------------------------------
    vector <string> ImgCarpGrisTest1= listarDir(ubiGrisInternaTest1);
    vector <string> ImgCarpGrisTest2= listarDir(ubiGrisInternaTest2);
    vector <string> ImgCarpGrisTest3= listarDir(ubiGrisInternaTest3);
    vector <string> ImgCarpGrisTest4= listarDir(ubiGrisInternaTest4);
//---------------------------------------LISTADO IMAGENES GRIS TRAIN----------------------------------------------------------------------
    vector <string> ImgCarpGrisTrain1= listarDir(ubiGrisInternaTrain1);
    vector <string> ImgCarpGrisTrain2= listarDir(ubiGrisInternaTrain2);
    vector <string> ImgCarpGrisTrain3= listarDir(ubiGrisInternaTrain3);
    vector <string> ImgCarpGrisTrain4= listarDir(ubiGrisInternaTrain4);

//-----------------------------------------------------VECTORES COLOR---------------------------------------------------------------------------    
//----------------------------------- VECTORES ACIERTOS----------------------------------------------
    vector <int> AciertosFila1_1;
    vector <int> AciertosFila2_2;    
    vector <int> AciertosFila3_3;
    vector <int> AciertosFila4_4;

//----------------------------------- VECTORES FALLOS----------------------------------------------
    //FILA1
        vector <int> FalloFila1_2;
        vector <int> FalloFila1_3;
        vector <int> FalloFila1_4;
    //FILA2
        vector <int> FalloFila2_1;
        vector <int> FalloFila2_3;
        vector <int> FalloFila2_4;
    //FILA3
        vector <int> FalloFila3_1;
        vector <int> FalloFila3_2;
        vector <int> FalloFila3_4;
    //FILA4
        vector <int> FalloFila4_1;
        vector <int> FalloFila4_2;
        vector <int> FalloFila4_3;

//-----------------------------------------------------VECTORES GRIS---------------------------------------------------------------------------    
//----------------------------------- VECTORES ACIERTOS----------------------------------------------
    vector <int> AciertosGrisFila1_1;
    vector <int> AciertosGrisFila2_2;    
    vector <int> AciertosGrisFila3_3;
    vector <int> AciertosGrisFila4_4;

//----------------------------------- VECTORES FALLOS----------------------------------------------
    //FILA1
        vector <int> FalloGrisFila1_2;
        vector <int> FalloGrisFila1_3;
        vector <int> FalloGrisFila1_4;
    //FILA2
        vector <int> FalloGrisFila2_1;
        vector <int> FalloGrisFila2_3;
        vector <int> FalloGrisFila2_4;
    //FILA3
        vector <int> FalloGrisFila3_1;
        vector <int> FalloGrisFila3_2;
        vector <int> FalloGrisFila3_4;
    //FILA4
        vector <int> FalloGrisFila4_1;
        vector <int> FalloGrisFila4_2;
        vector <int> FalloGrisFila4_3;

//----------------------------------------------COMPARACION DE IMAGENES COLOR---------------------------------------------------------
//-----------------------IMAGENES TEST 1 vs TODAS IMAGENES TRAIN
for (string nombreImgTest: ImgCarpTest1)
{
//--------------------------------CARPETA 1-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain1)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            AciertosFila1_1.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 2-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain2)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila1_2.push_back(ResultadoFinal);
        }
    }

//--------------------------------CARPETA 3-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain3)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila1_3.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 4-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain4)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila1_4.push_back(ResultadoFinal);
        }
    }

}

//-----------------------IMAGENES TEST 2 vs TODAS IMAGENES TRAIN
for (string nombreImgTest: ImgCarpTest2)
{
//--------------------------------CARPETA 1-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain1)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila2_1.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 2-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain2)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            AciertosFila2_2.push_back(ResultadoFinal);
        }
    }

//--------------------------------CARPETA 3-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain3)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila2_3.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 4-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain4)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila2_4.push_back(ResultadoFinal);
        }
    }
}
//-----------------------IMAGENES TEST 3 vs TODAS IMAGENES TRAIN
for (string nombreImgTest: ImgCarpTest3)
{
//--------------------------------CARPETA 1-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain1)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila3_1.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 2-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain2)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila3_2.push_back(ResultadoFinal);
        }
    }

//--------------------------------CARPETA 3-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain3)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            AciertosFila3_3.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 4-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain4)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila3_4.push_back(ResultadoFinal);
        }
    }

}
//-----------------------IMAGENES TEST 4 vs TODAS IMAGENES TRAIN
for (string nombreImgTest: ImgCarpTest4)
{
//--------------------------------CARPETA 1-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain1)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila4_1.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 2-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain2)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila4_2.push_back(ResultadoFinal);
        }
    }

//--------------------------------CARPETA 3-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain3)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloFila4_3.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 4-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpTrain4)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            AciertosFila4_4.push_back(ResultadoFinal);
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------COMPARACION DE IMAGENES GRIS---------------------------------------------------------
//-----------------------IMAGENES TEST GRIS 1 vs TODAS IMAGENES TRAIN
for (string nombreImgTest: ImgCarpGrisTest1)
{
//--------------------------------CARPETA 1-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain1)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            AciertosGrisFila1_1.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 2-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain2)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila1_2.push_back(ResultadoFinal);
        }
    }

//--------------------------------CARPETA 3-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain3)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila1_3.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 4-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTest4)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila1_4.push_back(ResultadoFinal);
        }
    }

}

//-----------------------IMAGENES TEST GRIS 2 vs TODAS IMAGENES TRAIN
for (string nombreImgTest: ImgCarpGrisTest2)
{
//--------------------------------CARPETA 1-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain1)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila2_1.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 2-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain2)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            AciertosGrisFila2_2.push_back(ResultadoFinal);
        }
    }

//--------------------------------CARPETA 3-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain3)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila2_3.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 4-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain4)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila2_4.push_back(ResultadoFinal);
        }
    }
}
//-----------------------IMAGENES TEST  GRIS 3 vs TODAS IMAGENES TRAIN
for (string nombreImgTest: ImgCarpGrisTest3)
{
//--------------------------------CARPETA 1-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain1)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50 ){
            FalloGrisFila3_1.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 2-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain2)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50 ){
            FalloGrisFila3_2.push_back(ResultadoFinal);
        }
    }

//--------------------------------CARPETA 3-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain3)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50 ){
            AciertosGrisFila3_3.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 4-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain4)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila3_4.push_back(ResultadoFinal);
        }
    }

}
//-----------------------IMAGENES TEST GRIS 4 vs TODAS IMAGENES TRAIN
for (string nombreImgTest: ImgCarpGrisTest4)
{
//--------------------------------CARPETA 1-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain1)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila4_1.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 2-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain2)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila4_2.push_back(ResultadoFinal);
        }
    }

//--------------------------------CARPETA 3-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain3)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            FalloGrisFila4_3.push_back(ResultadoFinal);
        }
    }
//--------------------------------CARPETA 4-----------------------------------------------------------------
    for (string nombreImgTrain: ImgCarpGrisTrain4)
    {
        int suma=0;
        Mat imagenTest = imread(nombreImgTest);
        Mat imagenTrain = imread(nombreImgTrain);
        resize(imagenTrain, imagenTrain, Size(imagenTest.cols,imagenTest.rows),0,0,1);

        Mat resta;
        absdiff(imagenTest, imagenTrain, resta);
        int pixG = 0;
        for(int i=0;i<resta.rows;i++){
            for(int j=0;j<resta.cols;j++){
                pixG = resta.at<uchar>(i,j);
                suma=suma+pixG;
            }
        }
        int ResultadoFinal= suma/(imagenTest.cols*imagenTest.rows);
        if(ResultadoFinal<50){
            AciertosGrisFila4_4.push_back(ResultadoFinal);
        }
    }
}




//---------------------------------------------------MATRIZ CONFUSION COLOR-----------------------------------------------------------------------
int Acfila1_1=AciertosFila1_1.size();
int Acfila2_2=AciertosFila2_2.size();
int Acfila3_3=AciertosFila3_3.size();
int Acfila4_4=AciertosFila4_4.size();
//----------------------------------------------
int FFila1_2=FalloFila1_2.size();
int FFila1_3=FalloFila1_3.size();
int FFila1_4=FalloFila1_4.size();
//----------------------------------------
int FFila2_1=FalloFila2_1.size();
int FFila2_3=FalloFila2_3.size();
int FFila2_4=FalloFila2_4.size();
//-----------------------------------------
int FFila3_1=FalloFila3_1.size();
int FFila3_2=FalloFila3_2.size();
int FFila3_4=FalloFila3_4.size();
//----------------------------------------
int FFila4_1=FalloFila4_1.size();
int FFila4_2=FalloFila4_2.size();
int FFila4_3=FalloFila4_3.size();


    cout<<"MATRIZ DE CONFUSION IMAGENES DE COLOR"<<endl;
    cout<<"Nobmre"<<" |"<<" Train 1 "<<" |"<<" Train 2 "<<" |"<<" Train 3 "<<" |"<<" Train 4 "<<endl;
    cout<<"Test 1"<< "|" << Acfila1_1 <<"|"<<FFila1_2<<"    |"<<FFila1_3<<"    |"<<FFila1_4<<endl;
    cout<<"Test 2"<<" |"<<FFila2_1<<"    |"<<Acfila2_2<<"   |"<<FFila2_3<<"    |"<<FFila2_4<<endl;
    cout<<"Test 3"<<" |"<<FFila3_1<<"    |"<<FFila3_2<<"    |"<<Acfila3_3<<"   |"<<FFila3_4<<endl;
    cout<<"Test 4"<<" |"<<FFila4_1<<"    |"<<FFila4_2<<"    |"<<FFila4_3<<"    |"<<Acfila4_4<<endl;





//---------------------------------------------------MATRIZ CONFUSION GRIS-----------------------------------------------------------------------
int AcGrisfila1_1=AciertosGrisFila1_1.size();
int AcGrisfila2_2=AciertosGrisFila2_2.size();
int AcGrisfila3_3=AciertosGrisFila3_3.size();
int AcGrisfila4_4=AciertosGrisFila4_4.size();
//----------------------------------------------
int FGrisFila1_2=FalloGrisFila1_2.size();
int FGrisFila1_3=FalloGrisFila1_3.size();
int FGrisFila1_4=FalloGrisFila1_4.size();
//----------------------------------------
int FGrisFila2_1=FalloGrisFila2_1.size();
int FGrisFila2_3=FalloGrisFila2_3.size();
int FGrisFila2_4=FalloGrisFila2_4.size();
//-----------------------------------------
int FGrisFila3_1=FalloGrisFila3_1.size();
int FGrisFila3_2=FalloGrisFila3_2.size();
int FGrisFila3_4=FalloGrisFila3_4.size();
//----------------------------------------
int FGrisFila4_1=FalloGrisFila4_1.size();
int FGrisFila4_2=FalloGrisFila4_2.size();
int FGrisFila4_3=FalloGrisFila4_3.size();


    cout<<"MATRIZ DE CONFUSION IMAGENES GRIS"<<endl;
    cout<<"Nobmre"<<" |"<<" Train 1 "<<" |"<<" Train 2 "<<" |"<<" Train 3 "<<" |"<<" Train 4 "<<endl;
    cout<<"Test 1"<< "|" << AcGrisfila1_1 <<"|"<<FGrisFila1_2<<"    |"<<FGrisFila1_3<<"    |"<<FGrisFila1_4<<endl;
    cout<<"Test 2"<<" |"<<FGrisFila2_1<<"    |"<<AcGrisfila2_2<<"   |"<<FGrisFila2_3<<"    |"<<FGrisFila2_4<<endl;
    cout<<"Test 3"<<" |"<<FGrisFila3_1<<"    |"<<FGrisFila3_2<<"    |"<<AcGrisfila3_3<<"   |"<<FGrisFila3_4<<endl;
    cout<<"Test 4"<<" |"<<FGrisFila4_1<<"    |"<<FGrisFila4_2<<"    |"<<FGrisFila4_3<<"    |"<<AcGrisfila4_4<<endl;

}
//------------------------PARTE 3-------------------------------

int thres = 0;
Mat frame;
Mat conversion;
Mat nueva;
VideoCapture video("/dev/video0");
int n = 0;

void eventoTrack(int v, void*data){ 
    
}

void locator(int event, int x, int y, int flags, void* userdata){ //function to track mouse movement and click//
   if (event == EVENT_LBUTTONDOWN){ //when left button clicked//
        string path = "/home/computacion/Descargas/Practica1/Imagenes Guardadas/imagen"+to_string(n)+".jpeg";
        imwrite(path,conversion);
        n += 1;
   }
}

void Modelo::parte3(){
    if(video.isOpened()){

        namedWindow("Video", WINDOW_AUTOSIZE);
        namedWindow("Conversion", WINDOW_AUTOSIZE);

        while(3==3){
            video >> frame;

            if(frame.empty()){
                break;
            }
            imshow("Video", frame);
            createTrackbar("Color", "Video", &thres, 4, eventoTrack, NULL);
            setMouseCallback("Conversion", locator, NULL);
            if(waitKey(33)==27){
                break;
            }

            switch(thres){
                case 0:
                    imshow("Conversion", frame);
                    break;
                case 1:
                    cvtColor(frame, conversion, COLOR_BGR2HSV);
                    imshow("Conversion", conversion);
                    cout << "Valor: " << thres << endl;
                    break;
                case 2:
                    cvtColor(frame, conversion, COLOR_BGR2Lab);
                    imshow("Conversion", conversion);
                    cout << "Valor: " << thres << endl;
                    break;
                case 3:
                    cvtColor(frame, conversion, COLOR_BGR2YCrCb);
                    imshow("Conversion", conversion);
                    cout << "Valor: " << thres << endl;
                    break;
                case 4:
                    cvtColor(frame, conversion, COLOR_BGR2GRAY);
                    imshow("Conversion", conversion);
                    cout << "Valor: " << thres << endl;
                    break;
            }
            
        }    
        video.release();
        destroyAllWindows();
    }
}