//****************************************************************************
//**
//**    GF1_Tga.cpp
//**
//**    Copyright (c) 2003 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 12/09/2002
//**
//****************************************************************************
#include "GF1_stdafx.h"
#include "GF1_Tga.h"


   namespace GF1
   {

      TgaLoader::TgaLoader(const char *filename)
      {
         assert(filename != NULL);

         m_filename = filename;
         memset(&m_header, '\0', sizeof(TgaHeader));
         m_headerLoaded = false;
      }


      TgaLoader::~TgaLoader()
      {
      }


      bool TgaLoader::IsTgaHeaderValid() const
      {
         if (!m_headerLoaded)
         {
            return false;
         }

         if (m_header.idLength > 0)
         {
            // id length > 0 not supported
            return false;
         }

         if (m_header.colourMapType != 0)
         {
            // tga colour maps (palettes) not supported
            return false;
         }

         if (m_header.imageType != IMAGE_DATA_TRUECOLOUR)
         {
            // only truecolour supported
            return false;
         }

         if (m_header.cmapStart  != 0 ||
            m_header.cmapLength != 0 ||
            m_header.cmapDepth  != 0)
         {
            // colour map not supported
            return false;
         }

         if (m_header.xOffset != 0 ||
            m_header.yOffset != 0)
         {
            // non-zero offsets not supported
            return false;
         }


         if (GetWidth() <= 0 || GetHeight() <= 0)
         {
            // invalid width & height
            return false;
         }

         if (GetBpp() != 24 && GetBpp() != 32)
         {
            // only 24 & 32 bit images supported
            return false;
         }

         return true;
      }


      bool TgaLoader::LoadHeader()
      {
         std::ifstream tgaifs;

         tgaifs.open(m_filename, std::ios::in | std::ios::binary);

         if (!tgaifs.good())
         {
            return false;
         }

         tgaifs.read((char *)&m_header, sizeof(TgaHeader));

         if (!tgaifs.good())
         {
            tgaifs.close();
            return false;
         }

         // need to set this to true before validation as it uses functions that
         // check for whtether it is loaded or not
         m_headerLoaded = true;

         if (!IsTgaHeaderValid())
         {
            m_headerLoaded = false;
            tgaifs.close();
            return false;
         }

         tgaifs.close();
         return true;
      }


      bool TgaLoader::LoadImageData(
         fbyte *imageData, 
         fdword size, 
         fdword width,
         fdword height,
         fdword bpp, 
         TgaImageOrgin origin)
      {
         std::ifstream tgaifs(m_filename, std::ios::in | std::ios::binary);

         if (!tgaifs.good())
         {
            return false;
         }

         tgaifs.seekg(sizeof(TgaHeader));

         if (!tgaifs.good())
         {
            tgaifs.close();
            return false;
         }

         tgaifs.read((char *)imageData, size);

         if (!tgaifs.good())
         {
            tgaifs.close();
            return false;
         }

         fdword bytesPerPixel = bpp >> 3;

         // need to swap the red and blue components
         // Loop Through The Image Data
         for (fdword i = 0; i < size; i += bytesPerPixel)
         {
            // Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)

            // Temporarily Store The Value At Image Data 'i'
            fbyte comp = imageData[i];

            // Set The 1st Byte To The Value Of The 3rd Byte
            imageData[i] = imageData[i + 2];		      

            // Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
            imageData[i + 2] = comp;						
         }
#if 1
         if (origin == IMAGE_ORIGIN_BOTTOM_LEFT)
         {
            fdword rowSize = width * bytesPerPixel;
            fbyte *swapRow = new fbyte[rowSize];
            fbyte *loc1, *loc2;

            // need to flip the image vertically
            fdword halfHeight = height / 2;
            for (fdword i = 0; i < halfHeight; i ++)
            {
               loc1 = &(imageData[i * rowSize]);
               loc2 = &(imageData[(height - 1 - i) * rowSize]);

               memcpy(swapRow, loc1, rowSize);
               memcpy(loc1, loc2, rowSize);
               memcpy(loc2, swapRow, rowSize);
            }

            delete [] swapRow;
         }
#endif

         tgaifs.close();
         return true;
      }


      fdword TgaLoader::GetHeight() const
      {
         if (!m_headerLoaded)
         {
            return 0;
         }
         else
         {
            return m_header.height;
         }
      }

      fdword TgaLoader::GetWidth() const
      {
         if (!m_headerLoaded)
         {
            return 0;
         }
         else
         {
            return m_header.width;
         }
      }


      fdword TgaLoader::GetBpp() const
      {
         if (!m_headerLoaded)
         {
            return 0;
         }
         else
         {
            return m_header.pixelDepth;
         }
      }


      TgaImageOrgin TgaLoader::GetImageOrigin() const
      {
         if (!m_headerLoaded)
         {
            return IMAGE_ORIGIN_BOTTOM_LEFT;
         }

         // Bit 5    - screen origin bit.
         //    0 = Origin in lower left-hand corner.
         //    1 = Origin in upper left-hand corner.
         if (m_header.imageDescriptor & (1 << 5))
         {
            return IMAGE_ORIGIN_TOP_LEFT;
         }

         return IMAGE_ORIGIN_BOTTOM_LEFT;
      }


      fdword TgaLoader::GetImageDataSize() const
      {
         fdword bytesPerPixel = GetBpp() >> 3;
         return  bytesPerPixel * GetWidth() * GetHeight();
      }

   }  // end namespace GF1



//****************************************************************************
//**
//**   END IMPLEMENTATION
//**
//****************************************************************************
