#include <iostream>
#include <vector>

using namespace std;

struct Orchard {
  int year;     // The year the orchard was established
  string id;    // The orchard's ID
  string type;  // The type of fruit grown
  int num;      // The number of fruit harvested last year
};

int main() {

  // Create some orchard data
  Orchard sector1 = {1954, "A13", "bartlett pear", 12980};
  Orchard sector2 = {2002, "B05", "gala apple", 3492};
  Orchard sector3 = {1983, "A65", "tart cherry", 35211};

  // Put the data into a vector
  vector <Orchard> allOrchards;
  allOrchards.push_back(sector1);
  allOrchards.push_back(sector2);
  allOrchards.push_back(sector3);

  // Print out the type and number for all sectors
  for (int i = 0; i < allOrchards.size(); ++i) {
      cout << "type:   " << allOrchards[i].type << endl;
      cout << "number: " << allOrchards[i].num << endl;
      cout << endl;
  }

}