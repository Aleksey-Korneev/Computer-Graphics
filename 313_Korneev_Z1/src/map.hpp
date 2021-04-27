#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <memory>
#include "tile.hpp"

#ifndef MAP_HPP
#define MAP_HPP

#pragma once

constexpr int WINDOW_HEIGHT = 800;
constexpr int WINDOW_WIDTH = 800;
constexpr int INVENTORY_WIDTH = 256;
constexpr int TILE_SIZE = 32;
constexpr int PLAYER_SPEED = 8;
constexpr int FRAME_TIME_TORCH = 100;
constexpr int FRAME_TIME_PLAYER = 150;
constexpr int TIME_ACCELERATION = 10000;
constexpr int MAX_HEALTH_POINTS = 5;
constexpr int HOR_TILES = WINDOW_WIDTH / TILE_SIZE;
constexpr int VER_TILES = WINDOW_HEIGHT / TILE_SIZE;

class Map {
    char room;
    Tile *playerTile;
    //std::unique_ptr<Tile> playerTile;
    sf::Vector2f coordStart;
    std::vector<sf::Vector2f> torchCoords;
    sf::RenderWindow &window;

    static bool acceleration;
    static float playerAcceleration;
    static size_t goldCnt;
    static size_t totalNumGold;
    static size_t staminaPotionCnt;
    static size_t healthPointsCnt;
    static std::array<Tile *, MAX_HEALTH_POINTS> healthPoints;
    //static std::array<std::unique_ptr<Tile>, MAX_HEALTH_POINTS> healthPoints;
    static sf::Font inventoryFont;
    static sf::Text textGold;
    static sf::Text numGold;
    static sf::Text textStamina;
    static sf::Text numStamina;
    static sf::Text textTotalGoldFound;
    static sf::Text textDefeat;
    static sf::Text textTimeStaminaPotion;
    static sf::Texture textureFire;
    static sf::Sprite spriteFire;
    static sf::Color fireColor_1;
    static sf::Color fireColor_2;

    void MovePlayer(sf::Keyboard::Key key);
    void UpdateTorchAnimation();
    void UpdatePlayerAnimation();
    void UseStaminaPotion();

    void DrawPlayer() const;
    void DrawInventory() const;

    static void SetText();
    static bool is_suitable_tile(const sf::Vector2f &coord, int i, int j, int radius);

public:
    static size_t gameRow;
    static size_t gameCol;
    std::array<std::array<Tile *, HOR_TILES>, VER_TILES> tiles;
    //std::array<std::array<std::unique_ptr<Tile>, HOR_TILES>, VER_TILES> tiles;
    static sf::Clock clockTorch;
    static sf::Clock clockPlayer;
    static sf::Clock clockStaminaPotion;

    explicit Map(sf::RenderWindow &window_, char room_let);

    void InitGame();
    void Check();
    void FinishGame(TileType tile_type);

    void ChangeOpacity(bool from_0_to_255);
    void PickUpObject(TileType tile_type, bool is_treasure);
    void ProcessEvent(sf::Event &event);
    void ProcessTimeEvents();

    void Draw() const;
    bool ReachedGameEnd() const;
    bool ReachedRoomExit() const;
    bool ReachedTrap() const;
    bool ReachedTreasure() const;
    bool ReachedGoldPile() const;
    bool ReachedGoldCoin() const;
    bool ReachedStaminaPotion() const;
    bool ReachedHealthPotion() const;

    static bool CanPickUpHealthPotion();
    static void ChangeRoom(Map &room);
    static std::vector<std::vector<Map>> CreateGame(sf::RenderWindow &window);
    static void IncreaseGoldCnt(size_t increase);
    static void IncreaseStaminaPotionCnt();
    static void IncreaseHealthPointsCnt();
    static void DecreaseHealthPointsCnt(Map &game);
    static void DecreaseStaminaPotionCnt();
    static void get_player_tile_borders(
            const sf::Vector2f &lu,
            sf::Vector2f &ld,
            sf::Vector2f &ru,
            sf::Vector2f &rd);
};

bool Map::acceleration;
float Map::playerAcceleration;
size_t Map::gameRow;
size_t Map::gameCol;
size_t Map::goldCnt;
size_t Map::totalNumGold;
size_t Map::staminaPotionCnt;
size_t Map::healthPointsCnt;
std::array<Tile *, MAX_HEALTH_POINTS> Map::healthPoints;
//std::array<std::unique_ptr<Tile>, MAX_HEALTH_POINTS> Map::healthPoints;
sf::Font Map::inventoryFont;
sf::Text Map::textGold;
sf::Text Map::numGold;
sf::Text Map::textStamina;
sf::Text Map::numStamina;
sf::Text Map::textTotalGoldFound;
sf::Text Map::textDefeat;
sf::Text Map::textTimeStaminaPotion;
sf::Texture Map::textureFire;
sf::Sprite Map::spriteFire;
sf::Color Map::fireColor_1;
sf::Color Map::fireColor_2;

sf::Clock Map::clockTorch;
sf::Clock Map::clockPlayer;
sf::Clock Map::clockStaminaPotion;

#endif
