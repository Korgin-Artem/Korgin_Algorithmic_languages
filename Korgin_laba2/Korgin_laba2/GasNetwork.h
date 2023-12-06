#pragma once
#include "Pipe.h"
#include "CompressorStation.h"

class GasNetwork {
public:
    void connectPipesToStations(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations);
};
