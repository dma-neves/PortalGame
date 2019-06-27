#include "TextureManager.h"

#include <iostream>

std::map<std::string ,sf::Texture> TextureManager::textures;

sf::Texture TextureManager::loadTexture(std::string newFileDir)
{
    std::map<std::string ,sf::Texture>::iterator it = textures.find(newFileDir);
    if(it == textures.end())
    {
	    sf::Texture newTexture;
		newTexture.loadFromFile(newFileDir);
		textures.insert(std::pair<std::string, sf::Texture> (newFileDir, newTexture) );
		return newTexture;
    }
    else return it->second;
}
