#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <thread>
#include <chrono>

std::map<std::string, double> costs;
std::map<char, int> roomGold;

void initializeCosts() {
    costs["AB"] = 2 + 3 * 4 - 5 / 10.0 + pow(5, 2);
    costs["AC"] = pow(2, 3) + 4 * 5 - 6 / 10.0 + 1;
    costs["BC"] = 5 * 4 - 2 + pow(5, 2) - 7;
    costs["BD"] = 3 + 4 * 5 - 8 / 2.0 + 1;
    costs["CD"] = pow(3, 3) + 8 - 5 * 3 + 8;
}

void initializeRoomGold() {
    roomGold['A'] = 40;
    roomGold['B'] = 50;
    roomGold['C'] = 75;
    roomGold['D'] = 100;
}

int traverseMaze(const std::vector<char>& route, int gold) {
    int totalGold = gold;

    std::cout << "\nTrying route: ";
    for (char c : route) std::cout << c << " ";
    std::cout << "\nStarting gold: " << totalGold << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    for (size_t i = 0; i < route.size() - 1; i++) {
        char currentRoom = route[i];
        char nextRoom = route[i + 1];
        std::string path = std::string(1, std::min(currentRoom, nextRoom)) + std::max(currentRoom, nextRoom);
        int pathCost = std::ceil(costs[path]);

        std::cout << "\nMoving from " << currentRoom << " to " << nextRoom << ". Path cost: " << pathCost << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        if (totalGold < pathCost) {
            std::cout << "Not enough gold to proceed!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            return 0;
        }

        totalGold -= pathCost;
        std::cout << "Paid " << pathCost << " gold. Remaining gold: " << totalGold << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        totalGold += roomGold[nextRoom];
        std::cout << "Collected " << roomGold[nextRoom] << " gold from room " << nextRoom << ". New total: " << totalGold << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    return totalGold;
}

int main() {
    initializeCosts();
    initializeRoomGold();

    std::vector<std::vector<char>> possibleRoutes = {
        {'A', 'B', 'D'},
        {'A', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'C', 'B', 'D'}
    };

    int maxGold = 0;
    std::vector<char> optimalRoute;

    for (const auto& route : possibleRoutes) {
        int gold = traverseMaze(route, 40);
        std::cout << "\nRoute ";
        for (char c : route) std::cout << c << " ";
        std::cout << "finished with " << gold << " gold" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        if (gold > maxGold) {
            maxGold = gold;
            optimalRoute = route;
        }
    }

    std::cout << "\nOptimal route: ";
    for (char c : optimalRoute) std::cout << c;
    std::cout << "\nMaximum gold: " << maxGold << std::endl;

    return 0;
}