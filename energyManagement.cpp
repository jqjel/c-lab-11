#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Plant {
  string type;         // either 1, 2, or 3
  string id;        // 4 alphanumeric characters
  double output;    // % of charge, between 0 and 1
  double max_output;
  bool isOnline;
};

double electricity_total(vector<Plant> &plants) {
    double total = 0.0;
    for (size_t i = 0; i < plants.size(); ++i) {
        if (plants[i].isOnline) {
            total += plants[i].output;
        }
    }
    return total;
}

double desirability(const Plant &plant) {
    double weight_additional = 0.0;
    double weight_factor = 0.0;
    double max_capacity = 0.0;
    double current_power = 0.0;

    if (plant.type == "Storage") {
        weight_factor = 8.3;
    }
    else if (plant.type == "Gas") {
        weight_factor = 2.1;
    }
    else {
        weight_factor = 0.9;
    }

    if (plant.isOnline == true) {
        weight_factor = weight_factor * 2;
    }

    current_power = plant.output;
    max_capacity = plant.max_output;

    weight_additional = weight_factor * (max_capacity - current_power);
    return weight_additional;
}

/*void printPlant(const Rover &rover, ostream &output) {
  output << "Type " << rover.type;
  output << " Rover #" << rover.id; 
  output << " (" << (rover.charge * 100) << "%)";
  output << " carrying " << rover.capacity << "kg. ";
}


void printPlants(const vector<Rover> &fleet, ostream &output){

  // traverse the fleet vector
  for (size_t i = 0; i < fleet.size(); ++i) {
    printRover(fleet.at(i),output); // use helper function to print a single rover
    output << endl; // go to a newline after this rover is printed
  }
}
*/

void loadPlants(vector<Plant> &plants, istream &PlantDataInput){
    Plant plant;
    while (PlantDataInput >> plant.type >> plant.id >> plant.output >> plant.max_output >> plant.isOnline) {
        plants.push_back(plant);
  }
}


int bestPlant(const vector<Plant> &plants, double charge_required){
    
    if (plants.empty()) {
        return -1; 
    }
    int bestIndex = -1;
    for (size_t i = 0; i < plants.size(); ++i) {


        double chargeIncrease = plants[i].max_output - plants[i].output;
        if (chargeIncrease > 25 && chargeIncrease < charge_required) {

            if (bestIndex == -1) {
                bestIndex = i;
            }
            else if (desirability(plants[i]) > desirability(plants[bestIndex])) {
                bestIndex = i;
            }

        }
    }
    return bestIndex; 
}


 

void selectPlants(vector<Plant> &plants, double energy_required) {
    while (energy_required > electricity_total(plants)) {
        int bestIndex = bestPlant(plants, energy_required - electricity_total(plants));
        if (bestIndex != -1) { 
            plants[bestIndex].isOnline = true;
            plants[bestIndex].output = plants[bestIndex].max_output;
        } 
        else { 
            return;
        } 
    } 
} 



void printConclusion(const vector<Plant> &plants) {
  
  int numSelected = 0;
  for(size_t i = 0; i < plants.size(); ++i) {
    if (plants[i].isOnline) {
      ++numSelected;
    }
  }
  cout << numSelected << " plants now online:" << endl;
  
  for(size_t i = 0; i < plants.size(); ++i) {
    if (plants[i].isOnline) {
      cout << "    " << plants[i].id << " - " <<plants[i].output << " MW-H" <<endl;
    }
  }
}

int main() {

    vector<Plant> plants;
    ifstream fIn("current_electricity_generation.txt");
  
    if(!fIn.is_open()) {
    cout << "error opening file!" << endl;
  }

    loadPlants(plants, fIn);
    cout << "Current energy production: " << endl;
    printConclusion(plants);

    cout << "Total energy production is " << electricity_total(plants) << " MW-H." << endl;


    double energy_required = 0.0;
    cout << "How many megawatt-hours (MW-H) does the grid need to provide right now? ";
    cin >> energy_required;

    selectPlants(plants, energy_required);

    cout << "New energy production: " << endl;
    printConclusion(plants);
    cout << "Total energy production is " << electricity_total(plants) << " MW-H." << endl;


/*
  fIn.close();

  cout << "This is what is in fleet: " << endl;
  printFleet(fleet,cout);


  Rover testRover = {1, "test", 1.0, 100, false};
  cout << "desirability of test rover: " ;
  cout << desirability(testRover) << endl; // should print 1000

  cout << "desirability of second rover in fleet: " ;
  cout << desirability(fleet.at(1)) << endl; // should print 250
  cout << desirability(fleet.at(4)) << endl;
  printRover(testRover,cout);
*/
}

