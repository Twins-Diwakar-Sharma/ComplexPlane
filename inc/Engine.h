#ifndef H_ENGINIUM_H
#define H_ENGINIUM_H

#include "Shaders.h"
#include "Window.h"
#include "Renderer.h"
#include <thread>
#include <time.h>
#include "Parser.h"

class Engine
{
  private:
      std::thread* gameThread;
      frame::Window* window;
      Renderer* renderer;
      Grid* grid;
      float ortho;
      std::string* code;
      bool pollCode = false;
      bool mousePressStart = false;

      void startGameThread();
      void endGameThread();
      void gameloop();
      void init();
      void input();
      void update();
      void render();

	  void cmdInput();

      int width, height;
      char* title;
      static double fps;
      static double MS_PER_UPDATE;

      std::string* compiledCode;
      std::string zLex="c";
      Parser parser;
 public:
      Engine(int,int,char*,std::string&);
      ~Engine();

};

#endif
