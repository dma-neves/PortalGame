#include "TextureManager.h"

#include <iostream>

std::vector<sf::Texture>TextureManager::texture;
std::vector<std::string>TextureManager::fileDir;

sf::Texture TextureManager::loadTexture(std::string newFileDir)
{
    for(unsigned i = 0; i < fileDir.size(); i++)
    {
        if(fileDir[i] == newFileDir) return texture[i];
    }

    sf::Texture newTexture;
    newTexture.loadFromFile(newFileDir);

    fileDir.push_back(newFileDir);
    texture.push_back(newTexture);

    return texture[texture.size()-1];
}
