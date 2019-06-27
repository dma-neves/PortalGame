#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    static sf::Texture loadTexture(std::string fileDir);

private:
    static std::map<std::string ,sf::Texture> textures;
};

#endif
