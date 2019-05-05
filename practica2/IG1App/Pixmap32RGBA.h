//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
#ifndef _H_PixMap32RGBA_H
#define _H_PixMap32RGBA_H

//#include <Windows.h>
//#include <gl/GL.h>
#include <GL/freeglut.h>
#include <string>

class PixMap32RGBA {   
public:
	
   struct rgba_color
   {
     GLubyte r,g,b,a;
   };
   
private:
   rgba_color * data_;
   GLsizei   width_;
   GLsizei   height_;
 
public:

   PixMap32RGBA()  // noexcept  
   : data_(nullptr), width_(0), height_(0) {}

   PixMap32RGBA(const std::string& filename) // throw(std::ios_base::failure, std::bad_alloc)
   : data_(nullptr), width_(0), height_(0)
   {
      load_bmp24BGR(filename);
   }

   ~PixMap32RGBA() 
   {
      free();
   }
   
   GLsizei width() const // noexcept
   {
      return width_;
   }

   GLsizei height() const // noexcept
   {
      return height_;
   }

   const rgba_color* data() const // noexcept
   { 
      return data_;
   }

   rgba_color* data() // noexcept
   {
	   return data_;
   }

   bool is_null() const // noexcept
   {
      return (data_  == nullptr); 
   }

   void load_bmp24BGR(const std::string & file_name); // throw(std::ios_base::failure, std::exception);

   void save_bmp24BGR(const std::string & file_name) const;  // throw(std::ios_base::failure);

   void set_alpha(GLubyte alpha = 255);  // throw(std::bad_alloc)   
   void set_colorkey_alpha(rgba_color colorKey, GLubyte alpha = 255);  // throw(std::bad_alloc)   

   void create_pixmap(GLsizei   width, GLsizei   height); // throw(std::bad_alloc);
   void free();  // noexcept;

protected:

   PixMap32RGBA(const unsigned int width, const unsigned int height); // throw(std::bad_alloc)
   PixMap32RGBA(const PixMap32RGBA & pixmap); // throw(std::exception)
   PixMap32RGBA & operator=(const PixMap32RGBA & pixmap); // throw(std::exception)

   void load_headers(std::ifstream & stream,  unsigned int & width, unsigned int & height) const; // throw(std::ios_base::failure);
   void save_headers(std::ofstream & stream) const; // noexcept;

   void row_bgr_rgba(char* rowAux, unsigned int r); // noexcept;
   void row_rgba_bgr(char* rowAux, unsigned int r) const; // noexcept;

   void get_pixel(const GLsizei x, const GLsizei y, rgba_color & rgba) const
   {
     rgba = data_[y * width_ + x];
   }

   void set_pixel(const GLsizei x, const GLsizei y, const rgba_color & rgba)
   {
     data_[y * width_ + x] = rgba;
   }

};

   
#endif
