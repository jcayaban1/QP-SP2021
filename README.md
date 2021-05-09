# QP-SP2021
Spring 2021 Quarterly Project

How to run physics engine on macOS terminal:
g++ QP_physics.cpp -c Game.cpp -c Player.cpp -c
g++ QP_physics.o Game.o Player.o -lsfml-graphics -lsfml-window -lsfml-system -o physics
./physics
