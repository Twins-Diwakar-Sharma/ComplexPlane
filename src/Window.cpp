#include "Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int frame::Window::width = 512;
int frame::Window::height = 512;
double frame::Window::clickX;
double frame::Window::clickY;
bool frame::Window::startClick = false;

frame::Window::Window(int width, int height, char* name, std::string icon)
{
    frame::Window::width = width;
    frame::Window::height = height;
    this->name = name;
    this->icon = icon;
    createWindow();
}

frame::Window::~Window()
{

}

void frame::Window::createWindow()
{
    if(!glfwInit())
    {
        std::cerr<< "Failed to initialize glfw3 " << std::endl;
        glfwTerminate();
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    glfwWindowHint(GLFW_DECORATED,false);

    window = glfwCreateWindow(width,height,name,NULL,NULL);
    if(window==NULL)
    {
        std::cerr << "Failed to create window " << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetCursorPosCallback(window,cursorPos);

    setWindowIcon(icon);
    glfwMakeContextCurrent(window);
    glViewport(0,0,width,height);
    glfwSwapInterval(1);

}

bool frame::Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void frame::Window::forceClose()
{
    glfwSetWindowShouldClose(window,true);
}

void frame::Window::destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void frame::Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void frame::Window::poll()
{
    glfwPollEvents();
}

bool frame::Window::keyPressed(int key)
{
    return glfwGetKey(window,key) == GLFW_PRESS;
}

bool frame::Window::mousePressed(int button)
{
    return glfwGetMouseButton(window,button) == GLFW_PRESS;
}

void frame::Window::setWindowIcon(std::string target)
{
    std::string path = "res/";
    GLFWimage icon[1];
    icon[0].pixels = stbi_load((path+target).c_str(),&icon[0].width,&icon[0].height,0,4);
    glfwSetWindowIcon(window, 1, icon);
    stbi_image_free(icon[0].pixels);

}

void frame::Window::changePosition()
{
    /*double changeX = xPos - clickX;
    double changeY = yPos - clickY;
    glfwGetWindowPos(window,&winX,&winY);
    winX += (int)changeX;
    winY += (int)changeY;
    glfwSetWindowPos(window,winX,winY);
    glfwSetCursorPos(window,clickX,clickY);*/
}

void frame::Window::setMouseClickPos()
{
   /*glfwGetCursorPos(window,&clickX,&clickY);*/
}

void frame::Window::cursorPos(GLFWwindow* win,double dx, double dy)
{
   if(glfwGetMouseButton(win,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
   {
        if(!startClick)
        {
            startClick = true;
            glfwGetCursorPos(win,&clickX,&clickY);
        }
        double changeX = dx - clickX;
        double changeY = dy - clickY;
        int wx, wy;
        glfwGetWindowPos(win,&wx,&wy);
        wx += (int)changeX;
        wy += (int)changeY;
        glfwSetWindowPos(win,wx,wy);
        glfwSetCursorPos(win,clickX,clickY);
   }
   else
   {
        startClick =false;
   }
}

