#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image list */
ILIST *CreateImageList(void)
{
        ILIST *list = (ILIST*)malloc(sizeof(ILIST));

        list->Length;
        list->First;
        list->Last;

        return list;

}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
        assert(list);
        assert(list->Length);
        assert(list->First);
        assert(list->Last);

        free(list->Length);
        free(list->First);
        free(list->Last);

        list->Length;
        list->First;
        list->Last;

}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
        IENTRY *i = (IENTRY *)malloc(sizeof(IENTRY));
        i->RGBImage = RGBimage;

        if(list->Last)
         {
                 i->List = list;
                 i->Next = NULL;
                 i->Prev = list->Last;
                 list->Last->Next = i;
                 list->Last = i;
         }

         else
         {
                 i->List = list;
                 i->Next = NULL;
                 i->Prev = NULL;
                 list->First = i;
                 list->Last = i;
         }
                 list->Length++;

}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
        IENTRY *i = (IENTRY *)malloc(sizeof(IENTRY));
        i->YUVImage = YUVimage;

        if(list->Last)
        {
                i->List = list;
                i->Next = NULL;
                i->Prev = list->Last;
                list->Last->Next = i;
                list->Last = i;
        }

        else
        {
                i->List = list;
                i->Next = NULL;
                i->Prev = NULL;
                list->First = i;
                list->Last = i;
        }

        list->Length++;

}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
/*      void CropImageList(ILIST *list, unsigned int start, unsigned int end)
        {

    IENTRY *current = (IENTRY *)malloc(sizeof(IENTRY));
    IENTRY *temp = (IENTRY *)malloc(sizeof(IENTRY));
    IENTRY *tempEnd = (IENTRY *)malloc(sizeof(IENTRY));


    current = list->First;

        for (int i = 0; i < start; i++)
         {

             temp = current->Next;
             DeleteIENTRY(current);
             current = temp;
         }

    list->First = temp;
    temp = NULL;
    current = list->First;

                for (int i = 0; i < end; i++)
                {

                }

                    for (int i = list->Length - end + 1; i < list->Length; i++)
                         {

                                temp = current->Next;
                                 DeleteIENTRY(current);
                                  current = temp;
                         }

    temp = current = NULL;
         }       */
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
/*
        int i;

        IENTRY *p;
        IENTRY *n;

        p = list->First;
        n = list->First->Next;

        for(i = 1; i < factor; i++)
        {

        }

        list->First...

        while(n)
        {

        }

        list->First->Next = n;
        list->First->Prev = n;  */
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
        IENTRY *p;
        IENTRY *n;

        p = NULL;
        n = list->First->Next;

        while (n)
        {
                list->First->Next = p;

                list->First->Prev = n;

                p = list->First;

                list->First = n;

                n = n->Next;

                list->First->Next = p;

                list->First->Prev = n;
        }

        list->Last = list->First;
}
