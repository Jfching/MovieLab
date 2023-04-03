
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

MOVIE *movie = NULL;

int main(int argc, char *argv[])
{
        int x = 0;
        char *fin = NULL;
        char *fout = NULL;
        int frameNum;
        int *start = NULL;
        int *end = NULL;
        int *factor;


        unsigned int width = 512;
        unsigned int height = 288;

        /* the while loop to check options in the command line */
        while (x < argc) {
                /* the input file name */
                if (strcmp(argv[x], "-i") == 0) {
                        if (x < argc - 1) {
                                fin = argv[x + 1];
                        } /*fi*/
                        else {
                                printf("Missing argument for the input file name!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                /* the output file name */
                if (strcmp(argv[x], "-o") == 0) {
                        if (x < argc - 1) {
                                fout = argv[x + 1];
                        } /*fi*/
                        else {
                                printf("Missing argument for the output file name!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                movie = LoadMovie(fin, frameNum, width, height);

                /* the help option */
                if (strcmp(argv[x], "-h") == 0) {
                        PrintUsage();
                        return 0;
                } /*fi*/

                if(strcmp(argv[x], "-f") == 0)
                {
                        if(x < argc - 1)
                        {
                                if(sscanf(argv[x + 1], "%d", &frameNum) != 1)
                                {
                                        printf("Input does not match");
                                        return 5;
                                }
                        }

                        else
                        {
                                printf("Missing argument");
                                return 5;
                        }

                        x += 2;
                        continue;
                }

                if(strcmp(argv[x], "-s") == 0)
                {
                        if(x < argc - 1)
                        {
                                sscanf(argv[x + 1], "%ux%u", &width, &height);
                        }
                        else
                        {
                                printf("Missing argument");
                                return 5;
                        }

                        x += 2;
                        continue;
                }

                if(strcmp(argv[x], "-aging") == 0)
                {
                        int i;

                        IENTRY *e;

                        e = movie->Frames->First;

                        while(e != NULL)
                        {
                                Aging(e->YUVImage);
                                e = e->Next;
                                i++;
                        }

                        x ++;
                        continue;
                }

                if(strcmp(argv[x], "-hflip") == 0)
                {
                        int i = 0;

                        IENTRY *e;

                        e = movie->Frames->First;

                        while(e != NULL)
                        {
                                HFlip(e->YUVImage);
                                e = e->Next;
                                i++;
                        }

                        x += 1;
                        continue;
                }

                if(strcmp(argv[x], "-edge") == 0)
                {
                        int i = 0;

                        IENTRY *e;

                        e = movie->Frames->First;

                        while(e != NULL)
                        {
                                Edge(e->YUVImage);
                                e = e->Next;
                                i++;
                        }

                        x += 1;
                        continue;
                }


                if(strcmp(argv[x], "-crop") == 0)
                {

                        if(x < argc - 1)
                        {
                                CropImageList(movie->Frames, &start, &end);
                        }
                        else
                        {
                                printf("Missing argument");
                                return 5;
                        }

                        x += 2;
                        continue;
                }

                if(strcmp(argv[x], "-fast") == 0)
                {

                        if(x < argc - 1)
                        {
                                sscanf(argv[x + 1], "%d", &factor);
                                FastImageList(movie->Frames, &factor);

                        }

                        else
                        {
                                        printf("Missing argument");
                                        return 5;
                        }
                        x += 2;
                        continue;
                }

                if(strcmp(argv[x], "-reverse") == 0)
                {
                        ReverseImageList(movie->Frames);
                        x++;
                        continue;
                }

                if(strcmp(argv[x], "-watermark") == 0)
                {
                        /*if(x < argc - 1)
                        {
                                MOVIE *movie;
                                IMAGE *image;

                                srand(time());
                                int x = rand()% width;
                                int y = rand()% height;

                        }*/

                        movie = LoadMovie(fin, frameNum, width, height);

                }

                if(strcmp(argv[x], "-spotlight") == 0)
                {
                        printf("Feature not implemented");
                }
                x++;

        } /*elihw*/

        if (fin == NULL) {
                printf("Missing argument for the input file name!\n");
                PrintUsage();
                return 5;
        }

        if (fout == NULL) {
                printf("Missing argument for the output file name!\n");
                PrintUsage();
                return 5;
        }

        /* to be implemented */

        SaveMovie(fout,movie);

        fin = NULL;
        fout = NULL;

        return 0;

}

void PrintUsage()
{
        printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
               "Options:\n"
               "-aging                Activate the aging filter on every movie frame\n"
               "-hflip                Activate horizontal flip on every movie frame\n"
               "-edge                 Activate the edge filter on every movie frame\n"
               "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
               "-fast <factor>        Fast forward the movie by <factor>\n"
               "-reverse              Reverse the frame order of the input movie\n"
               "-watermark <file>     Add a watermark from <file> to every movie frame\n"
               "-spotlight            Spotlight the fade in and fade out\n"
               "-zoom                 Zoom in and out the input movie\n"
               "-h                    Display this usage information\n"
              );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
        FILE *file;
        unsigned int x, y;
        unsigned char c;
        YUVIMAGE* YUVimage;

        /* Check errors */
        assert(fname);
        assert(n >= 0);

        YUVimage = CreateYUVImage(width, height);
        if (YUVimage == NULL) {
                return NULL;
        }

        /* Open the input file */
        file = fopen(fname, "r");
        if (file == NULL) {
                DeleteYUVImage(YUVimage);
                return NULL;
        }

        /* Find the desired frame */
        fseek(file, 1.5 * n * width * height, SEEK_SET);

        for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                        c = fgetc(file);
                        SetPixelY(YUVimage, x, y, c);
                } /*rof*/
        }

        for (y = 0; y < height; y += 2) {
                for (x = 0; x < width; x += 2) {
                        c = fgetc(file);
                        SetPixelU(YUVimage, x, y, c);
                        SetPixelU(YUVimage, x + 1, y, c);
                        SetPixelU(YUVimage, x, y + 1, c);
                        SetPixelU(YUVimage, x + 1, y + 1, c);
                }
        }

        for (y = 0; y < height; y += 2) {
                for (x = 0; x < width; x += 2) {
                        c = fgetc(file);
                        SetPixelV(YUVimage, x, y, c);
                        SetPixelV(YUVimage, x + 1, y, c);
                        SetPixelV(YUVimage, x, y + 1, c);
                        SetPixelV(YUVimage, x + 1, y + 1, c);
                }
        }

        /* Check errors */
        assert(ferror(file) == 0);

        /* Close the input file and return */
        fclose(file);
        file = NULL;
        return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
        int i;

        MOVIE *movie = CreateMovie();

        for(i = 0; i < frameNum; i++)
        {
                AppendYUVImage(movie->Frames, LoadOneFrame(fname, i, width, height));
        }

        return movie;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
        FILE *file = fopen(fname, "w");
        assert(file != NULL);
        IENTRY *node;
        node = movie->Frames->First;
                 while (node)
                 {
                        SaveOneFrame(node->YUVImage, fname, file);
                        node = node->Next;
                 }
        fclose(file);
        file = NULL;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
        int x, y;
        for (y = 0; y < image->H; y++) {
                for (x = 0; x < image->W; x++) {
                        fputc(GetPixelY(image, x, y), file);
                }
        }

        for (y = 0; y < image->H; y += 2) {
                for (x = 0; x < image->W; x += 2) {
                        fputc(GetPixelU(image, x, y), file);
                }
        }

        for (y = 0; y < image->H; y += 2) {
                for (x = 0; x < image->W; x += 2) {
                        fputc(GetPixelV(image, x, y), file);
                }
        }
}
