#include "map.hpp"
#include "tile.hpp"

// Constructor.
Map::Map(sf::RenderWindow &window_, char room_let = 'A') : room(room_let), window(window_)
{
    std::stringstream filename;
    filename << "../resources/maze/" << room << ".txt";
    std::ifstream file(filename.str());

    for (size_t i = 0; i < VER_TILES; ++i) {
        std::string line;
        getline(file, line);
        for (size_t j = 0; j < HOR_TILES; ++j) {
            switch (line[j]) {
            case ' ': // empty space
                this->tiles[j][i] = new Tile("../resources/images/empty.png", j * TILE_SIZE, i * TILE_SIZE, TileType::EMPTY);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/empty.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::EMPTY));
                break;
            case '#': // outer wall
                this->tiles[j][i] = new Tile("../resources/images/outer_wall.png", j * TILE_SIZE, i * TILE_SIZE, TileType::OUTER_WALL);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/outer_wall.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::OUTER_WALL));
                break;
            case '$': // inner wall
                this->tiles[j][i] = new Tile("../resources/images/inner_wall.png", j * TILE_SIZE, i * TILE_SIZE, TileType::INNER_WALL);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/inner_wall.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::INNER_WALL));
                break;
            case '.': // floor
                this->tiles[j][i] = new Tile("../resources/images/floor.png", j * TILE_SIZE, i * TILE_SIZE, TileType::FLOOR);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/floor.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::FLOOR));
                break;
            case '@': // player
                this->tiles[j][i] = new Tile("../resources/images/floor.png", j * TILE_SIZE, i * TILE_SIZE, TileType::FLOOR);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/floor.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::FLOOR));
                this->playerTile = new Tile("../resources/animation/player/idle/hero_idle_0.png", j * TILE_SIZE, i * TILE_SIZE, TileType::PLAYER);
                //this->playerTile = std::move(std::make_unique<Tile>(std::move("../resources/animation/player/idle/hero_idle_0.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::PLAYER));
                this->coordStart = sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE);
                break;
            case 'i': // trap
                this->tiles[j][i] = new Tile("../resources/images/trap.png", j * TILE_SIZE, i * TILE_SIZE, TileType::TRAP);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/trap.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::TRAP));
                break;
            case 'x': // room exit
                this->tiles[j][i] = new Tile("../resources/images/room_exit.png", j * TILE_SIZE, i * TILE_SIZE, TileType::ROOM_EXIT);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/room_exit.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::ROOM_EXIT));
                break;
            case 'Q': // game exit
                this->tiles[j][i] = new Tile("../resources/images/game_exit.png", j * TILE_SIZE, i * TILE_SIZE, TileType::GAME_EXIT);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/game_exit.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::GAME_EXIT));
                break;
            case 'd': // left door
                this->tiles[j][i] = new Tile("../resources/images/door_left.png", j * TILE_SIZE, i * TILE_SIZE, TileType::DOOR);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/door_left.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::DOOR));
                break;
            case 'f': // middle door
                this->tiles[j][i] = new Tile("../resources/images/door_middle.png", j * TILE_SIZE, i * TILE_SIZE, TileType::DOOR);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/door_middle.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::DOOR));
                break;
                case 'D': // right door
                this->tiles[j][i] = new Tile("../resources/images/door_right.png", j * TILE_SIZE, i * TILE_SIZE, TileType::DOOR);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/door_right.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::DOOR));
                break;
            case 'G': // treasure
                this->tiles[j][i] = new Tile("../resources/images/treasure_closed.png", j * TILE_SIZE, i * TILE_SIZE, TileType::TREASURE_CLOSED);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/treasure_closed.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::TREASURE_CLOSED));
                Map::totalNumGold += 10;
                break;
            case 'g': // gold pile
                this->tiles[j][i] = new Tile("../resources/images/gold_pile.png", j * TILE_SIZE, i * TILE_SIZE, TileType::GOLD_PILE);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/gold_pile.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::GOLD_PILE));
                Map::totalNumGold += 5;
                break;
            case 'j': // gold coin
                this->tiles[j][i] = new Tile("../resources/images/gold_coin.png", j * TILE_SIZE, i * TILE_SIZE, TileType::GOLD_COIN);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/gold_coin.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::GOLD_COIN));
                ++Map::totalNumGold;
                break;
            case 'T': // torch + inner_wall
                this->tiles[j][i] = new Tile("../resources/animation/torch/torch_0_inner_wall.png", j * TILE_SIZE, i * TILE_SIZE, TileType::TORCH_FLOOR);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/animation/torch/torch_0_inner_wall.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::TORCH_FLOOR));
                this->torchCoords.emplace_back(sf::Vector2f(j, i));
                break;
            case 't': // torch + empty
                this->tiles[j][i] = new Tile("../resources/animation/torch/torch_0_empty.png", j * TILE_SIZE, i * TILE_SIZE, TileType::TORCH_EMPTY);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/animation/torch/torch_0_empty.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::TORCH_EMPTY));
                this->torchCoords.emplace_back(sf::Vector2f(j, i));
                break;
            case 'L': // stamina potion
                this->tiles[j][i] = new Tile("../resources/images/stamina_potion.png", j * TILE_SIZE, i * TILE_SIZE, TileType::STAMINA_POTION);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/stamina_potion.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::STAMINA_POTION));
                break;
            case 'H': // health potion
                this->tiles[j][i] = new Tile("../resources/images/health_potion.png", j * TILE_SIZE, i * TILE_SIZE, TileType::HEALTH_POTION);
                //this->tiles[j][i] = std::move(std::make_unique<Tile>(std::move("../resources/images/health_potion.png"), j * TILE_SIZE, i * TILE_SIZE, TileType::HEALTH_POTION));
                break;
            default:
                break;
            }
        }
    }
    file.close();
}

// Update animation and check other long-running processes.
void Map::ProcessTimeEvents()
{
    if (Map::clockTorch.getElapsedTime().asMilliseconds() > FRAME_TIME_TORCH) {
        this->UpdateTorchAnimation();
    }
    if (Map::clockPlayer.getElapsedTime().asMilliseconds() > FRAME_TIME_PLAYER) {
        this->UpdatePlayerAnimation();
    }
    if (Map::acceleration && Map::clockStaminaPotion.getElapsedTime().asMilliseconds() > TIME_ACCELERATION) {
        Map::acceleration = false;
        Map::playerAcceleration = 1.f;
        Map::clockStaminaPotion.restart();
    }
}

void Map::Check()
{
    if (this->ReachedGameEnd()) {
        this->FinishGame(TileType::GAME_EXIT);
    } else if (this->ReachedTrap()) {
        Map::DecreaseHealthPointsCnt(*this);
        this->PickUpObject(TileType::TRAP, false);
    } else if (this->ReachedTreasure()) {
        Map::IncreaseGoldCnt(10);
        this->PickUpObject(TileType::TREASURE_CLOSED, true);
    } else if (this->ReachedGoldPile()) {
        Map::IncreaseGoldCnt(5);
        this->PickUpObject(TileType::GOLD_PILE, false);
    } else if (this->ReachedGoldCoin()) {
        Map::IncreaseGoldCnt(1);
        this->PickUpObject(TileType::GOLD_COIN, false);
    } else if (this->ReachedStaminaPotion()) {
        Map::IncreaseStaminaPotionCnt();
        this->PickUpObject(TileType::STAMINA_POTION, false);
    } else if (this->ReachedHealthPotion() &&
                Map::CanPickUpHealthPotion()) {
        Map::IncreaseHealthPointsCnt();
        this->PickUpObject(TileType::HEALTH_POTION, false);
    }
}

// Update a torch tile animation frame.
void Map::UpdateTorchAnimation()
{
    static size_t frame = 0;
    frame = (frame + 1) % 4;
    for (const sf::Vector2f &coord : torchCoords) {
        if (this->tiles[coord.x][coord.y]->tileType == TileType::TORCH_FLOOR) {
            this->tiles[coord.x][coord.y]->SetSprite(
                    "../resources/animation/torch/torch_" +
                    std::to_string(frame) +
                    "_inner_wall.png");
        } else {
            this->tiles[coord.x][coord.y]->SetSprite(
                    "../resources/animation/torch/torch_" +
                    std::to_string(frame) +
                    "_empty.png");
        }
    }
    Map::clockTorch.restart();
}

// Update the player tile animation frame.
void Map::UpdatePlayerAnimation()
{
    static size_t frame_idle = 0;
    static size_t frame_walk = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        frame_idle = 0;
        frame_walk = (frame_walk + 1) % 10;
        this->playerTile->SetSprite(
            "../resources/animation/player/walk/hero_walk_" +
            std::to_string(frame_walk) +
            ".png");
    } else {
        frame_walk = 0;
        frame_idle = (frame_idle + 1) % 20;
        this->playerTile->SetSprite(
            "../resources/animation/player/idle/hero_idle_" +
            std::to_string(frame_idle) +
            ".png");
    }
    Map::clockPlayer.restart();
}

// Process an event, i.e. game exit or user input.
void Map::ProcessEvent(sf::Event &event)
{
    if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        this->window.close();
    } else if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            this->MovePlayer(sf::Keyboard::W);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->MovePlayer(sf::Keyboard::A);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            this->MovePlayer(sf::Keyboard::S);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->MovePlayer(sf::Keyboard::D);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if (Map::staminaPotionCnt > 0 && !Map::acceleration) {
                this->UseStaminaPotion();
            }
        }
    }
}

// Set text for inventory and victory/defeat game endings.
void Map::SetText()
{
    Map::goldCnt = 0;
    Map::staminaPotionCnt = 0;
    Map::healthPointsCnt = 1;
    if (!Map::inventoryFont.loadFromFile("../resources/fonts/Scary_Serif.ttf")) {
        std::cerr << "An error occured while downloading fonts!" << std::endl;
    }
    Map::textGold.setFont(inventoryFont);
    Map::textGold.setString("Gold");
    Map::textGold.setCharacterSize(24);
    Map::textGold.setFillColor(sf::Color(255, 215, 0));
    Map::textGold.setStyle(sf::Text::Bold);
    Map::textGold.setPosition(812.f, 40+22.f);

    Map::numGold.setFont(inventoryFont);
    Map::numGold.setString(std::to_string(Map::goldCnt));
    Map::numGold.setCharacterSize(58);
    Map::numGold.setFillColor(sf::Color(255, 215, 0));
    Map::numGold.setStyle(sf::Text::Bold);
    Map::numGold.setPosition(952.f, 40+00.f);

    Map::textStamina.setFont(inventoryFont);
    Map::textStamina.setString("Stamina\npotion");
    Map::textStamina.setCharacterSize(24);
    Map::textStamina.setFillColor(sf::Color::Red);
    Map::textStamina.setStyle(sf::Text::Bold);
    Map::textStamina.setPosition(812.f, 40+64.f);

    Map::numStamina.setFont(inventoryFont);
    Map::numStamina.setString(std::to_string(Map::staminaPotionCnt));
    Map::numStamina.setCharacterSize(58);
    Map::numStamina.setFillColor(sf::Color::Red);
    Map::numStamina.setStyle(sf::Text::Bold);
    Map::numStamina.setPosition(952.f, 40+56.f);

    Map::textTotalGoldFound.setFont(inventoryFont);
    Map::textTotalGoldFound.setCharacterSize(60);
    Map::textTotalGoldFound.setFillColor(sf::Color(255, 215, 0));
    Map::textTotalGoldFound.setStyle(sf::Text::Bold);
    Map::textTotalGoldFound.setPosition(116.f, 400.f);

    Map::textDefeat.setFont(inventoryFont);
    Map::textDefeat.setString("You died");
    Map::textDefeat.setCharacterSize(80);
    Map::textDefeat.setFillColor(sf::Color::Red);
    Map::textDefeat.setStyle(sf::Text::Bold);
    Map::textDefeat.setPosition(316.f, 664.f);

    Map::textTimeStaminaPotion.setFont(inventoryFont);
    Map::textTimeStaminaPotion.setCharacterSize(96);
    Map::textTimeStaminaPotion.setFillColor(sf::Color(240, 255, 255));
    Map::textTimeStaminaPotion.setStyle(sf::Text::Bold);
    Map::textTimeStaminaPotion.setPosition(896.f, 336.f);
}

// Perform the initial setup.
void Map::InitGame()
{
    Map::SetText();
    for (size_t cnt = 0; cnt < MAX_HEALTH_POINTS; ++cnt) {
        Map::healthPoints[cnt] = new Tile("../resources/images/heart.png", 812 + (TILE_SIZE + 8) * cnt, 22, TileType::HEART);
        //Map::healthPoints[cnt] = std::move(std::make_unique<Tile>(std::move("../resources/images/heart.png"), 812 + (TILE_SIZE + 8) * cnt, 22, TileType::HEART));
    }
    Map::acceleration = false;
    Map::playerAcceleration = 1.f;
    Map::textureFire.loadFromFile("../resources/images/white.png");
    Map::spriteFire.setTexture(textureFire);
    Map::fireColor_1 = sf::Color(255, 165, 0, 64);
    Map::fireColor_2 = sf::Color(255, 69, 0, 64);
    this->ChangeOpacity(true);
    sf::Event event;
    while (this->window.pollEvent(event));
    this->clockTorch.restart();
    this->clockPlayer.restart();
}

bool Map::is_suitable_tile(const sf::Vector2f &coord, int i, int j, int radius)
{
    return (coord.x + i >= 0) && (coord.x + i <= HOR_TILES) &&
            (coord.y + j >= 0) && (coord.y + j <= VER_TILES) &&
            (i * i + j * j != 0);
}

// Draw the contents of the game screen.
void Map::Draw() const
{
    for (size_t i = 0; i < VER_TILES; ++i) {
        for (size_t j = 0; j < HOR_TILES; ++j) {
            this->window.draw(tiles[i][j]->sprite);
        }
    }
    this->DrawPlayer();
    this->DrawInventory();

    if (Map::acceleration && Map::clockStaminaPotion.getElapsedTime().asMilliseconds() < TIME_ACCELERATION) {
        int time_left = 11 - Map::clockStaminaPotion.getElapsedTime().asSeconds();
        Map::textTimeStaminaPotion.setString(std::to_string(time_left));
        this->window.draw(Map::textTimeStaminaPotion);
    }

    static size_t frame = 0;
    frame = (frame + 1) % 500;
    for (const sf::Vector2f &coord : this->torchCoords) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (Map::is_suitable_tile(coord, i, j, 1) &&
                    this->tiles[coord.x + i][coord.y + j]->tileType != TileType::EMPTY /*
                    && this->tiles[coord.x + i][coord.y + j]->tileType != TileType::TORCH_EMPTY
                    && this->tiles[coord.x + i][coord.y + j]->tileType != TileType::TORCH_FLOOR */) {
                    Map::spriteFire.setPosition(
                            (coord.x + i) * TILE_SIZE,
                            (coord.y + j) * TILE_SIZE);
                    if (((i > 0 ? i : -i)  + (j > 0 ? j : -j)) == 1) {
                        if (frame < 250) {
                            Map::spriteFire.setColor(Map::fireColor_1);
                        } else {
                            Map::spriteFire.setColor(Map::fireColor_2);
                        }
                    } else {
                        if (frame >= 250) {
                            Map::spriteFire.setColor(Map::fireColor_1);
                        } else {
                            Map::spriteFire.setColor(Map::fireColor_2);
                        }
                    }
                    window.draw(Map::spriteFire);
                }
            }
        }
    }
}

// Draw the player tile.
void Map::DrawPlayer() const
{
    this->window.draw(playerTile->sprite);
}

// Draw the inventory.
void Map::DrawInventory() const
{
    this->window.draw(textGold);
    this->window.draw(numGold);
    this->window.draw(textStamina);
    this->window.draw(numStamina);
    for (size_t cnt = 0; cnt < Map::healthPointsCnt; ++cnt) {
        this->window.draw(Map::healthPoints[cnt]->sprite);
    }
}

// Calculate coordinates of the corner points orf the player tile.
void Map::get_player_tile_borders(
        const sf::Vector2f &lu,
        sf::Vector2f &ld,
        sf::Vector2f &ru,
        sf::Vector2f &rd)
{
    ld = lu + sf::Vector2f(0.f, TILE_SIZE - 1.f);
    ru = lu + sf::Vector2f(TILE_SIZE - 1.f, 0.f);
    rd = lu + sf::Vector2f(TILE_SIZE - 1.f, TILE_SIZE - 1.f);
}

// Check for reaching the game exit tile.
bool Map::ReachedGameEnd() const
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    return tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == TileType::GAME_EXIT &&
            tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == TileType::GAME_EXIT &&
            tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == TileType::GAME_EXIT &&
            tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == TileType::GAME_EXIT;
}

// Check for reaching the room exit tile.
bool Map::ReachedRoomExit() const
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    return tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == TileType::ROOM_EXIT &&
            tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == TileType::ROOM_EXIT &&
            tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == TileType::ROOM_EXIT &&
            tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == TileType::ROOM_EXIT;
}

// Check for reaching the trap tile.
bool Map::ReachedTrap() const
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    return tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == TileType::TRAP ||
            tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == TileType::TRAP ||
            tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == TileType::TRAP ||
            tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == TileType::TRAP;
}

// Check for reaching the treasure tile.
bool Map::ReachedTreasure() const
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    return tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == TileType::TREASURE_CLOSED ||
            tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == TileType::TREASURE_CLOSED ||
            tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == TileType::TREASURE_CLOSED ||
            tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == TileType::TREASURE_CLOSED;
}

// Check for reaching the gold pile tile.
bool Map::ReachedGoldPile() const
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    return tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == TileType::GOLD_PILE ||
            tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == TileType::GOLD_PILE ||
            tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == TileType::GOLD_PILE ||
            tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == TileType::GOLD_PILE;
}

// Check for reaching the gold coin tile.
bool Map::ReachedGoldCoin() const
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    return tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == TileType::GOLD_COIN ||
            tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == TileType::GOLD_COIN ||
            tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == TileType::GOLD_COIN ||
            tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == TileType::GOLD_COIN;
}

// Check for reaching the stamina potion tile.
bool Map::ReachedStaminaPotion() const
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    return tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == TileType::STAMINA_POTION ||
            tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == TileType::STAMINA_POTION ||
            tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == TileType::STAMINA_POTION ||
            tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == TileType::STAMINA_POTION;
}

// Check for reaching the health potion tile.
bool Map::ReachedHealthPotion() const
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    return tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == TileType::HEALTH_POTION ||
            tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == TileType::HEALTH_POTION ||
            tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == TileType::HEALTH_POTION ||
            tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == TileType::HEALTH_POTION;
}

// Perform a movement of the player tile.
void Map::MovePlayer(sf::Keyboard::Key key)
{
    sf::Vector2f movement;
    sf::Vector2f old = this->playerTile->sprite.getPosition();
    switch (key) {
    case sf::Keyboard::W:
        movement = sf::Vector2f(0, -PLAYER_SPEED);
        break;
    case sf::Keyboard::A:
        movement = sf::Vector2f(-PLAYER_SPEED, 0);
        break;
    case sf::Keyboard::S:
        movement = sf::Vector2f(0, PLAYER_SPEED);
        break;
    case sf::Keyboard::D:
        movement = sf::Vector2f(PLAYER_SPEED, 0);
        break;
    default:
        break;
    }
    movement *= Map::playerAcceleration;
    sf::Vector2f lu = this->playerTile->sprite.getPosition() + movement;
    sf::Vector2f ld, ru, rd;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    TileType tt1, tt2;
    switch (key) {
    case sf::Keyboard::W:
        tt1 = this->tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType;
        tt2 = this->tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType;
        if (!(lu.y >= 0.f && Tile::MOVABLE.count(tt1) && Tile::MOVABLE.count(tt2))) {
            movement = sf::Vector2f(0.f, 0.f);
        }
        break;
    case sf::Keyboard::A:
        tt1 = this->tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType;
        tt2 = this->tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType;
        if (!(lu.x >= 0.f && Tile::MOVABLE.count(tt1) && Tile::MOVABLE.count(tt2))) {
            movement = sf::Vector2f(0.f, 0.f);
        }
        break;
    case sf::Keyboard::S:
        tt1 = this->tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType;
        tt2 = this->tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType;
        if (!(rd.y <= WINDOW_HEIGHT && Tile::MOVABLE.count(tt1) && Tile::MOVABLE.count(tt2))) {
            movement = sf::Vector2f(0.f, 0.f);
        }
        break;
    case sf::Keyboard::D:
        tt1 = this->tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType;
        tt2 = this->tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType;
        if (!(rd.x <= WINDOW_WIDTH && Tile::MOVABLE.count(tt1) && Tile::MOVABLE.count(tt2))) {
            movement = sf::Vector2f(0.f, 0.f);
        }
        break;
    default:
        break;
    }

    this->playerTile->sprite.move(movement);
}

// Read the maze matrix from the file.
std::vector<std::vector<Map>> Map::CreateGame(sf::RenderWindow &window)
{
    std::vector<std::vector<Map>> game;
    std::ifstream file("../resources/maze/maze.txt");
    std::string line;
    Map::totalNumGold = 0;
    Map::gameRow = 0;
    Map::gameCol = 0;
    while (getline(file, line)) {
        std::vector<Map> game_line;
        for (char level : line) {
            game_line.emplace_back(Map(window, level));
            //game_line.push_back(Map(window, level));
        }
        game.emplace_back(game_line);
        //game.push_back(game_line);
    }
    return game;
}

// Fade in/out.
void Map::ChangeOpacity(bool from_0_to_255)
{
    sf::Color colors[HOR_TILES][VER_TILES];

    for (size_t i = 0; i < VER_TILES; ++i) {
        for (size_t j = 0; j < HOR_TILES; ++j) {
            colors[i][j] = this->tiles[i][j]->sprite.getColor();
        }
    }

    if (from_0_to_255) {
        for (size_t opacity = 0; opacity != 256; ++opacity) {
            this->window.clear();

            for (size_t i = 0; i < VER_TILES; ++i) {
                for (size_t j = 0; j < HOR_TILES; ++j) {
                    colors[i][j].a = opacity;
                    this->tiles[i][j]->sprite.setColor(colors[i][j]);
                    this->window.draw(tiles[i][j]->sprite);
                }
            }

            this->window.display();
            sf::sleep(sf::milliseconds(1));
        }
    } else {
        for (size_t opacity = 255; opacity != 0; --opacity) {
            this->window.clear();

            for (size_t i = 0; i < VER_TILES; ++i) {
                for (size_t j = 0; j < HOR_TILES; ++j) {
                    colors[i][j].a = opacity;
                    this->tiles[i][j]->sprite.setColor(colors[i][j]);
                    this->window.draw(tiles[i][j]->sprite);
                }
            }

            this->window.display();
            sf::sleep(sf::milliseconds(1));
        }
        for (size_t i = 0; i < VER_TILES; ++i) {
            for (size_t j = 0; j < HOR_TILES; ++j) {
                colors[i][j].a = 255;
                this->tiles[i][j]->sprite.setColor(colors[i][j]);
            }
        }
    }
}

// Use a stamina potion to increase player speed.
void Map::UseStaminaPotion()
{
    Map::acceleration = true;
    Map::playerAcceleration = 2.f;
    Map::DecreaseStaminaPotionCnt();
    Map::clockStaminaPotion.restart();
}

// Move to the next room.
void Map::ChangeRoom(Map &room)
{
    sf::Vector2f coord_player = room.playerTile->sprite.getPosition();
    if (coord_player.x == 0) {
        --Map::gameCol;
    } else if (coord_player.x == WINDOW_WIDTH - TILE_SIZE) {
        ++Map::gameCol;
    } else if (coord_player.y == 0) {
        --Map::gameRow;
    } else if (coord_player.y == WINDOW_HEIGHT - TILE_SIZE) {
        ++Map::gameRow;
    }
    room.playerTile->sprite.setPosition(room.coordStart);
}

// Finish the game in case of victory/death.
void Map::FinishGame(TileType tile_type)
{
    switch(tile_type) {
    case TileType::GAME_EXIT:
        this->ChangeOpacity(false);
        this->window.draw(Tile("../resources/images/victory.png", 211.5, 122.5, TileType::GAME_EXIT).sprite);
        Map::textTotalGoldFound.setString(
                "    Congratulations!\nYou found " + std::to_string(Map::goldCnt) +
                "/" + std::to_string(Map::totalNumGold) + " gold!");
                this->window.draw(Map::textTotalGoldFound);
        break;
    case TileType::TRAP:
    {
        sf::Vector2f coord = playerTile->sprite.getPosition();
        //std::unique_ptr<Tile> blood1 = std::move(std::make_unique<Tile>(std::move("../resources/images/blood_1.png"), coord.x, coord.y + TILE_SIZE, TileType::BLOOD));
        //std::unique_ptr<Tile> blood2 = std::move(std::make_unique<Tile>(std::move("../resources/images/blood_2.png"), coord.x, coord.y + TILE_SIZE, TileType::BLOOD));
        Tile *blood1 = new Tile("../resources/images/blood_1.png", coord.x, coord.y + 16.f, TileType::BLOOD);
        Tile *blood2 = new Tile("../resources/images/blood_2.png", coord.x, coord.y + 16.f, TileType::BLOOD);
        for (size_t frame_death = 0; frame_death < 10; ++frame_death) {
            this->playerTile->SetSprite(
                    "../resources/animation/player/die/hero_die_" +
                    std::to_string(frame_death) +
                    ".png");
            this->window.clear();
            this->Draw();
            if (frame_death < 5) {
                this->window.draw(blood1->sprite);
            } else {
                this->window.draw(blood2->sprite);
            }
            this->window.display();
            sf::sleep(sf::milliseconds(150));
        }
        delete blood1;
        delete blood2;
        this->ChangeOpacity(false);
        this->window.draw(Tile("../resources/images/defeat.png", 152, 24, TileType::TRAP).sprite);
        this->window.draw(textDefeat);
        break;
    }
    default:
        break;
    }
    this->window.display();
    sf::sleep(sf::seconds(3));
    this->window.close();
}

// Update amount of gold.
void Map::IncreaseGoldCnt(size_t increase)
{
    Map::goldCnt += increase;
    Map::numGold.setString(std::to_string(Map::goldCnt));
}

// Update amount of stamina potions.
void Map::IncreaseStaminaPotionCnt()
{
    Map::numStamina.setString(std::to_string(++Map::staminaPotionCnt));
}

// Decrease amount of stamina potions.
void Map::DecreaseStaminaPotionCnt()
{
    Map::numStamina.setString(std::to_string(--Map::staminaPotionCnt));
}

// Update amount of health points.
void Map::IncreaseHealthPointsCnt()
{
    ++Map::healthPointsCnt;
}

// Decrease amount of health points and finish the game if all health points are used.
void Map::DecreaseHealthPointsCnt(Map &game)
{
    if (--Map::healthPointsCnt == 0) {
        game.FinishGame(TileType::TRAP);
    }
}

// Pick up an object, i.e gold or stamina potion.
void Map::PickUpObject(TileType tile_type, bool is_treasure)
{
    sf::Vector2f lu = playerTile->sprite.getPosition();
    sf::Vector2f ld, ru, rd;
    sf::Vector2f object_pos;
    Map::get_player_tile_borders(lu, ld, ru, rd);
    if (this->tiles[lu.x / TILE_SIZE][lu.y / TILE_SIZE]->tileType == tile_type) {
        object_pos = lu;
    } else if (this->tiles[ld.x / TILE_SIZE][ld.y / TILE_SIZE]->tileType == tile_type) {
        object_pos = ld;
    } else if (this->tiles[ru.x / TILE_SIZE][ru.y / TILE_SIZE]->tileType == tile_type) {
        object_pos = ru;
    } else if (this->tiles[rd.x / TILE_SIZE][rd.y / TILE_SIZE]->tileType == tile_type) {
        object_pos = rd;
    }
    delete this->tiles[object_pos.x / TILE_SIZE][object_pos.y / TILE_SIZE];
    int coord_x = object_pos.x - static_cast<int>(object_pos.x) % TILE_SIZE;
    int coord_y = object_pos.y - static_cast<int>(object_pos.y) % TILE_SIZE;
    if (is_treasure) {
        this->tiles[object_pos.x / TILE_SIZE][object_pos.y / TILE_SIZE] =
                new Tile(
                        "../resources/images/treasure_opened.png",
                        coord_x,
                        coord_y,
                        TileType::TREASURE_OPENED);
        /*
        this->tiles[object_pos.x / TILE_SIZE][object_pos.y / TILE_SIZE] =
                std::move(std::make_unique<Tile>(
                        std::move("../resources/images/treasure_opened.png"),
                        coord_x,
                        coord_y,
                        TileType::TREASURE_OPENED));
        */
    } else {
        this->tiles[object_pos.x / TILE_SIZE][object_pos.y / TILE_SIZE] =
                new Tile(
                            "../resources/images/floor.png",
                            coord_x,
                            coord_y,
                            TileType::FLOOR);
        /*
        this->tiles[object_pos.x / TILE_SIZE][object_pos.y / TILE_SIZE] =
                std::move(std::make_unique<Tile>(
                            std::move("../resources/images/floor.png"),
                            coord_x,
                            coord_y,
                            TileType::FLOOR));
        */
    }
}

// Check if the user can pick up another health potion.
bool Map::CanPickUpHealthPotion() {
    return Map::healthPointsCnt < MAX_HEALTH_POINTS;
}
