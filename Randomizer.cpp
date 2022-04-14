#include "Randomizer.h"

double Randomizer::generateRandomDouble(double min, double max) {

    std::random_device rd;

    uint64_t entropy_from_time =
            std::chrono::high_resolution_clock::now().time_since_epoch().count();

    std::seed_seq seeder{
            rd(),
            static_cast<uint32_t>(entropy_from_time),
            static_cast<uint32_t>(entropy_from_time >> 32),
    };

    std::mt19937 gen(seeder);
    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

int Randomizer::generateRandomInt(int min, int max) {

    return floor(generateRandomDouble(min, max));
}

bool Randomizer::generateRandomBool() {
    return generateRandomDouble(0.0,2.0) > 1
}