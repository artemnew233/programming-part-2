#ifndef ENGINE_H
#define ENGINE_H

#include <string>

class Engine {
public:
    Engine(int horsepower, const std::string& type);
    void start();
    void stop();
    int getHorsepower() const;
    std::string getType() const;
    bool isRunning() const;

private:
    int horsepower;
    std::string type;
    bool running;
};

#endif
