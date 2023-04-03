#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"

/* Aging */
IMAGE *Aging(IMAGE *image)
{
        unsigned int x, y;

        assert(image);

        for (x = 0; x < image->W; x++) {
                for (y = 0; y < image->H; y++) {
                        SetPixelB(image, x, y, (GetPixelR(image, x, y) +
                                                GetPixelG(image, x, y) +
                                                GetPixelB(image, x, y)) / 5);
                        SetPixelR(image, x, y, GetPixelB(image, x, y) * 1.6);
                        SetPixelG(image, x, y, GetPixelB(image, x, y) * 1.6);
                }
        }

        return image;
}

/* Horizontal flip */
IMAGE *HFlip(IMAGE *image)
{
        unsigned int x, y;
        unsigned char R, G, B;
        unsigned int width, height;

        assert(image);

        width = image->W;
        height = image->H;

        for (x = 0; x < width / 2; x++) {
                for (y = 0; y < height; y++) {
                        R = GetPixelR(image, width - 1 - x, y);
                        G = GetPixelG(image, width - 1 - x, y);
                        B = GetPixelB(image, width - 1 - x, y);

                        SetPixelR(image, width - 1 - x, y, GetPixelR(image, x, y));
                        SetPixelG(image, width - 1 - x, y, GetPixelG(image, x, y));
                        SetPixelB(image, width - 1 - x, y, GetPixelB(image, x, y));

                        SetPixelR(image, x, y, R);
                        SetPixelG(image, x, y, G);
                        SetPixelB(image, x, y, B);
                }
        }

        return image;
}

/* Edge detection */
IMAGE *Edge(IMAGE *image)
{
        unsigned int x, y;
        int i, j;
        int tmpR = 0;
        int tmpG = 0;
        int tmpB = 0;
        unsigned int width, height;

        assert(image);

        width = image->W;
        height = image->H;

        IMAGE *tmpImage = CreateImage(width, height);

        for (x = 0; x < width; x++) {
                for (y = 0; y < height; y++) {
                        SetPixelR(tmpImage, x, y, GetPixelR(image, x, y));
                        SetPixelG(tmpImage, x, y, GetPixelG(image, x, y));
                        SetPixelB(tmpImage, x, y, GetPixelB(image, x, y));
                }
        }

        for (x = 1; x < width - 1; x++) {
                for (y = 1; y < height - 1; y++) {
                        tmpR = 0;
                        tmpG = 0;
                        tmpB = 0;

                        for (i = -1; i <= 1; i++) {
                                for (j = -1; j <= 1; j++) {
                                        tmpR += GetPixelR(tmpImage, x, y) -
                                                GetPixelR(tmpImage, x + i, y + j);
                                        tmpG += GetPixelG(tmpImage, x, y) -
                                                GetPixelG(tmpImage, x + i, y + j);
                                        tmpB += GetPixelB(tmpImage, x, y) -
                                                GetPixelB(tmpImage, x + i, y + j);
                                }
                        }

                        SetPixelR(image, x, y, tmpR > 255 ? 255 : (tmpR < 0 ? 0 : tmpR));
                        SetPixelG(image, x, y, tmpG > 255 ? 255 : (tmpG < 0 ? 0 : tmpG));
                        SetPixelB(image, x, y, tmpB > 255 ? 255 : (tmpB < 0 ? 0 : tmpB));
                }
        }

        for (x = 0; x < width; x++) {
                y = 0;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
                y = height - 1;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
        }

        for (y = 0; y < height; y++) {
                x = 0;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
                x = width - 1;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
        }

        DeleteImage(tmpImage);
        return image;
}

/* Add a watermark to an image */
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark,
                 unsigned int topLeftX, unsigned int topLeftY)
{
        unsigned int x, y;
        unsigned int R, G, B;

        assert(image);
        assert(watermark);

        for (x = 0; x < watermark->W; x++) {
                for (y = 0; y < watermark->H; y++) {
                        if (topLeftX + x < image->W&&
                                topLeftY + y < image->H) {
                                if (GetPixelR(watermark, x, y) == 0 &&
                                        GetPixelG(watermark, x, y) == 0 &&
                                        GetPixelB(watermark, x, y) == 0) {
                                        R = GetPixelR(image, topLeftX + x, topLeftY + y);
                                        G = GetPixelG(image, topLeftX + x, topLeftY + y);
                                        B = GetPixelB(image, topLeftX + x, topLeftY + y);

                                        if (R * WATERMARK_RATIO > 255) {
                                                SetPixelR(image, topLeftX + x, topLeftY + y, 255);
                                        } else {
                                                SetPixelR(image, topLeftX + x, topLeftY + y,
                                                          R * WATERMARK_RATIO);
                                        }

                                        if (G * WATERMARK_RATIO > 255) {
                                                SetPixelG(image, topLeftX + x, topLeftY + y, 255);
                                        } else {
                                                SetPixelG(image, topLeftX + x, topLeftY + y,
                                                          G * WATERMARK_RATIO);
                                        }

                                        if (B * WATERMARK_RATIO > 255) {
                                                SetPixelB(image, topLeftX + x, topLeftY + y, 255);
                                        } else {
                                                SetPixelB(image, topLeftX + x, topLeftY + y,
                                                          B * WATERMARK_RATIO);
                                        }
                                }
                        }
                }
        }

        return image;
}

/* Spotlight */
IMAGE *Spotlight(IMAGE *image, int centerX, int centerY, unsigned int radius)
{
//      printf("Function not implemented");
}

/* Zoom an image */
IMAGE *Zoom(IMAGE *image, unsigned int percentage)
{
        unsigned int x, y;
        unsigned int x1, y1, x2, y2;
        unsigned int i, j;
        unsigned int tmpR, tmpG, tmpB;
        unsigned int width, height;
        unsigned int resWidth, resHeight;
        unsigned int hBorderWidth, vBorderWidth;
        IMAGE *resImage = NULL;

        assert(image);
        assert(percentage <= 100);
        assert(percentage % 2 == 0);

        width = image->W;
        height = image->H;

        if (percentage == 0) {
                for (x = 0; x < width; x++) {
                        for (y = 0; y < height; y++) {
                                SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
                }
        } else {
                resWidth = width * percentage / 100;
                resHeight = height * percentage / 100;

                hBorderWidth = (height - resHeight) / 2;
                vBorderWidth = (width - resWidth) / 2;

                /* Create the resized image */
                resImage = CreateImage(resWidth, resHeight);
                if (resImage == NULL) {
                        return image;
                }

                for (x = 0; x < resWidth; x++) {
                        for (y = 0; y < resHeight; y++) {
                                x1 = x / (percentage / 100.0);
                                y1 = y / (percentage / 100.0);
                                x2 = (x + 1) / (percentage / 100.0);
                                y2 = (y + 1) / (percentage / 100.0);
                                tmpR = 0;
                                tmpG = 0;
                                tmpB = 0;

                                for (i = x1; i < x2; i++) {
                                        for (j = y1; j < y2; j++) {
                                                tmpR += GetPixelR(image, i, j);
                                                tmpG += GetPixelG(image, i, j);
                                                tmpB += GetPixelB(image, i, j);
                                        }
                                }

                                SetPixelR(resImage, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
                                SetPixelG(resImage, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
                                SetPixelB(resImage, x, y, tmpB / ((x2 - x1) * (y2 - y1)));
                        }
                }

                /* Add the top horizontal border */
                for (x = 0; x < width; x++) {
                        for (y = 0; y < hBorderWidth; y++) {
                                SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
                }

                /* Add the left vertical border */
                for (x = 0; x < vBorderWidth; x++) {
                        for (y = hBorderWidth; y < hBorderWidth + resHeight; y++) {
                                SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
                }

                /* Add the resized image */
                for (x = vBorderWidth; x < vBorderWidth + resWidth; x++) {
                        for (y = hBorderWidth; y < hBorderWidth + resHeight; y++) {
                                SetPixelR(image, x, y,
                                          GetPixelR(resImage, x - vBorderWidth, y - hBorderWidth));
                                SetPixelG(image, x, y,
                                          GetPixelG(resImage, x - vBorderWidth, y - hBorderWidth));
                                SetPixelB(image, x, y,
                                          GetPixelB(resImage, x - vBorderWidth, y - hBorderWidth));
                        }
                }

                /* Add the right vertical border */
                for (x = vBorderWidth + resWidth; x < width; x++) {
                        for (y = hBorderWidth; y < hBorderWidth + resHeight; y++) {
                                SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
                }

                /* Add the bottom horizontal border */
                for (x = 0; x < width; x++) {
                        for (y = hBorderWidth + resHeight; y < height; y++) {
                                SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
                }

                DeleteImage(resImage);
        }

        return image;
}
