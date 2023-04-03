
#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
        MOVIE *movie;

        movie = malloc(sizeof(MOVIE));

        movie->Frames = CreateImageList();

        return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
        assert(movie);
        DeleteImageList(movie->Frames);
        movie->Frames;
        free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
        int x, y, C, D, E, w, h;
        int R, G, B;

        IENTRY *currentImage, *nextImage;
        IMAGE *tmpImage;
        ILIST *ImgList = movie->Frames;
        currentImage = ImgList->First;


        while(currentImage)
        {
                for(y = 0; y < h; y++)
                {
                        for(x = 0; x < w; x++)
                        {
                                C = GetPixelY(currentImage->YUVImage, x, y) - 16;
                                D = GetPixelU(currentImage->YUVImage, x, y) - 128;
                                E = GetPixelV(currentImage->YUVImage, x, y) - 128;

                                R = (( 298 * C + 409 * E + 128) >> 8);
                                G = (( 298 * C - 100 * D - 208 * E + 128) >> 8);
                                B = (( 298 * C + 516 * D + 128) >> 8);

                                SetPixelR(tmpImage, x, y, R);
                                SetPixelG(tmpImage, x, y, G);
                                SetPixelB(tmpImage, x, y, B);
                        }
                }

                currentImage->RGBImage = tmpImage;
                currentImage = nextImage;
        }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
        int x, y, R, G, B, w, h;
        int Y, U, V;

        IENTRY *currentImage, *nextImage;
        YUVIMAGE *tmpYUV;
        ILIST *ImgList = movie->Frames;
        currentImage = ImgList->First;

        while(currentImage)
        {
                for(y = 0; y < h; y++)
                {
                        for(x = 0; x < w; x++)
                        {
                                R = GetPixelR(currentImage->RGBImage, x, y);
                                G = GetPixelG(currentImage->RGBImage, x, y);
                                B = GetPixelB(currentImage->RGBImage, x, y);

                                Y = ( ( ( 66 * R + 129 * G + 25 * B + 128) >> 8) + 16 );
                                U = ( ( ( -38 * R - 74 * G + 112 * B + 128) >> 8) + 128 );
                                V = ( ( ( 112 * R - 94 * G - 18 * B + 128) >> 8) + 128 );

                                SetPixelY(tmpYUV, x, y, Y);
                                SetPixelU(tmpYUV, x, y, U);
                                SetPixelV(tmpYUV, x, y, V);
                        }
                }

        currentImage->YUVImage = tmpYUV;
        currentImage = nextImage;

        }
}
