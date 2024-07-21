#ifndef UTIL_OPENGL_DISPLAY_HH
#define UTIL_OPENGL_DISPLAY_HH

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <stdexcept>
#include <iostream>
#include <cstring>

namespace util {

  class opengl_display {
    Display* dpy;
    void init(const char* display) throw(std::runtime_error);
    friend class opengl_window;
  public:
    opengl_display(int argc=0, char** argv=0) throw(std::runtime_error);
    operator Display*() { return dpy; }
    Display* get_display() { return dpy; }
    ~opengl_display();
  };

  class opengl_window {
    Pixmap cursor_pixmap;
    XColor cursor_color;
    Cursor cursor_empty;
    void del_p();
    opengl_display dpy;
    bool fullscreen_;
    GLXContext ctx;
    XVisualInfo* vi;
    Colormap get_colormap();
    Window win;
    int pointer_x_, pointer_y_;
    int width_, height_;

    bool go_fullscreen();
    void no_fullscreen();

  public:

    opengl_window(int argc=0, char** argv=0) throw(std::runtime_error);

    void handle_events();

    void set_name(const char* name);
    void set_size(int w, int h);
    void swap_buffers();

    int width() { return width_; }
    int height() { return height_; }

    int pointer_x() { return pointer_x_; }
    int pointer_y() { return height_-pointer_y_-1; } // convert to OpenGL coords

    bool fullscreen() { return fullscreen_; };
    void fullscreen(bool make_fullscreen);

    virtual void expose() { }

    virtual void enter() { }

    virtual void leave() { }

    virtual void button_press(int which, int x, int y);

    virtual void button_release(int which, int x, int y);

    virtual void pointer_motion(int x, int y);

    /// Called when a delete window
    virtual bool del() { return true; }

    virtual void make_current() { glXMakeCurrent(dpy, win, ctx); }

    virtual void keypress(char c);

    virtual void keyrelease(char c);

    virtual void resize(int w, int h);

    virtual ~opengl_window();
  };

  class opengl_cursor_texture
  {
    opengl_window* win;
    static const int hot_x=8, hot_y=8;
    static const int w=16, h=16;
    static const unsigned char data[w*h*4+1];
    GLuint texture, list;

  public:
    opengl_cursor_texture(opengl_window* win) : win(win)
    {

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glGenTextures(1, &texture);
      std::cerr << "texture = " << texture << '\n';
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
      		      GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
      		      GL_NEAREST);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h,
      		   0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      
      list = glGenLists(1);
      glNewList(list, GL_COMPILE);

      glPushAttrib( GL_COLOR_BUFFER_BIT | // blend state
		    GL_DEPTH_BUFFER_BIT | // depth buffer state
		    GL_TEXTURE_BIT |      // texture state
		    1 );

      glDisable(GL_DEPTH_TEST);
      glDepthMask(GL_FALSE);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);

      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      glBindTexture(GL_TEXTURE_2D, texture);

      glBegin(GL_POLYGON);
      glColor3d(0,0,0);
      glTexCoord2d(0, 1); glVertex2d(0, 0);
      glTexCoord2d(1, 1); glVertex2d(1, 0);
      glTexCoord2d(1, 0); glVertex2d(1, 1);
      glTexCoord2d(0, 0); glVertex2d(0, 1);
      glEnd();

      glPopAttrib();

      glEndList();


    }

    void draw()
    {
      //      double x = (2.0 * (win->pointer_x()-hot_x)) / win->width() - 1.0;
      //      double y = (2.0 * win->pointer_y()) / win->height() - 1.0;

      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      glOrtho(0, win->width(), 0, win->height(), 1, -1);

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
      glTranslated(win->pointer_x(), win->pointer_y(), 0);
      glScaled(w, h, 1);

      glCallList(list);

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();

      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
    }

    ~opengl_cursor_texture()
    {
      glDeleteLists(list, 1);
      glDeleteTextures(1, &texture);
    }
  };


  class opengl_cursor_drawpix
  {
    opengl_window* win;
    static const int hot_x=2, hot_y=2;
    static const int w=5, h=5;
    static unsigned char data[h][w][4];
    GLuint list;

  public:
    opengl_cursor_drawpix(opengl_window* win) : win(win)
    {
      list = glGenLists(1);
      glNewList(list, GL_COMPILE);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glDisable(GL_BLEND);
      glEndList();
    }

    void draw()
    {
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();

      glOrtho(0,win->width(), 0, win->height(), 1, -1);

      glRasterPos2i(win->pointer_x()-hot_x, win->pointer_y()-hot_y);
      glCallList(list);

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();

      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
    }

    ~opengl_cursor_drawpix()
    {
      glDeleteLists(list, 1);
    }
  };


} // namespace util

inline void util::opengl_window::keypress(char c)
{
  std::cerr << "key pressed: " << c << '\n';
}

inline void util::opengl_window::keyrelease(char c)
{
  std::cerr << "key released: " << c << '\n';
}

inline void util::opengl_window::resize(int, int) { }
inline void util::opengl_window::button_press(int, int, int) { }
inline void util::opengl_window::button_release(int, int, int) { }
inline void util::opengl_window::pointer_motion(int, int) { }

#endif // UTIL_OPENGL_DISPLAY_HH
