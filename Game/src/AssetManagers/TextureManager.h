#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    static sf::Texture loadTexture(std::string fileDir);

private:
    static std::vector<sf::Texture>texture;
    static std::vector<std::string>fileDir;
};

#endif
