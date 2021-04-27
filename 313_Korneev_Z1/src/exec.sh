g++ -c main.cpp
g++ main.o -o app -O2 -Wall -Werror -Wextra -pedantic -lsfml-graphics -lsfml-window -lsfml-system
./app
rm -rf main.o app
