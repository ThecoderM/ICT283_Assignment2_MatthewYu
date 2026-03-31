#include <iostream>
#include <fstream>
#include <iomanip>
#include "WeatherLog.h"
#include "UserInterface.h"


using std::cout;
using std::endl;


int main()

{
    WeatherLog WeathLog; // Create WeatherLog object to store dataset records
    // Load dataset based on filename stored inside data/data_source.txt (handled by WeatherLog)
    if (!WeathLog.LoadData("data_source.txt")) // Attempt to load dataset
    {
        cout << "Error: could not load file data_source.txt" << endl;
        return 1;
    }

    UserInterface::RunMenu(WeathLog); // Start menu once data is loaded
    return 0;


}





