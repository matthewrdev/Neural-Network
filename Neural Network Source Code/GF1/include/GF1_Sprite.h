#ifndef GF1_SPRITE_H
#define GF1_SPRITE_H
//****************************************************************************
//**
//**    GF1_Sprite.h
//**
//**    Copyright (c) 2002 QANTM Australia CMC Pty Ltd
//**
//**    Author:  Dale Freya
//**    Created: 12/09/2002
//**
//****************************************************************************
#include <GF1_Def.h>
#include <GF1_Types.h>
#include <GF1_Colour.h>

   namespace GF1
   {
      class Vector3;
      struct SpriteImpl;

      // =====================================================================
      // Sprite
      // =====================================================================
      // The sprite class represents an image or series of images with the 
      // following attributes:
      //    - Position
      //    - Angle
      //    - Scale
      //    - Blend Mode
      //
      // The sprite class facilitates frame based animation.
      //
      // CLASS INVARIANTS
      //    - current frame < frame count
      //    - (texture width / frame width) * (texture height / frame height) 
      //      >= frame count
      // =====================================================================
      class GF1_API Sprite
      {
      public:
         //-------------------------------------------------------------------
         // BlendMode
         //-------------------------------------------------------------------
         // BLEND_MODE_NONE
         //    No blending.
         // BLEND_MODE_TRANSPARENT
         //    This sprite is transparent when displayed over other sprites.  
         //    The amount of transparency is dependant on the values in the 
         //    alpha channel in the texture used for this sprite and the alpha
         //    value in the colour set for each vertex of the sprite
         //    mode: src(src_alpha), dst(1 - src_alpha)
         // BLEND_MODE_ADDITIVE
         //    Combines the whole of the existing image with part of the 
         //    sprite dependant on the alpha channel in the texture used for 
         //    this sprite and the alpha value in the colour set for each 
         //    vertex of the sprite.
         //    mode: src(src_alpha), dst(1)
         // BLEND_MODE_ADDITIVE_COLOUR
         //    Combines the whole of the existing image with part of the 
         //    sprite dependant on the colour values of the sprite.  No
         //    alpha is used.
         //    mode: src(colour), dst(1)
         //-------------------------------------------------------------------
         enum BlendMode
         {
            BLEND_MODE_NONE,
            BLEND_MODE_TRANSPARENT,
            BLEND_MODE_ADDITIVE,
            BLEND_MODE_ADDITIVE_COLOUR
         };

         enum Corner
         {
            CORNER_TOP_LEFT,
            CORNER_TOP_RIGHT,
            CORNER_BOTTOM_LEFT,
            CORNER_BOTTOM_RIGHT
         };


         // ------------------------------------------------------------------
         // Filter
         // ------------------------------------------------------------------
         // The texture mapping filter used to render the texture.
         //
         // NEAREST
         //    The fastest/simplest method which produced blocky results when
         //    scaled however this is the default as it prevents the bleeding 
         //    between sprite frames that can occur with LINEAER filtering.
         //
         // LINEAR
         //    This method samples surronding points in the texture when 
         //    choosing the colour of the destination pixel resulting in a
         //    smoother final image when scaled.
         // ------------------------------------------------------------------
         enum Filter
         {
            FILTER_NEAREST,
            FILTER_LINEAR
         };


         //-------------------------------------------------------------------
         // Constructor
         //-------------------------------------------------------------------
         // texName
         //    Filename/path of the texture.
         // frameWidth
         //    How wide is one frame of animation of the sprite
         // frameHeight
         //    How heigh is one frame of animation of the sprite
         // frameHold
         //    How many logic calls to hold each frame of animation of the 
         //    sprite for when using AutoFrameAdvance().
         // loops
         //    When using AutoFrameAdvance(), does the sprite loop back to 
         //    frame zero when it gets to the end or does it finish on the 
         //    last frame.
         //-------------------------------------------------------------------
         Sprite(
            const char *texName,
            unsigned int frameWidth = 0,
            unsigned int frameHeight = 0,
            unsigned int frameCount = 1,
            unsigned int frameHold = 1,
            bool loops = false);
		 Sprite(){};


         //-------------------------------------------------------------------
         // Copy Constructor
         //-------------------------------------------------------------------
         // rhs
         //    The sprite being copied.
         //-------------------------------------------------------------------
         Sprite(const Sprite &rhs);


         //-------------------------------------------------------------------
         // Destructor
         //-------------------------------------------------------------------
         ~Sprite();


         //-------------------------------------------------------------------
         // Bad
         //-------------------------------------------------------------------
         // Returns true if there was a problem loading the texture for 
         // the sprite
         //-------------------------------------------------------------------
         bool Bad() const;


         //-------------------------------------------------------------------
         // GetPosition
         //-------------------------------------------------------------------
         // Get the world position of the sprite.
         //-------------------------------------------------------------------
         const Vector3 &GetPosition() const;


         //-------------------------------------------------------------------
         // GetAngle
         //-------------------------------------------------------------------
         // Get the angle of the sprite in degrees.
         //-------------------------------------------------------------------
         float GetAngle() const;


         //-------------------------------------------------------------------
         // GetFrameWidth
         //-------------------------------------------------------------------
         // Get the width of one frame of animation of the sprite.
         //-------------------------------------------------------------------
         unsigned int GetFrameWidth() const;


         //-------------------------------------------------------------------
         // GetFrameHeight
         //-------------------------------------------------------------------
         // Get the height of one frame of animation of the sprite.
         //-------------------------------------------------------------------
         unsigned int GetFrameHeight() const;


         //-------------------------------------------------------------------
         // GetFrameHeight
         //-------------------------------------------------------------------
         // Get the number of frames of animation of the sprite.
         //-------------------------------------------------------------------
         unsigned int GetFrameCount() const;


         //-------------------------------------------------------------------
         // GetCurrentFrame
         //-------------------------------------------------------------------
         // Get the index of the current frame of the sprite.
         // The first frame has index 0.
         //-------------------------------------------------------------------
         unsigned int GetCurrentFrame() const;


         //-------------------------------------------------------------------
         // IsAnimationFinished
         //-------------------------------------------------------------------
         // Returns true if the sprite is non looping and AutoFrameAdvance()
         // has advanced to the last frame of the sprite.  
         //-------------------------------------------------------------------
         bool IsAnimationFinished() const;


         //-------------------------------------------------------------------
         // GetBlendMode
         //-------------------------------------------------------------------
         // Returns the current blend mode of the sprite.  The blend mode
         // defaults to NONE for RGB sprites and to TRANSPARENT for RGBA
         // sprites.
         //-------------------------------------------------------------------
         BlendMode GetBlendMode() const;

         //-------------------------------------------------------------------
         // GetTextureName
         //-------------------------------------------------------------------
         // Returns the texture name of the sprite.
         //-------------------------------------------------------------------
		 const char *GetTextureName() const;


         // ------------------------------------------------------------------
         // GetScaleX
         // ------------------------------------------------------------------
         // Get the current X scale factor.
         // ------------------------------------------------------------------
         float GetScaleX() const;


         // ------------------------------------------------------------------
         // GetScaleY
         // ------------------------------------------------------------------
         // Get the current Y scale factor.
         // ------------------------------------------------------------------
         float GetScaleY() const;


         // ------------------------------------------------------------------
         // GetColour
         // ------------------------------------------------------------------
         // Retrieve the colour of one corner of the sprite.
         //
         // corner
         //    Can be CORNER_TOP_LEFT, CORNER_TOP_RIGHT, CORNER_BOTTOM_LEFT or
         //    CORNER_BOTTOM_RIGHT.
         // ------------------------------------------------------------------
         Colour GetColour(Corner corner) const;


         // ------------------------------------------------------------------
         // GetMinificationFilter
         // ------------------------------------------------------------------
         // Obtain the type of texture mapping filter used when the area being
         // texture mapped is smaller than the actual texture.
         // ------------------------------------------------------------------
         Filter GetMinificationFilter() const;


         // ------------------------------------------------------------------
         // GetMagnificationFilter
         // ------------------------------------------------------------------
         // Obtain the type of texture mapping filter used when the area being
         // texture mapped is larger than the actual texture.
         // ------------------------------------------------------------------
         Filter GetMagnificationFilter() const;


         // ------------------------------------------------------------------
         // Assignment Operator
         // ------------------------------------------------------------------
         Sprite &operator=(const Sprite &rhs);


         // ------------------------------------------------------------------
         // Render
         // ------------------------------------------------------------------
         // Call each frame to display the sprite.  Uses the sprites texture, 
         // position and angle.  If your sprite has an alpha channel and you 
         // want it to be masked, OpenGL must be setup in the following state:
         //    glAlphaFunc(GL_GREATER,0.1f);
         //    glEnable(GL_ALPHA_TEST);
         // ------------------------------------------------------------------
         void Render();


         // ------------------------------------------------------------------
         // SetPosition
         // ------------------------------------------------------------------
         // Set the world position of the sprite.
         //
         // pos
         //    The new position of the sprite in world coordinates.
         // ------------------------------------------------------------------
         void SetPosition(const Vector3 &pos);


         // ------------------------------------------------------------------
         // SetAngle
         // ------------------------------------------------------------------
         // Set the angle of the sprite in degrees.
         //
         // angle
         //    The new angle of the sprite in degrees.
         // ------------------------------------------------------------------
         void SetAngle(float angle);


         // ------------------------------------------------------------------
         // SetScale
         // ------------------------------------------------------------------
         // Set the scale of the sprite.
         //
         // scale_x, scale_y
         //    Scale factor. A scale of 2 doubles the sprite size, 0.5 halves
         //    the size, etc.
         // ------------------------------------------------------------------
         void SetScale(float scale_x, float scale_y);


         // ------------------------------------------------------------------
         // AutoFrameAdvance
         // ------------------------------------------------------------------
         // Advances the frames of the sprite causing animation.  Call this every
         // logic if you want to play the sprite as an animation.  Do not call 
         // this function if you want to manually set the current animation frame 
         // of the sprite.  The frame is advanced based on the frameCount, 
         // frameHold and loops parameters to the sprite constructor.
         // ------------------------------------------------------------------
         void AutoFrameAdvance();


         // ------------------------------------------------------------------
         // ResetAnimation
         // ------------------------------------------------------------------
         // Rest the sprite animation so that IsAnimationFinished() returns false 
         // and the animation frame is set back to 0.
         // ------------------------------------------------------------------
         void ResetAnimation();


         // ------------------------------------------------------------------
         // SetCurrentFrame
         // ------------------------------------------------------------------
         // Manually set the current animation frame of the sprite.
         //
         // current_frame
         //    The new current frame.
         //    PRE: currentFrame < GetFrameCount()
         // ------------------------------------------------------------------
         void SetCurrentFrame(unsigned int currentFrame);


         // ------------------------------------------------------------------
         // SetBlendMode
         // ------------------------------------------------------------------
         // Set the blend mode of the sprite.
         //
         // newBlendMode
         //    The new blend mode.  See BlendMode for more details.
         // ------------------------------------------------------------------
         void SetBlendMode(BlendMode newBlendMode);


         // ------------------------------------------------------------------
         // EnableAutoAlphaMask
         // ------------------------------------------------------------------
         // Enable and set the properties of the automatic alpha channel
         // generation.
         //
         // If a sprite already has an alpha channel, it is replaced with the 
         // auto generated channel.
         //
         // Auto alpha should be enabled after a sprite has been constructed
         // but before it's been rendered (so it hasn't been loaded yet). Any
         // changes to auto alpha (enable, disable) after the sprite has been 
         // rendered won't take effect until after the sprite has been cached
         // out of memory and then cached back in.
         //
         // Auto alpha actually applies to a texture, not to a sprite, so if
         // two sprites load the same texture but only one has auto alpha 
         // enabled, they will both get an auto alpha channel.
         //
         // c
         //    Colour used to specify the transparent colour in a texture.
         //    Any pixels with a colour within tolerance range of c will be
         //    given an alpha of zero (or between zero and one if fade is on).
         // tolerance
         //    The colour space distance which is used to select pixels for 
         //    transparency. The colour space distance between black and pure
         //    red is 1. If tolerance is zero, only pixels with exactly the
         //    same colour as c will become transparent.
         // fade
         //    When fade is false, all pixels will have alpha of 0 or 1. When
         //    fade is true, pixels within tolerance range of c will have an 
         //    alpha proportional to their colour space distance from c.
         // ------------------------------------------------------------------
         void EnableAutoAlphaMask(const Colour &c, float tolerance, bool fade);


         // ------------------------------------------------------------------
         // DisableAutoAlphaMask
         // ------------------------------------------------------------------
         // Disable the auto alpha generation.
         // ------------------------------------------------------------------
         void DisableAutoAlphaMask();


         // ------------------------------------------------------------------
         // SetColour
         // ------------------------------------------------------------------
         // Set the colour of a sprite. Each corner can be set individually,
         // or all at once to the same value.
         //
         // The colour is modulated with the colour of each pixel. For 
         // example, a green sprite with a red colour will appear black.
         //
         // Control blending by modifying the alpha value of the sprite 
         // colour.
         //
         // c
         //    Colour to set either the entire sprite or a single corner to.
         // corner
         //    Can be CORNER_TOP_LEFT, CORNER_TOP_RIGHT, CORNER_BOTTOM_LEFT or
         //    CORNER_BOTTOM_RIGHT.
         // ------------------------------------------------------------------
         void SetColour(const Colour &c);
         void SetColour(const Colour &c, Corner corner);


         // ------------------------------------------------------------------
         // Revert
         // ------------------------------------------------------------------
         // The memory and system textures are reverted to the image file
         // strored on disk.
         // ------------------------------------------------------------------
         void Revert();


         // ------------------------------------------------------------------
         // Lock
         // ------------------------------------------------------------------
         // Lock the sprite's texture so it can be accessed by the pixel
         // manipulation methods.
         //
         // Locking creates a memory buffer containing a copy of a texture.
         // This memory buffer will stay associated with the texture until
         // it is destroyed.
         // 
         // Changes to the texture aren't committed until the texture is 
         // unlocked. This means you can lock a sprite and take several frames
         // to update it without stopping it from rendering or seeing a
         // partially modified version.
         // 
         // Returns
         //    A pointer to the memory buffer containing the texture (in
         //    32 bit RGBA format). This can be used for fastest access to 
         //    the sprite's texture, but you will have to manually set regions
         //    to dirty (meaning they will be sent back to opengl) using the
         //    UpdateRegion() method.
         // ------------------------------------------------------------------
         fdword *Lock();


         // ------------------------------------------------------------------
         // Unlock
         // ------------------------------------------------------------------
         // Unlocks a sprite's locked texture.
         //
         // On the next render, any dirty regions of the texture will be
         // committed back to opengl.
         // ------------------------------------------------------------------
         void Unlock();

         // ------------------------------------------------------------------
         // UpdateRegion
         // ------------------------------------------------------------------
         // Set a region of the screen to the dirty state, which will cause
         // that region to be committed back to opengl the next time the
         // sprite is rendered while not locked.
         //
         // y1
         //    First line to update (must be between 0 and frame height).
         // y2
         //    Last line to update (must be between 0 and frame height).
         // ------------------------------------------------------------------
         void UpdateRegion(fdword y1, fdword y2);

         // ------------------------------------------------------------------
         // SetPixelRGBA
         // SetPixelColour
         // ------------------------------------------------------------------
         // Set one pixel in a sprite's locked texture.
         //
         // x
         //    x coordinate of pixel (0 <= x < frame width)
         // y
         //    y coordinate of pixel (0 <= y < frame height)
         // c
         //    The colour (in 32 bit RGBA or Colour object form) to set the
         //    pixel to.
         //
         // Preconditions
         //    If the sprite isn't locked, no changes are made to the sprite's
         //    texture.
         // ------------------------------------------------------------------
         void SetPixelRGBA(fdword x, fdword y, fdword c);
         void SetPixelColour(fdword x, fdword y, const Colour &c);

         // ------------------------------------------------------------------
         // GetPixelRGBA
         // GetPixelColour
         // ------------------------------------------------------------------
         // Get one pixel in a sprite's locked texture.
         //
         // x
         //    x coordinate of pixel (0 <= x < frame width)
         // y
         //    y coordinate of pixel (0 <= y < frame height)
         //
         // Returns
         //    The colour (in 32 bit RGBA or Colour object form) of the pixel.
         //
         // Preconditions
         //    If the sprite isn't locked, black is returned.
         // ------------------------------------------------------------------
         fdword GetPixelRGBA(fdword x, fdword y);
         Colour GetPixelColour(fdword x, fdword y);

         // ------------------------------------------------------------------
         // ClearPixelsRGBA
         // ClearPixelsColour
         // ------------------------------------------------------------------
         // Fill the entire sprite with a single colour.
         //
         // c
         //    The colour (in 32 bit RGBA or Colour object form) to fill the
         //    sprite's texture with.
         //
         // Preconditions
         //    If the sprite isn't locked, no changes are made to the sprite's
         //    texture.
         // ------------------------------------------------------------------
         void ClearPixelsRGBA(fdword c);
         void ClearPixelsColour(const Colour &c);


         // ------------------------------------------------------------------
         // SetFilter
         // ------------------------------------------------------------------
         // Specify the type of texture mapping filter used when the area being
         // texture mapped is smaller or larger than the actual texture.
         // ------------------------------------------------------------------
         void SetFilter(Filter minFilter, Filter magFilter);


      private:
         void CalculateTextureCoords();
         void NextFrame();

         SpriteImpl *m_impl;
      };

   }  // end namespace GF1


//****************************************************************************
//**
//**   END INTERFACE
//**
//****************************************************************************
#endif
