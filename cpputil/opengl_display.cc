#include "opengl_display.hh"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xmu/Xmu.h>
#include <X11/Xmu/StdCmap.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <map>

namespace {

  std::map<int, const char*> xevent_names;

  void init_xevent_names()
  {
    xevent_names[KeyPress] = "KeyPress";
    xevent_names[KeyPress] = "KeyPress";
    xevent_names[KeyRelease] = "KeyRelease";
    xevent_names[ButtonPress] = "ButtonPress";
    xevent_names[ButtonRelease] = "ButtonRelease";
    xevent_names[MotionNotify] = "MotionNotify";
    xevent_names[EnterNotify] = "EnterNotify";
    xevent_names[LeaveNotify] = "LeaveNotify";
    xevent_names[FocusIn] = "FocusIn";
    xevent_names[FocusOut] = "FocusOut";
    xevent_names[KeymapNotify] = "KeymapNotify";
    xevent_names[Expose] = "Expose";
    xevent_names[GraphicsExpose] = "GraphicsExpose";
    xevent_names[NoExpose] = "NoExpose";
    xevent_names[VisibilityNotify] = "VisibilityNotify";
    xevent_names[CreateNotify] = "CreateNotify";
    xevent_names[DestroyNotify] = "DestroyNotify";
    xevent_names[UnmapNotify] = "UnmapNotify";
    xevent_names[MapNotify] = "MapNotify";
    xevent_names[MapRequest] = "MapRequest";
    xevent_names[ReparentNotify] = "ReparentNotify";
    xevent_names[ConfigureNotify] = "ConfigureNotify";
    xevent_names[ConfigureRequest] = "ConfigureRequest";
    xevent_names[GravityNotify] = "GravityNotify";
    xevent_names[ResizeRequest] = "ResizeRequest";
    xevent_names[CirculateNotify] = "CirculateNotify";
    xevent_names[CirculateRequest] = "CirculateRequest";
    xevent_names[PropertyNotify] = "PropertyNotify";
    xevent_names[SelectionClear] = "SelectionClear";
    xevent_names[SelectionRequest] = "SelectionRequest";
    xevent_names[SelectionNotify] = "SelectionNotify";
    xevent_names[ColormapNotify] = "ColormapNotify";
    xevent_names[ClientMessage] = "ClientMessage";
    xevent_names[MappingNotify] = "MappingNotify";
  }

}

namespace util {

  opengl_display::opengl_display(int argc, char** argv)
    throw(std::runtime_error)
  {

    if (!xevent_names.size())
      init_xevent_names();

    const char* name = 0;
    for (int i=1; i<argc; ++i) {
      if (!std::strcmp(argv[i], "-display") ||
	  !std::strcmp(argv[i], "-d"))
      {
	if (i==argc-1)
	  throw std::runtime_error("-display option requires an argument");
	name = argv[i+1];
	break;
      }
    }
    init(name);
  }

  void opengl_display::init(const char* name)
    throw(std::runtime_error)
  {
    dpy = XOpenDisplay(name); 
    if (!dpy)
      throw std::runtime_error("could not open display");
  }

  opengl_display::~opengl_display() {
    XCloseDisplay(dpy);
  }

  Colormap opengl_window::get_colormap() {
    if (vi->visual == DefaultVisual(dpy.dpy, vi->screen))
      return DefaultColormap(dpy.dpy, vi->screen);

    Status status = XmuLookupStandardColormap( dpy, vi->screen,
					       vi->visualid,
					       vi->depth,
					       XA_RGB_DEFAULT_MAP,
					       False, // replace
					       True   // retain
					       );

    if (status) {
      XStandardColormap* cmaps;
      int ncmaps;
      status = XGetRGBColormaps(dpy, RootWindow(dpy.dpy, vi->screen),
				&cmaps, &ncmaps, XA_RGB_DEFAULT_MAP);
      if (status) {
	for (int i=0; i<ncmaps; ++i) {
	  if (cmaps[i].visualid == vi->visualid) {
	    Colormap cmap = cmaps[i].colormap;
	    XFree(cmaps);
	    return cmap;
	  }
	}
	XFree(cmaps);
      }
    }
    throw std::runtime_error("could not get colormap");
  }

  opengl_window::opengl_window(int argc, char** argv)
    throw(std::runtime_error)
    : dpy(argc,argv), fullscreen_(false),
      pointer_x_(1), pointer_y_(1), width_(0), height_(0)
  {

    // get what information we can from the arguments
    const char* name = argc ? argv[0] : 0;
    int x=0, y=0;
    unsigned int w=300, h=300;
    for (int i=1; i<argc; ++i) {
      if (!std::strcmp(argv[i], "-name") ||
	  !std::strcmp(argv[i], "-n"))
      {
	if (i==argc-1)
	  throw std::runtime_error("-name option requires an argument");
	name = argv[++i];
      }
      else if (!std::strcmp(argv[i], "-geometry") ||
	       !std::strcmp(argv[i], "-g"))
      {
	if (i==argc-1)
	  throw std::runtime_error("-geometry option requires an argument");
	XParseGeometry(argv[++i], &x, &y, &w, &h);
      }
    }

    int attr[] = {
      GLX_DOUBLEBUFFER,
      GLX_RGBA,
      GLX_RED_SIZE, 3,
      GLX_GREEN_SIZE, 3,
      GLX_BLUE_SIZE, 2,
      GLX_ALPHA_SIZE, 4,
      GLX_DEPTH_SIZE, 4,
      None
    };

    vi = glXChooseVisual(dpy, DefaultScreen(dpy.dpy), attr);
    if (!vi)
      throw std::runtime_error("could not get a visual");

    ctx = glXCreateContext(dpy, vi, 0, GL_FALSE);
    if (!ctx)
      throw std::runtime_error("could not create rendering context");

    Colormap cmap = get_colormap();

    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask =
      StructureNotifyMask |
      KeyPressMask | KeyReleaseMask |
      ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ButtonMotionMask |
      EnterWindowMask | LeaveWindowMask |
      ExposureMask |
      0;

    width_ = w;
    height_ = h;
    win = XCreateWindow(dpy,
			RootWindow(dpy.dpy, vi->screen),
			x, y, w, h, 0, vi->depth,
			InputOutput, vi->visual,
			CWBorderPixel|CWColormap|CWEventMask, &swa);

    Atom del_atom = XInternAtom(dpy,"WM_DELETE_WINDOW",False);
    /*
    XChangeProperty(dpy, win,
		    XInternAtom(dpy,"WM_PROTOCOLS",False),
		    XA_ATOM, 32, PropModeAppend,
		    (const unsigned char*)&del_atom, 1
		    );
    */
    XSetWMProtocols(dpy, win, &del_atom, 1);

    const char cursor_empty_data[] = { 0 };
    cursor_pixmap = XCreateBitmapFromData(dpy, win, cursor_empty_data,
					  1,1);
    cursor_color.red = cursor_color.green = cursor_color.blue = 0;
    cursor_color.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(dpy, cmap, &cursor_color);
    cursor_empty = XCreatePixmapCursor(dpy, cursor_pixmap, cursor_pixmap,
				       &cursor_color, &cursor_color ,0,0);
    XDefineCursor(dpy, win, cursor_empty);
    
    if (name)
      set_name(name);

    XMapWindow(dpy, win);
    make_current();

  }

  void opengl_window::swap_buffers()
  {
    glXSwapBuffers(dpy, win);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
      std::cerr << gluErrorString(err) << '\n';
  }

  void opengl_window::set_size(int w, int h)
  {
    XResizeWindow(dpy, win, w, h);
  }

  void opengl_window::set_name(const char* name) {
    XStoreName(dpy, win, name);
  }

  void opengl_window::handle_events() {
    XEvent e;
    while (XPending(dpy)) {
      XNextEvent(dpy, &e);
      switch (e.type) {

      case ClientMessage:
	if (
	    XInternAtom(dpy,"WM_PROTOCOLS",False) == e.xclient.message_type &&
	    XInternAtom(dpy,"WM_DELETE_WINDOW",False) == static_cast<Atom>(e.xclient.data.l[0]) &&
	    e.xclient.format==32
	    )
	  del_p();
	break;

      case Expose:
	if (e.xexpose.count == 0)
	  expose();
	break;

      case ConfigureNotify:
	if (e.xconfigure.width != width_ ||
	    e.xconfigure.height != height_)
	  {
	    width_ = e.xconfigure.width;
	    height_ = e.xconfigure.height;
	    resize(width_, height_);
	  }
	break;

      case KeyPress:
	keypress('a');
	break;

      case KeyRelease:
	keyrelease('a');
	break;

      case MotionNotify:
	pointer_x_ = e.xmotion.x;
	pointer_y_ = e.xmotion.y;
	pointer_motion(pointer_x(), pointer_y());
	break;

      case EnterNotify:
	enter();
	break;

      case LeaveNotify:
	leave();
	break;

      case ButtonPress:
	button_press(e.xbutton.button, e.xbutton.x, height_-e.xbutton.y-1);
	break;

      case ButtonRelease:
	button_release(e.xbutton.button, e.xbutton.x, height_-e.xbutton.y-1);
	break;

      default:
	std::map<int, const char*>::const_iterator it =
	  xevent_names.find(e.type);
	std::cerr
	  << "Unhandled XEvent: "
	  << (it == xevent_names.end() ? "UNKNOWN EVENT" : it->second)
	  << '\n';
      }
    }
  }

  void opengl_window::fullscreen(bool doit)
  {
    if (fullscreen_ == doit)
      return;

    if (doit) {
      no_fullscreen();
      fullscreen_ = false;
    }
    else
      fullscreen_ = go_fullscreen();
  }

  bool opengl_window::go_fullscreen()
  {
    if (!width() || !height())
      return false;

    return true;
  }

  void opengl_window::no_fullscreen()
  {

  }

  

  void opengl_window::del_p() {
    if (del())
      XUnmapWindow(dpy, win);
  }

  opengl_window::~opengl_window() {
    XFreePixmap(dpy, cursor_pixmap);
    XFreeCursor(dpy, cursor_empty);
    glXDestroyContext(dpy, ctx);
    XDestroyWindow(dpy, win);
  }

  unsigned char opengl_cursor_drawpix::data[5][5][4] = {
    {
      {0,0,0,0},
      {0,0,0,0},
      {255,255,255,255},
      {0,0,0,0},
      {0,0,0,0}
    },

    {
      {0,0,0,0},
      {0,0,0,0},
      {255,255,255,255},
      {0,0,0,0},
      {0,0,0,0}
    },

    {
      {255,255,255,255},
      {255,255,255,255},
      {255,255,255,255},
      {255,255,255,255},
      {255,255,255,255}
    },

    {
      {0,0,0,0},
      {0,0,0,0},
      {255,255,255,255},
      {0,0,0,0},
      {0,0,0,0}
    },

    {
      {0,0,0,0},
      {0,0,0,0},
      {255,255,255,255},
      {0,0,0,0},
      {0,0,0,0}
    }

  };

  const unsigned char opengl_cursor_texture::data[16*16*4+1] =
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\377\377\377\377\377\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\377\377\377\377\377\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\377\377\377\377\0\377\377\377\0\377\377\377\377"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\377\377\377\377\0\377\377"
  "\377\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\377\377\377\377"
  "\0\377\377\377\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\377"
  "\377\377\377\0\377\377\377\377\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\377\377\377\377\0\377\377\377\0\377\377\377\377\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\377"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\377"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\377\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\377\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\377\377\377\377\377\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\377\377\377\377\0\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\377\377\377\377\377\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\377\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377"
  "\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0"
  "\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377"
  "\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377\377\0\377\377"
  "\377\0";

}
