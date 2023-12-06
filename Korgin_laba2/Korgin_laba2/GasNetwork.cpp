#include <iostream>
#include "Get_Correct.cpp"
#include "GasNetwork.h"

void GasNetwork::connectPipesToStations(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations) {
    if (pipes.size() != 0 && stations.size() != 0) {
        int in_id, out_id, pipe_diameter;

        std::cout << "Enter the ID of the input compressor station: ";
        in_id = get_correct_value<int>(1, INT_MAX);

        std::cout << "Enter the ID of the output compressor station: ";
        out_id = get_correct_value<int>(1, INT_MAX);

        pipe_diameter = get_correct_diameter();

        bool pipe_found = false;
        for (auto& [id, pipe] : pipes) {
            if (pipe.diameter == pipe_diameter && pipe.getIdCSOfTheEntrance() == 0 && pipe.getIdCSOfTheExit() == 0) {
                pipe.connecting_with_cs(in_id, out_id);
                pipe_found = true;
                break;
            }
        }

        if (!pipe_found) {
            std::cout << "The pipe with the entered diameter does not exist! Create a pipe.\n";
            Pipe pipe;
            pipe.read();
            //pipe.diameter = pipe_diameter;
            pipe.connecting_with_cs(in_id, out_id);
            pipes.insert(make_pair(pipe.getid(), pipe));
        }

        stations[in_id].connecting_with_pipes();

        std::cout << "Pipe connected successfully.\n";
    } else {
        std::cout << "Insufficient data to establish connections.\n";
    }
}
