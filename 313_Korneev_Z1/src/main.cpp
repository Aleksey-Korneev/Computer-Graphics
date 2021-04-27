#include <SFML/Graphics.hpp>
#include "map.cpp"
#include "tile.cpp"

int main()
{
    sf::RenderWindow window(
            sf::VideoMode(WINDOW_WIDTH + INVENTORY_WIDTH, WINDOW_HEIGHT),
            "Korneev Aleksey, 313 CMC MSU." /*,
            sf::Style::Close | sf::Style::Titlebar */);
    std::vector<std::vector<Map>> game = Map::CreateGame(window);
    game[Map::gameRow][Map::gameCol].InitGame();

    while (window.isOpen())
    {
        game[Map::gameRow][Map::gameCol].ProcessTimeEvents();

        sf::Event event;
        while (window.pollEvent(event))
        {
            game[Map::gameRow][Map::gameCol].ProcessEvent(event);
            game[Map::gameRow][Map::gameCol].Check();
            if (game[Map::gameRow][Map::gameCol].ReachedRoomExit()) {
                game[Map::gameRow][Map::gameCol].ChangeOpacity(false);
                Map::ChangeRoom(game[Map::gameRow][Map::gameCol]);
                game[Map::gameRow][Map::gameCol].ChangeOpacity(true);
                while (window.pollEvent(event));
            }
        }

        window.clear();
        game[Map::gameRow][Map::gameCol].Draw();
        window.display();
    }

    return 0;
}
