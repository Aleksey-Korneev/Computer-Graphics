#include "tile.hpp"

Tile::Tile(const std::string &path, int x, int y, TileType tile_type)
{
    if (!SetSprite(path)) {
        std::cerr << "An error occured while downloading a sprite!" << std::endl;
    }
    tileType = tile_type;
    pos = sf::Vector2f(x, y);
    sprite.setPosition(pos);
}

bool Tile::SetSprite(const std::string &path)
{
    if (!texture.loadFromFile(path)) {
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    return true;
}
