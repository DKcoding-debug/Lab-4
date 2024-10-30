/*
	Delvis Kouete
	Computer Science Fall 2024
	Due: Oct. 22, 2024
	Lab 4, Lab 4 Temperature Output
	Design and write a C++ program that inputs a series of hourly temperature
	from a file, and outputs a bar chart (using stars) of the temperatures.
	*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iomanip>

class TemperatureBarChart {
public:
    // Constructor to initialize temperatures
    TemperatureBarChart(const std::string& filename) {
        readTemperaturesFromFile(filename);
    }

    // Function to display the bar chart
    void displayBarChart() const {
        std::cout << "Hourly Temperature Bar Chart (Each '*' represents 3 degrees)\n";
        std::cout << "Temperature (°F) | Bar\n";
        std::cout << "------------------|------------------------------\n";

        for (const auto& temp : temperatures) {
            if (isValidTemperature(temp)) {
                std::cout << std::setw(16) << temp << " | " << getBar(temp) << '\n';
            }
            else {
                std::cerr << "Error: Invalid temperature " << temp << "°F\n";
            }
        }
    }

private:
    std::vector<int> temperatures;

    // Reads temperatures from a file and stores them in a vector
    void readTemperaturesFromFile(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        int temp;
        while (infile >> temp) {
            if (isValidTemperature(temp)) {
                temperatures.push_back(temp);
            }
            else {
                std::cerr << "Warning: Skipping invalid temperature " << temp << "°F\n";
            }
        }
    }

    // Validates the temperature value
    bool isValidTemperature(int temp) const {
        return (temp >= -30 && temp <= 120);
    }

    // Returns a string representing the bar
    std::string getBar(int temp) const {
        int numStars = temp / 3; // Each star represents 3 degrees
        return std::string(numStars, '*'); // Create a string with 'numStars' stars
    }
};

int main() {
    try {
        // Create an instance of TemperatureBarChart
        TemperatureBarChart chart("temperature.txt");
        chart.displayBarChart();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

