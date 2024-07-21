#include "opengl_display.hh"
#include "timer.hh"
#include <iostream>
#include <exception>
#include <cstdlib>
#include <csignal>

using namespace std;

class my_opengl_window;
namespace {
  my_opengl_window* gwindow = 0;
  util::timer gtimer;
}

class rect {
  GLuint list;

public:
  rect() {

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    glBegin(GL_POLYGON);

    glColor3d(1,0,0);
    glVertex2d(-0.5, -0.5);

    glColor3d(0,1,0);
    glVertex2d(+0.5, -0.5);

    glColor3d(1,1,0);
    glVertex2d(+0.5, +0.5);

    glColor3d(0,0,1);
    glVertex2d(-0.5, +0.5);

    glEnd();

    glEndList();

    glPopMatrix();
  }

  virtual void draw()
  {
    glCallList(list);
  }
    
};

class spinning_rect : public rect
{

  util::timer t;
  const double period;
  const double z;

public:

  spinning_rect(double period, double z)
    : t(false), period(period), z(z)
  {
  }

  void stop() { t.stop(); }
  void start() { t.start(); }

  void draw() {
    double elapsed = t.elapsed();
    double phase = elapsed / period - int( elapsed / period );
    double angle = 360 * phase;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRotated(angle, 0, 0, 1);
    glTranslated(0,0,z);
    rect::draw();
    glPopMatrix();
  }
};

class my_opengl_window : public util::opengl_window {

  spinning_rect r1;
  //  spinning_rect r2;
  util::opengl_cursor_texture cursor;

public:

  bool stop;
  int nframes;
  my_opengl_window(int argc, char**argv)
    : util::opengl_window(argc,argv), r1(2, -0.5), cursor(this),
      stop(false), nframes(0)
  {
    glEnable(GL_DEPTH_TEST);
  }

  void pause() { r1.stop(); }
  void unpause() { r1.start(); }

  void leave() { pause(); }
  void enter() { unpause(); }
  void expose() { draw(); }

  void button_press(int, int, int) { pause(); }
  void button_release(int, int, int) { unpause(); }

  void resize(int w, int h) {
    glViewport(0,0,w,h);
  }

  bool del() {
    stop = true;
    std::cout << "Goodbye, world!\n";
    return true;;
  }

  void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    r1.draw();
    cursor.draw();
    swap_buffers();
    nframes++;
  }

};

extern "C" {
  static void handle_alarm(int signum)
  {
    if (signum != SIGALRM)
      return;

    if (gwindow) {
      std::cout << "FPS = " << (gwindow->nframes / gtimer.elapsed()) << '\n';

      // reset the timer, counter
      gtimer.reset();
      gwindow->nframes = 0;
    }

    alarm(2);
  }
}

int main(int argc, char** argv) {
  try {
    my_opengl_window w1(argc, argv);
    gwindow = &w1;
    std::signal(SIGALRM, handle_alarm);
    alarm(2);
    gtimer.reset();
    while (!w1.stop) {
      w1.handle_events();
      w1.draw();
    }
  }
  catch (exception& e) {
    cerr << "exception caught: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
}
