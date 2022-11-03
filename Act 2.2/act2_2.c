#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NUM_THREADS 200

void blurring(char outputImage[], int sizeM);
void blurring_inv(char outputImgName[], int sizeM);

int main(){
  #pragma omp parallel
    {
        #pragma omp sections
        {
        #pragma omp section
            blurring("sample_blur_sections_gris1.bmp", 3);
        #pragma omp section
            blurring("sample_blur_sections_gris2.bmp", 5);
        #pragma omp section
            blurring("sample_blur_sections_gris3.bmp", 7);
        #pragma omp section
            blurring("sample_blur_sections_gris4.bmp", 9);
        #pragma omp section
            blurring("sample_blur_sections_gris5.bmp", 11);
        #pragma omp section
            blurring("sample_blur_sections_gris6.bmp", 13);
        #pragma omp section
            blurring("sample_blur_sections_gris7.bmp", 15);
        #pragma omp section
            blurring("sample_blur_sections_gris8.bmp", 17);
        #pragma omp section
            blurring("sample_blur_sections_gris9.bmp", 19);
        #pragma omp section
            blurring_inv("sample_blur_sections_gris10.bmp", 21);
        #pragma omp section
            blurring_inv("sample_blur_sections_gris11.bmp", 19);   
        #pragma omp section
            blurring_inv("sample_blur_sections_gris12.bmp", 17);
        #pragma omp section
            blurring_inv("sample_blur_sections_gris13.bmp", 15);
        #pragma omp section
            blurring_inv("sample_blur_sections_gris14.bmp", 13);
        #pragma omp section
            blurring_inv("sample_blur_sections_gris15.bmp", 11);
        #pragma omp section
            blurring_inv("sample_blur_sections_gris16.bmp", 9);
        #pragma omp section
            blurring_inv("sample_blur_sections_gris17.bmp", 7);
        #pragma omp section
            blurring_inv("sample_blur_sections_gris18.bmp", 5);  
        #pragma omp section
            blurring_inv("sample_blur_sections_gris19.bmp", 3);
        }
    }
  return 0;
}

void blurring(char outputImageName[], int sizeM){
	// Declare pointers for image & new image
	FILE *image, *outputImage, *lecturas;
	
	// Open original image
	image = fopen("5.bmp","rb");                 //Imagen original a transformar
	// Create new image
	outputImage = fopen(outputImageName,"wb");      //Imagen transformada
	
	// Declare width & height of the image
	long ancho;
	long alto;

	// Declare RGB pixel chars
	unsigned char r, g, b;    //Pixel
	unsigned char* ptr;
	// Array for the first 54 header's line
	unsigned char xx[54];

	// Define variables
	long cuenta = 0, anchoR = 0, altoR = 0, anchoM = 0, altoM = 0;
	long sum;
	int iR, jR;

	// Read first 54 header's line and move img memory counter
	for(int i = 0; i < 54; i++) {
		xx[i] = fgetc(image);
		fputc(xx[i], outputImage);      //Copia cabecera a nueva imagen
	}

	// Calculate the width & height of the original image
	ancho = (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
	alto = (long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
	
	// Print width & height
	// printf("alto img %li\n",alto);
	// printf("ancho img %li\n",ancho);
	// printf("total %li\n",ancho*alto*3);

	// Asign pointers of malloc
	ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));
	
	// Set num of threads
	omp_set_num_threads(NUM_THREADS);

	// Define photo bidimensional matrices	
	unsigned char foto[alto][ancho], fotoB[alto][ancho];
	
	// Declase pixel
	unsigned char pixel;
	
	// Convert original img to gray scale
	for(int i = 0; i < alto; i++){
		// Get RGB values as received: B, G, R
		for(int j = 0; j < ancho; j++){
			b = fgetc(image);
			g = fgetc(image);
			r = fgetc(image);

			// Create new pixel in gray scale
			pixel = 0.21*r + 0.72*g + 0.07*b;
			
			// Build bidimensional matrix with pixel triad
			foto[i][j] = pixel;
			fotoB[i][j] = pixel;
		}
	}

	// Calculate widths and heights
	anchoR = ancho/sizeM;
	altoR = alto/sizeM;
	anchoM = ancho%sizeM;
	altoM = alto%sizeM;

	// Declare image X and Y starts, ends and sides
	int inicioX,inicioY,cierreX,cierreY,ladoX,ladoY;
	// Image representation
	for(int i = 0; i < alto; i++){
		//iR = i * sizeM;
		for(int j = 0; j < ancho; j++){
			//jR=j*sizeM;
			if(i < sizeM){
				inicioX = 0;
				cierreX = i+sizeM;
				ladoX = i+sizeM;
			} else if(i >= alto-sizeM){
				inicioX = i-sizeM;
				cierreX = alto;
				ladoX = alto-i+sizeM;
			}else{
				inicioX = i-sizeM;
				cierreX = i+sizeM;
				ladoX = sizeM*2+1;
			}
		
			if(j < sizeM){
				inicioY = 0;
				cierreY = j+sizeM;
				ladoY = j+sizeM;
			}else if(j >= ancho-sizeM){
				inicioY = j-sizeM;
				cierreY = ancho;
				ladoY = ancho-j+sizeM;
			}else{
				inicioY = j-sizeM;
				cierreY = j+sizeM;
				ladoY = sizeM*2+1;
			}
			
			sum = 0;
			
			// Built bidimensional matrix
			for(int x = inicioX; x < cierreX; x++){
				for(int y = inicioY; y < cierreY; y++){
					sum += foto[x][y];
				}
			}

			// Calculate blurring sum
			sum = sum/(ladoX*ladoY);

			// Asign bidimensional matrix blurring sum
			fotoB[i][j] = sum;
		}
	}
	
	// Reset counter
	cuenta = 0;
	// Image asignation
	for(int i = 0; i < alto; i++){
		// Normal
		for(int j = 0; j < ancho; j++){
			ptr[cuenta] = fotoB[i][j]; //b
			ptr[cuenta+1] = fotoB[i][j]; //g
			ptr[cuenta+2] = fotoB[i][j]; //r
			cuenta++;
		}
	}       

	// Measure initial time (startTime)
	const double startTime = omp_get_wtime();

	// Gray scale
	#pragma omp parallel
	{
		#pragma omp for schedule(dynamic)
			for (int i = 0; i < alto*ancho; ++i) {
				fputc(ptr[i], outputImage);
				fputc(ptr[i+1], outputImage);
				fputc(ptr[i+2], outputImage);
			}
	}

	// Measure final time (endTime)
	const double endTime = omp_get_wtime();

	// Print image name
	printf("\nNormal\n");
	// Print number of threads
    printf("Threads: %d\n", NUM_THREADS);
	// Print how much time did it take
	printf("Tiempo = %f\n", endTime-startTime);
	
	// Free memory
	free(ptr);
	
	// Close original image
	fclose(image);

	// Close new image
	fclose(outputImage);
}

void blurring_inv(char outputImgName[], int sizeM){
	// Declare pointers for image & new image
	FILE *image, *outputImage, *lecturas;

	// Open original image
	image = fopen("5.bmp","rb");
	// Create new image
	outputImage = fopen(outputImgName,"wb");

	// Declare width & height of the image
	long width;
	long height;

	// Declare RGB pixel chars
	unsigned char r, g, b;
	unsigned char* ptr;

	// Array for the first 54 header's line
	unsigned char xx[54];

	// Define variables
	long counter = 0, widthR = 0, heightR = 0, widthM = 0, heightM = 0;
	long sum;
	int iR, jR;

    // Read first 54 header's line and move img memory counter
    for (int i = 0; i < 54; i++) {
        // Get header line from original img
        xx[i] = fgetc(image);
        // Set header line to new img
        fputc(xx[i], outputImage);
    }

    // Calculate the width & height of the original image
	width = (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
	height = (long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];

    // Print width & height
	// printf("alto img %li\n",width);
  	// printf("ancho img %li\n",height);
  	// printf("total %li\n",height*width*3);

	// Asign pointers of malloc
	ptr = (unsigned char*)malloc(height*width*3* sizeof(unsigned char));

	// Set num of threads
	omp_set_num_threads(NUM_THREADS);

	// Define photo bidimensional matrices
	unsigned char photo[height][width], photoB[height][width];

	// Declase pixel
	unsigned char pixel;

	// Convert original img to gray scale
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			// Get RGB values as received: B, G, R
			b = fgetc(image);
			g = fgetc(image);
			r = fgetc(image);

			// Create new pixel in gray scale
			pixel = 0.21*r + 0.72*g + 0.07*b;

			// Build bidimensional matrix with pixel triad
			photo[i][j] = pixel;
			photoB[i][j] = pixel;
		}
	}

	// Calculate widths and heights
	widthR = width / sizeM;
	heightR = height / sizeM;
	widthM = width % sizeM;
	heightM = height % sizeM;

	// Declare image X and Y starts, ends and sides
	int startX, startY, endX, endY, sideX, sideY;

	// Image representation
	for(int i = 0; i < height; i++) {
		// iR = i * sizeM;
		for(int j = 0; j < width; j++) {
			// jR = j * sizeM;
			if (i < sizeM) {
				startX = height;
				endX = 0;
				sideX = i+sizeM;
			} else if (i >= height-sizeM) {
				startX = i+sizeM;
				endX = 0;
				sideX = height-i+sizeM;
			} else {
				startX = i-sizeM;
				endX = i+sizeM;
				sideX = sizeM*2+1;
			}

			if (j < sizeM) {
				startY = width;
				endY = j+sizeM;
				sideY = j+sizeM;
			} else if (j >= width-sizeM) {
				startY = j-sizeM;
				endY = width;
				sideY = width-j+sizeM;
			} else {
				startY = j-sizeM;
				endY = j+sizeM;
				sideY = sizeM*2+1;
			}

			sum = 0;

			// Built bidimensional matrix
			for (int x = startX; x < endX; x++) {
				for (int y = startY; y < endY; y++) {
					sum += photo[x][y];
				}
			}

			// Calculate blurring sum
			sum = sum / (sideX*sideY);

			// Asign bidimensional matrix blurring sum
			photoB[i][j] = sum;
		}
	}

	// Reset counter
	counter = 0;

	// Image asignation
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// Inverted
			ptr[counter] = photoB[i][width-j]; // Blue
			ptr[counter+1] = photoB[i][width-j]; // Green
			ptr[counter+2] = photoB[i][width-j]; // Red
			counter++;
		}
	}       

	// Measure initial time (t1)
	const double t1 = omp_get_wtime();

	// Gray scale
	#pragma omp parallel
	{
		#pragma omp for schedule(dynamic)
			for (int i = 0; i < height*width; ++i) {
				fputc(ptr[i], outputImage);
				fputc(ptr[i+1], outputImage);
				fputc(ptr[i+2], outputImage);
			}
	}

	// Measure final time (t2)
	const double t2 = omp_get_wtime();

	// Print image name
	printf("\nInvertida\n");
	// Print number of threads
    printf("Threads: %d\n", NUM_THREADS);
    // Print how much time did it take
    printf("Tiempo = %f\n", t2-t1);

	// Free memory
	free(ptr);

	// Close original image
	fclose(image);

	// Close new image
	fclose(outputImage);
}