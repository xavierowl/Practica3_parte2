
// Librerías que contienen funciones estándar de C++
#include <iostream>
#include <cstdlib>


// Librería que contiene funciones matemáticas
#include <cmath>

// Librerías de OpenCV

// Se pueden cargar todas las Librerías incluyendo
//#include <opencv2/opencv.hpp>

// Contiene las definiciones fundamentales de las matrices e imágenes 
#include <opencv2/core/core.hpp> 
// Procesamiento de imágenes
#include <opencv2/imgproc/imgproc.hpp>
// Códecs de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp>
// Manejo de ventanas y eventos de ratón, teclado, etc.
#include <opencv2/highgui/highgui.hpp>
// Lectura de video
#include <opencv2/video/video.hpp>
// Escritura de video
#include <opencv2/videoio/videoio.hpp>

using namespace std;
using namespace cv; // Espacio de nombres de OpenCV (Contiene funciones y definiciones de varios elementos de OpenCV)

Mat erosion;
Mat dilatacion;
Mat top_hat;
Mat black_hat;
Mat operacion;

void transformar(Mat original, Mat elementoEstructurante){
    erode(original, erosion, elementoEstructurante);
    dilate(original, dilatacion, elementoEstructurante);
    morphologyEx(original, top_hat, MORPH_TOPHAT, elementoEstructurante);
    morphologyEx(original, black_hat, MORPH_BLACKHAT, elementoEstructurante);
    absdiff(top_hat, black_hat, operacion);
    add(original, operacion, operacion);
    
    namedWindow("Imagen (original)", WINDOW_AUTOSIZE);
    imshow("Imagen (original)", original);
    
    namedWindow("Imagen erosionada", WINDOW_AUTOSIZE);
    imshow("Imagen erosionada", erosion);
    
    namedWindow("Imagen dilatada", WINDOW_AUTOSIZE);
    imshow("Imagen dilatada", dilatacion);
    
    namedWindow("Imagen (Top Hat)", WINDOW_AUTOSIZE);
    imshow("Imagen (Top Hat)", top_hat);
    
    namedWindow("Imagen (Black Hat)", WINDOW_AUTOSIZE);
    imshow("Imagen (Black Hat)", black_hat);
    
    namedWindow("Imagen (Original+(Top hat-Black hat))", WINDOW_AUTOSIZE);
    imshow("Imagen (Original+(Top hat-Black hat))", operacion);
    
    //namedWindow("Kernel", WINDOW_FREERATIO);
    //imshow("Kernel", elementoEstructurante);
    
    waitKey(0);
}

int main(int argc, char *argv[]){
    //Creamos el kernel para la erosion y dilatacion
    Mat elementoEstructurante = getStructuringElement(MORPH_CROSS, Size(61,61)) * 255;
    // Leemos las imágenes de las radiografías
    Mat original = imread("radio_dental.jpeg", IMREAD_GRAYSCALE);
    resize(original, original, Size(), 0.45, 0.45);
    transformar(original, elementoEstructurante);
    
    original = imread("tac_craneo.jpeg", IMREAD_GRAYSCALE);
    resize(original, original, Size(), 0.2, 0.2);
    transformar(original, elementoEstructurante);
    
    original = imread("angio_renal.jpeg", IMREAD_GRAYSCALE);
    resize(original, original, Size(), 0.3, 0.3);
    transformar(original, elementoEstructurante);
    
    return 0;
}


