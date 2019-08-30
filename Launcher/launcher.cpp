#include <iostream>
#include <fstream>
#include <cstring>

#define BUILD "cd Game; make clean; make; cd .."
#define RUN_GAME "cd Game/bin; ./PortalGame.out; cd ../.."
#define RUN_EDITOR "cd LevelEditor/src; python app.py; cd ../.."
#define LEVELS "cd Assets/Levels;"

#define LEVEL_NAMES_PATH "Assets/Levels/levelNames.txt"

void showLevels();
void eraseFileLine(std::string path, std::string eraseLine);
void deleteLevel();

void runCommand(char* cmd)
{
    std::cout << "Command: "  << cmd<< std::endl << std::endl;
    system(cmd);
}

int main()
{
    int input = 0;

    while(input != 6)
    {
        std::cout << std::endl << "1) Build program" << std::endl;
        std::cout << "2) Run game" << std::endl;
        std::cout << "3) Run editor" << std::endl;
        std::cout << "4) Show levels" << std::endl;
        std::cout << "5) Delete level" << std::endl;
        std::cout << "6) exit" << std::endl << "> ";

        std::cin >> input;
        switch(input)
        {
            case 1: runCommand(BUILD); break;
            case 2: runCommand(RUN_GAME); break;
            case 3: runCommand(RUN_EDITOR); break;
            case 4: showLevels(); break;
            case 5: deleteLevel(); break;
        }
    }
}

void showLevels()
{
    std::cout << "\nLevel names: " << std::endl;
    std::ifstream namesFile(LEVEL_NAMES_PATH);

    std::string name;
    while (namesFile >> name) std::cout << name << std::endl;

    namesFile.close();
}

void deleteLevel()
{
    std::cout << "Level name: ";
    std::string levelName; std::cin >> levelName;

    bool valid = false;
    std::ifstream namesFile(LEVEL_NAMES_PATH);
    std::string name;
    while (namesFile >> name)
    {
        if(name == levelName)
        {
            valid = true;
            break;
        }
    }
    namesFile.close();

    if(!valid) std::cout << "Error: Invalid level name" << std::endl;

    else
    {
        eraseFileLine(LEVEL_NAMES_PATH, name);

        std::string path = std::string("Assets/Levels/") + levelName + ".txt";
        remove(path.c_str());
    }
}

void eraseFileLine(std::string path, std::string eraseLine) 
{
    std::string line;
    std::ifstream fin;

    fin.open(path);
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line)) 
    {
        if (line != eraseLine) temp << line << std::endl;
    }

    temp.close();
    fin.close();

    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}