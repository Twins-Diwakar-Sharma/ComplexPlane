#include "Engine.h"

int main(int argc, char** argv)
{

    char* title = (char*)"Argand Plane";
    if(argc > 1)
    {
        std::cout << "There should be no arguements " << std::endl;
    }
    Engine engine(512,512,title);
    return 0;
}
