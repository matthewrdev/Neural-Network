//****************************************************************************
//**
//**    tga.h
//**
//**    Copyright (c) 2002 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 12/09/2002
//**
//****************************************************************************
#include <GF1_Types.h>


   namespace GF1
   {

      // pack structure to 1 byte
#pragma pack(1)

      struct TgaHeader
      {
         fbyte idLength;            // 00h   Size of Image ID field
         fbyte colourMapType;       // 01h   Colour Map Type
         fbyte imageType;           // 02h   Image type code
         fword cmapStart;           // 03h   Colour map origin
         fword cmapLength;          // 05h   Colour map length
         fbyte cmapDepth;           // 07h   Depth of colour map entries
         fword xOffset;             // 08h   X origin of image
         fword yOffset;             // 0Ah   Y origin of image
         fword width;               // 0Ch   Width of image
         fword height;              // 0Eh   Height of image
         fbyte pixelDepth;          // 10h   Image pixel size
         fbyte imageDescriptor;     // 11h   Image descriptor byte
      };

      // restore structure packing
#pragma pack()



      enum TgaImageData
      {
         IMAGE_DATA_NONE                = 0,
         IMAGE_DATA_COLOURMAPPED        = 1,
         IMAGE_DATA_TRUECOLOUR          = 2,
         IMAGE_DATA_MONOCHROME          = 3,
         IMAGE_DATA_COLOURMAPPED_ENC    = 9,
         IMAGE_DATA_TRUECOLOUR_ENC      = 10,
         IMAGE_DATA_MONOCHROME_ENC      = 11
      };

      enum TgaImageOrgin
      {
         IMAGE_ORIGIN_BOTTOM_LEFT,
         IMAGE_ORIGIN_TOP_LEFT
      };


      class TgaLoader
      {
      public:
         TgaLoader(const char *filename);

         ~TgaLoader();

         bool LoadHeader();
            // loads the tga header

         bool LoadImageData(
            fbyte *imageData, 
            fdword size, 
            fdword width,
            fdword height,
            fdword bpp,
            TgaImageOrgin origin);
            // loads the tga image data
            // image data is a client supplied array to hold the image data
            // size is the size in bytes of the image data
            // bpp is the number of bits per pixel

         fdword GetHeight() const;
            // obtain the height of the image
            // returns 0 if header data not loaded

         fdword GetWidth() const;
            // obtain the width of the image
            // returns 0 if header data not loaded

         fdword GetBpp() const;
            // obtain the bits per pixel of the image
            // returns 0 if header data not loaded

         TgaImageOrgin GetImageOrigin() const;
            // Determine the origin of the image
            // Most tga origin's are the bottom left

         fdword GetImageDataSize() const;
            // obtain the size in bytes of the image data
            // returns 0 if header data not loaded

      private:
         bool IsTgaHeaderValid() const;
         // returns false if not supported or invalid data

         const char *m_filename;
         TgaHeader m_header;
         bool m_headerLoaded;
      };


   }  // end namespace GF1




//****************************************************************************
//**
//**   END INTERFACE
//**
//****************************************************************************
