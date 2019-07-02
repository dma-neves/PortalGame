#include <iostream>

#define BUILD "cd Game; make; cd .."
#define RUN_GAME "cd Game/bin; ./PortalGame.out; cd ../.."
#define RUN_EDITOR "cd LevelEditor/src; python app.py; cd ../.."

void runCommand(char* cmd)
{
    std::cout << "Command: "  << cmd<< std::endl << std::endl;
    system(cmd);
}

int main()
{
    int input = 0;

    while(input != 4)
    {
        std::cout << std::endl << "1) Build program" << std::endl;
        std::cout << "2) Run game" << std::endl;
        std::cout << "3) Run editor" << std::endl;
        std::cout << "4) exit" << std::endl << std::endl;

        std::cin >> input;
        switch(input)
        {
            case 1: runCommand(BUILD); break;
            case 2: runCommand(RUN_GAME); break;
            case 3: runCommand(RUN_EDITOR); break;
        }
    }
}