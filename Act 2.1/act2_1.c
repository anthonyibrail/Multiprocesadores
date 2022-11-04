#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 20

void imageGray(char inputImageName[], char outputImageName[]);
void imageBlue(char inputImageName[], char outputImageName[]);
void imageGreen(char inputImageName[], char outputImageName[]);
void imageRed(char inputImageName[], char outputImageName[]);

int main()
{   
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
                imageGray("5.bmp", "imageGray_5.bmp");
            #pragma omp section
                imageBlue("5.bmp", "imageBlue_5.bmp");
            #pragma omp section
                imageGreen("5.bmp", "imageGreen_5.bmp");
            #pragma omp section
                imageRed("5.bmp", "imageRed_5.bmp");
        }
    }
    return 0;
}

void imageGray(char inputImageName[], char outputImageName[]){
    // Obtiene el número de threads
    omp_set_num_threads(NUM_THREADS);
    // Declare pointers for image & new image
    FILE *image, *outputImage, *lecturas;
    image = fopen(inputImageName,"rb");          //Imagen original a transformar
    outputImage = fopen(outputImageName,"wb");    //Imagen transformada
    long ancho;
    long alto;
    int nthreads;

    unsigned char r, g, b;               //Pixel

    // Read first 54 header's line and move img memory counter
    unsigned char xx[54];
    for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }

    // Calculate the width & height of the original image    
    ancho = (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    alto = (long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    long n = ancho * alto * 3;
    // printf("n %li\n", n);

    // Measure initial time (startTime)
	const double startTime = omp_get_wtime();

    // Convert original img to gray scale
    nthreads = omp_get_num_threads();
    #pragma omp parallel for      
        for (int i = 0; i < n; i++){
        //while(!feof(image)){                                        //Grises
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);
            
            // Create new pixel in gray scale
            unsigned char pixel = 0.21*r + 0.72*g + 0.07*b;
            fputc(pixel, outputImage);  //b
            fputc(pixel, outputImage);  //g
            fputc(pixel, outputImage);  //r
        }

    // Measure final time (endTime)
	const double endTime = omp_get_wtime();

	// Print how much time did it take
	printf("Tiempo imagen gris = %f\n", endTime-startTime);

    // Close original image
    fclose(image);
    // Close new image
    fclose(outputImage);
}

void imageBlue(char inputImageName[], char outputImageName[]){
    // Obtiene el número de threads
    omp_set_num_threads(NUM_THREADS);
    // Declare pointers for image & new image
    FILE *image, *outputImage, *lecturas;
    image = fopen(inputImageName,"rb");          //Imagen original a transformar
    outputImage = fopen(outputImageName,"wb");    //Imagen transformada
    long ancho;
    long alto;
    int nthreads;

    unsigned char r, g, b;               //Pixel

    // Read first 54 header's line and move img memory counter
    unsigned char xx[54];
    for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }

    // Calculate the width & height of the original image    
    ancho = (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    alto = (long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    long n = ancho * alto * 3;
    // printf("n %li\n", n);

    // Measure initial time (startTime)
	const double startTime = omp_get_wtime();

    // Convert original img to gray scale
    nthreads = omp_get_num_threads();
    #pragma omp parallel for      
        for (int i = 0; i < n; i++){
        //while(!feof(image)){                                        //Grises
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);
            
            // Create new pixel in gray scale
            unsigned char pixel = 0.21*r + 0.72*g + 0.07*b;
            fputc(b, outputImage);  //b
            fputc(0, outputImage);  //g
            fputc(0, outputImage);  //r
        }

    // Measure final time (endTime)
	const double endTime = omp_get_wtime();

	// Print how much time did it take
	printf("Tiempo imagen azul = %f\n", endTime-startTime);

    // Close original image
    fclose(image);
    // Close new image
    fclose(outputImage);
}

void imageGreen(char inputImageName[], char outputImageName[]){
    // Obtiene el número de threads
    omp_set_num_threads(NUM_THREADS);
    // Declare pointers for image & new image
    FILE *image, *outputImage, *lecturas;
    image = fopen(inputImageName,"rb");          //Imagen original a transformar
    outputImage = fopen(outputImageName,"wb");    //Imagen transformada
    long ancho;
    long alto;
    int nthreads;

    unsigned char r, g, b;               //Pixel

    // Read first 54 header's line and move img memory counter
    unsigned char xx[54];
    for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }

    // Calculate the width & height of the original image    
    ancho = (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    alto = (long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    long n = ancho * alto * 3;
    // printf("n %li\n", n);

    // Measure initial time (startTime)
	const double startTime = omp_get_wtime();

    // Convert original img to gray scale
    nthreads = omp_get_num_threads();
    #pragma omp parallel for      
        for (int i = 0; i < n; i++){
        //while(!feof(image)){                                        //Grises
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);
            
            // Create new pixel in gray scale
            unsigned char pixel = 0.21*r + 0.72*g + 0.07*b;
            fputc(0, outputImage);  //b
            fputc(g, outputImage);  //g
            fputc(0, outputImage);  //r
        }

    // Measure final time (endTime)
	const double endTime = omp_get_wtime();

	// Print how much time did it take
	printf("Tiempo imagen verde = %f\n", endTime-startTime);

    // Close original image
    fclose(image);
    // Close new image
    fclose(outputImage);
}

void imageRed(char inputImageName[], char outputImageName[]){
    // Obtiene el número de threads
    omp_set_num_threads(NUM_THREADS);
    // Declare pointers for image & new image
    FILE *image, *outputImage, *lecturas;
    image = fopen(inputImageName,"rb");          //Imagen original a transformar
    outputImage = fopen(outputImageName,"wb");    //Imagen transformada
    long ancho;
    long alto;
    int nthreads;

    unsigned char r, g, b;               //Pixel

    // Read first 54 header's line and move img memory counter
    unsigned char xx[54];
    for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }

    // Calculate the width & height of the original image    
    ancho = (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    alto = (long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    long n = ancho * alto * 3;
    // printf("n %li\n", n);

    // Measure initial time (startTime)
	const double startTime = omp_get_wtime();

    // Convert original img to gray scale
    nthreads = omp_get_num_threads();
    #pragma omp parallel for      
        for (int i = 0; i < n; i++){
        //while(!feof(image)){                                        //Grises
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);
            
            // Create new pixel in gray scale
            unsigned char pixel = 0.21*r + 0.72*g + 0.07*b;
            fputc(0, outputImage);  //b
            fputc(0, outputImage);  //g
            fputc(r, outputImage);  //r
        }

    // Measure final time (endTime)
	const double endTime = omp_get_wtime();

	// Print how much time did it take
	printf("Tiempo imagen rojo = %f\n", endTime-startTime);

    // Close original image
    fclose(image);
    // Close new image
    fclose(outputImage);
}