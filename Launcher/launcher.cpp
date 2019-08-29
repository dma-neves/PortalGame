#include <iostream>
#include <fstream>

#define BUILD "cd Game; make; cd .."
#define RUN_GAME "cd Game/bin; ./PortalGame.out; cd ../.."
#define RUN_EDITOR "cd LevelEditor/src; python app.py; cd ../.."
#define LEVELS "cd Assets/Levels;"

void runCommand(char* cmd)
{
    std::cout << "Command: "  << cmd<< std::endl << std::endl;
    system(cmd);
}

void showLevels();

int main()
{
    int input = 0;

    while(input != 5)
    {
        std::cout << std::endl << "1) Build program" << std::endl;
        std::cout << "2) Run game" << std::endl;
        std::cout << "3) Run editor" << std::endl;
        std::cout << "4) Show levels" << std::endl;
        std::cout << "5) exit" << std::endl << "> ";

        std::cin >> input;
        switch(input)
        {
            case 1: runCommand(BUILD); break;
            case 2: runCommand(RUN_GAME); break;
            case 3: runCommand(RUN_EDITOR); break;
            case 4: showLevels(); break;
        }
    }
}

void showLevels()
{
    std::cout << "\nLevel names: " << std::endl;
    std::ifstream namesFile("Assets/Levels/levelNames.txt");

    std::string name;
    while (namesFile >> name) std::cout << name << std::endl;
} 