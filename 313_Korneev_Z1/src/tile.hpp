#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>

#ifndef TILE_HPP
#define TILE_HPP

#pragma once

enum class TileType
{
    BLOOD,
    DOOR,
    EMPTY,
    FLOOR,
    GAME_EXIT,
    GOLD_COIN,
    GOLD_PILE,
    HEALTH_POTION,
    HEART,
    INNER_WALL,
    OUTER_WALL,
    PLAYER,
    ROOM_EXIT,
    STAMINA_POTION,
    TORCH_EMPTY,
    TORCH_FLOOR,
    TRAP,
    TREASURE_CLOSED,
    TREASURE_OPENED
};

class Tile
{
public:
    Tile() {};
    Tile(const std::string &path, int x, int y, TileType tile_type);
    bool SetSprite(const std::string &path);

    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;
    TileType tileType;
    static const std::set<TileType> MOVABLE;
};

const std::set<TileType> Tile::MOVABLE =
{
    TileType::FLOOR,
    TileType::GAME_EXIT,
    TileType::GOLD_COIN,
    TileType::GOLD_PILE,
    TileType::HEALTH_POTION,
    TileType::ROOM_EXIT,
    TileType::STAMINA_POTION,
    TileType::TRAP,
    TileType::TREASURE_CLOSED,
    TileType::TREASURE_OPENED
};

#endif
