#pragma once
#include <string>

class Root {
public:
    explicit Root(double depthCm, std::string type = "taproot");
    double getDepth() const;
    const std::string& getType() const;
    double waterAbsorptionRate() const;
    std::string describe() const;
private:
    double depthCm_;
    std::string type_;
};
