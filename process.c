#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* The RGB values of a pixel. */
struct Pixel {
    unsigned int red, green, blue;
};

//An image loaded from a file.
struct Image {
    /* TODO: Question 1 */
    int width, height; //The integer height and the width of the image from the header
    struct Pixel* pix; //Pointer "pix" dynamically allocates pixel array
};

//Free a struct Image
void free_image(struct Image *img)  
{
    /* TODO: Question 2a */
    if(img != NULL){  //image pointer null or no
        if(img -> pix != NULL){  //pixel data pointer null or no
            free(img -> pix);  //free the memory which is allocated for image structure
        }
    free(img);  //free memory which is allocated for image structure
    }
}

/* Opens and reads an image file, returning a pointer to a new struct Image.
 * On error, prints an error message and returns NULL. */
struct Image *load_image(const char *filename)
{
    /* Open the file for reading */
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "File %s could not be opened.\n", filename);  //error message if file cannot be opened
        return NULL; 
    }

    /* Allocate the Image object, and read the image from the file */
    /* TODO: Question 2b */
    struct Image *img = malloc(sizeof(struct Image));  //allocates memory for an image
    if (img == NULL)  //check if memory allocation has failed
    {
            printf("Memory allocation has failed.\n"); //error message if memory allocation fails
            fclose(f);
        return NULL;    
    }

    //Reading the image header
    int width, height;  //variables
    if (fscanf(f, "HSHEX %d %d\n", &width, &height) != 2 ){  //read the width and height from file header
        printf("Error while reading the image dimensions from %s.\n", filename);  
        free(img);
        //If fails to read width and height 
        //it prints an error message
        //free memory which is allocated for image

        fclose(f);
        return NULL;
        
    }

    //Allocating memory for the pixels
    img->width = width, img->height = height;  //setting width and height of image
    img->pix = (struct Pixel *)malloc(width * height * sizeof(struct Pixel)); //allocate memory for pixel data
    if (img->pix == NULL) {
        fprintf(stderr, "Memory allocation has failed.\n");  
        fclose(f);
        free(img);
        //If allocation fails, it prints an error message
        //closes the file 
        //free the memory allocated for the image

        return NULL;
    }

    //Reading the pixel data
    for (int i = 0; i < img->width * img->height; ++i) { //loop
        if (fscanf(f, "%hhx %hhx %hhx", &img->pix[i].red, &img->pix[i].green, &img->pix[i].blue) != 3) {  //reads pixel data from file
            fprintf(stderr, "Error while reading pixel data.\n");  //error message
            free_image(img);
            fclose(f);
            //If fails to read values for any pixel
            //prints an error message
            //free the memory which is allocated for the image
            //closes the file

            return NULL;
        }
    }

    //Closing the file
    fclose(f);
    return img;
}

/* Write img to file filename. Return true on success, false on error. */
bool save_image(const struct Image *img, const char *filename) 
{
    FILE *f = fopen(filename, "w");  //trying to open file
    if (f == NULL){
        printf("Error: Unable to open file %s for writing.\n", filename);  //error image printed if file couldn't be opened
        return false;
    }
    
    //Writes image header to the file
    if (fprintf(f, "HSHEX %d %d ", img->width, img->height) < 0) { //writes image width and height
        printf("Error: Failed to write header\n");  //error message if writing the header fails
        fclose(f);
        return false;
    }

    //Writes RGB values/pixel data to file
    for (int i = 0; i < img->width * img->height; ++i) {  //loop on each pixels
        //Writing the Red, Green and Blue components of each pixel
        if (fprintf(f, "%02hhx%02hhx ", img->pix[i].red, img->pix[i].red) < 0 ||
            fprintf(f, "%02hhx%02hhx ", img->pix[i].green, img->pix[i].green) < 0 ||
            fprintf(f, "%02hhx%02hhx ", img->pix[i].blue, img->pix[i].blue) < 0) {
            fprintf(stderr, "File %s couldn't be written.\n", filename);  //error message if it fails
            fclose(f);
            return false;
        }
    }

    // Close the file
    fclose(f);
    return true;
}

/* Allocate a new struct Image and copy an existing struct Image's contents
 * into it. On error, returns NULL. */
struct Image *copy_image(const struct Image *source)
{
    /* TODO: Question 2d */
    if (source == NULL) {
        return NULL;  // Return NULL for invalid input
    }

    //Allocating memory for the new image structure
    struct Image *copy = malloc(sizeof(struct Image));
    if (copy == NULL) {
        printf("Error: Memory allocation failed.\n");  //error image
        return NULL;
    }

    //Copy header information
    copy->width = source->width, copy->height = source->height;  //copying the width and height from the source image

    //Allocating memory for pixel/RGB data //
    copy->pix = malloc(sizeof(struct Pixel) * source->width * source->height);
    if (copy->pix == NULL) {
        printf("Error: Memory allocation failed.\n");  //error image
        free(copy);
        return NULL;
    }

    // Copy pixel data
    for (int i = 0; i < source->width * source->height; ++i) {  //loop on each pixel1
        copy->pix[i] = source->pix[i];  //copying the pixel/RGB data from source to "copy"
    }

    return copy;
}

/* Perform your first task.
 * (TODO: Write a better comment here, and rename the function.
 * You may need to add or change arguments depending on the task.)
 * Returns a new struct Image containing the result, or NULL on error. */
struct Image *apply_MONO(const struct Image *source)
{
   //checking if input image is valid or no
    if (source == NULL || source->pix == NULL){
        fprintf(stderr, "Invalid input image.\n");
        return NULL;
    }

    //create a duplicate of the actual image using the function copy_image function
    struct Image *output = copy_image(source);
    if (output == NULL){
        fprintf(stderr, "Error creating a copy of the original image.\n");  //error message if it doesn't work
        return NULL;
    }

    //converting each pixel to greyscale (mono effect)
    for (int i = 0; i < source->width * source->height; i++){
        //Calculate weighted sum to convert to greyscale
        double grey_value = 0.299 * output->pix[i].red + 0.587 * output->pix[i].green + 0.114 * output->pix[i].blue;
        
        //simply sets the red, blue and green component of pixel to grey scale
        output->pix[i].red = (unsigned int)grey_value, 
        output->pix[i].green = (unsigned int)grey_value, 
        output->pix[i].blue = (unsigned int)grey_value;
    }

    return output; 
}

/* Perform your second task.
 * (TODO: Write a better comment here, and rename the function.
 * You may need to add or change arguments depending on the task.)
 * Returns true on success, or false on error. 
 */
bool apply_HIST(const struct Image *source)
{
    if (source == NULL) {
        printf("The source image is NULL.\n");
        return false;
        //checks if source image is null or no 
        //It will print error message if failed
    }


    int hist[256] = {0};  
    //storing histogram values in an array
    //initalized to 0

    for (int i = 0; i < source->width * source->height; i++) {
        hist[source->pix[i].red]++, hist[source->pix[i].green]++, hist[source->pix[i].blue]++;
        //increases the values of the RGB histograms for every pixel.
    }

    for (int i = 0; i < 256; i++) {
        if (hist[i] > 0)  //for non zero values
        {  
            printf("Value %d: %d pixels\n", i, hist[i]);
            //printing format for the histogram values in console
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    /* Initialise the random number generator, using the time as the seed */
    /* TODO: Remove this if you don't need to use rand() */
    srand(time(NULL));

    /* Check command-line arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: process INPUTFILE OUTPUTFILE\n");
        return 1;
    }

    /* Load the input image */
    struct Image *in_img = load_image(argv[1]);
    if (in_img == NULL) {
        return 1;
    }
    printf("Load function is working.\n");  //successfully working message                                        

    /* Apply the first process */
    struct Image *out_img = apply_MONO(in_img);
    if (out_img == NULL) {
        fprintf(stderr, "First process failed.\n");
        free_image(in_img);
        return 1;     
    }

    /* Apply the second process */
    if (!apply_HIST(out_img)) {
        fprintf(stderr, "Second process failed.\n");
        free_image(in_img);
        free_image(out_img);
        return 1;
    }

    /* Save the output image */
    if (!save_image(out_img, argv[2])) {
        fprintf(stderr, "Saving image to %s failed.\n", argv[2]);
        free_image(in_img);
        free_image(out_img);
        return 1;
    }
    printf("Save function is working.\n");  //successfully working message

    free_image(in_img);
    free_image(out_img);
    return 0;
}
