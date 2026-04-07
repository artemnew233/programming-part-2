#include "../public/Engine.h"
#include <iostream>

Engine::Engine(int hp, const std::string& t) : horsepower(hp), type(t), running(false) {}

void Engine::start() {
    running = true;
    std::cout << "Engine started (" << horsepower << " HP " << type << ")" << std::endl;
}

void Engine::stop() {
    running = false;
    std::cout << "Engine stopped." << std::endl;
}

int Engine::getHorsepower() const { return horsepower; }
std::string Engine::getType() const { return type; }
bool Engine::isRunning() const { return running; }
