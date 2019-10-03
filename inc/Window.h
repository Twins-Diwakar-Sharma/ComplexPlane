#ifndef H_KHIDKI_H
#define H_KHIDKI_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
namespace frame
{
    class Window
    {
        private:
            GLFWwindow* window;
            char* name;
            void createWindow();
            std::string icon;
            int winX, winY;
            void setWindowIcon(std::string);

            static void cursorPos(GLFWwindow*,double,double);
            static double clickX,clickY;
            static bool startClick;


         public:
            static int width, height;

            Window(int,int,char*,std::string);
            ~Window();

            bool shouldClose();
            void forceClose();
            void destroy();
            void swapBuffers();
            void poll();
            bool keyPressed(int);
            bool mousePressed(int);
            void changePosition();
            void setMouseClickPos();

   };

}

#endif
