#include "Engine.h"

double Engine::fps = 400.0;
double Engine::MS_PER_UPDATE = 1000/fps;

Engine::Engine(int width, int height, char* name,std::string &mcode)
{
    this->width = width;
    this->height = height;
    this->title = name;
    code = &mcode;
    std::cout << this->code << std::endl;
    compiledCode = new std::string();
    startGameThread();

	cmdInput();

   	endGameThread();
}

Engine::~Engine()
{
  delete window;
}

void Engine::init()
{

    window = new frame::Window(width,height,title,"icon.png");
    std::cout << *code << std::endl;
    shaders::updateGridShader(code);
    renderer = new Renderer();
    renderer->linkCode(shaders::grid_vs,shaders::grid_gs,shaders::grid_fs);
    // inserting world
    //projection::setOrthogonal(-40,40,-40,40,-40,40);
    ortho = 10;
    projection::setOrthogonal(ortho);

    grid = new Grid(20);
    grid->setInterpolation(80);
    glClearColor(0.05f,0.05f,0.05f,1);

}

void Engine::input()
{
   // if(window->keyPressed(GLFW_KEY_ESCAPE))
   // {
   //     window->forceClose();
  //  }
    if(window->keyPressed(GLFW_KEY_R))
    {
        grid->setT(0);
    }
    if(window->keyPressed(GLFW_KEY_Z))
    {
        if(window->keyPressed(GLFW_KEY_LEFT_SHIFT)||window->keyPressed(GLFW_KEY_RIGHT_SHIFT))
        {
            ortho += 0.1f;
        }
        else
        {
            if(ortho > 0.1f)
                ortho -= 0.1f;
        }
        projection::setOrthogonal(ortho);
    }
   /* if(window->mousePressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        frame::Window::lClick = true;
    }
    else if(!window->mousePressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        frame::Window::lClick = false;
    }*/
    window->poll();

}

void Engine::update()
{
   grid->update();
    if(pollCode)
    {
        std::cout << " ----------------- " <<*compiledCode<< std::endl;
		delete renderer;
	    shaders::updateGridShader(compiledCode);
    	renderer = new Renderer();
    	renderer->linkCode(shaders::grid_vs,shaders::grid_gs,shaders::grid_fs);
		pollCode = false;
        grid->setT(0);
        code->clear();
    }
}

void Engine::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    renderer->render(*grid);
    window->swapBuffers();
}

void Engine::startGameThread()
{
    gameThread = new std::thread(&Engine::gameloop,this);
    std::cout << "It starts" << std::endl;
}

void Engine::endGameThread()
{
    gameThread->join();
    std::cout << "I hate to loose " << std::endl;
}

void Engine::gameloop()
{
    clock_t start=clock(), end=clock();
    double elapsed=0, lag=0;

    init();

    while(!window->shouldClose())
    {
        elapsed = ( (double)(end - start))*1000/CLOCKS_PER_SEC;
        lag += elapsed;

        start = clock();
        input();
        while(lag >= MS_PER_UPDATE)
        {
            update();
            //std::cout << "update" << std::endl;
            lag -= MS_PER_UPDATE;
        }
		if(!pollCode)
        	render();
        //std::cout << "render " << std::endl;
        end = clock();
    }
    window->destroy();
}

void Engine::cmdInput()
{
std::string name="notquit";
	while(name.compare("exit") != 0)
	{
		getline(std::cin,name);
        if(name.compare("!") == 0)
        {
           // pollCode = true;
            parser.reset(code,zLex);
            std::cout << "#########" << *code << std::endl;
            if(parser.parseAndTranslate(compiledCode))
            {
                pollCode = true;
            }
            else
            {
                std::cerr<<(*compiledCode)<<std::endl;
            }
           *code = "";
        }
        else
		    (*code) += (name + " $ ");
    }
    window->forceClose();

}
