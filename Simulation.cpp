//Standard libraries to be used
#include <iostream>
#include <vector> 
#include <random>
using namespace std; //We put std into the global namespace to improve readability in some parts of the code.


int main() {
    //For random number generation
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> random(1, 1000);

    //Initializing the simulation
    int mHistory[50];
    int aHistory[50];
    vector<bool> creatures;
    vector<bool> newCreatures; //newCreatures is to contain the updated values, but is to not be read while iterating organisms.
    vector<float> food;
    creatures.push_back(false);
    food.push_back(0.0f);

    //Looping 20 generations
    int i;
    int j;
    int size;
    for (int g = 0;g < 50;g++) {
        //Allocating 500 food evenly to creatures
        for (i = 0;i < creatures.size();i++)
            food[i] = (float)500 / (float)creatures.size();

        //Applying stealing functionality to aggressors
        for (i = 0;i < creatures.size();i++) {
            if (creatures[i]) {
                int target = (random(rng) % creatures.size()); //Picking another creature at random
                if (creatures[target])   //If the selected creature is aggressive also
                    food[i] = 0; //The aggressive selecting creature dies, but since it is difficult and messy to remove an item from a vector we set the food to 0 as that is equivalent.
                else { //If the selected creature is meek
                    food[i] += food[target]; //Stealing food from the selected creature
                    food[target] = 0;
                }
            }
        }

        //Reproducing creatures according to food. Also possible mutations may happen
        for (i = 0;i < creatures.size();i++) {
            for (j = 0;j < food[i];j++) {
                if (random(rng) == 1) // 1 in 1000 chance of mutation.
                    newCreatures.push_back(not creatures[i]); //Passing the opposite behavioral characteristic as if by mutation
                else
                    newCreatures.push_back(creatures[i]); //Passing the same behavior characteristic as if by passing on genes.
            }
            //Applying the decimal value as a percentage of one more offspring.
            if (random(rng) < (food[i] - j) * 1000) {
                //Same reproduction code is applied as before.
                if (random(rng) == 1)
                    newCreatures.push_back(not creatures[i]);
                else
                    newCreatures.push_back(creatures[i]);
            }

        }

        //Replacing creatures with newCreatures, and adjusting food spaces that it is the same size as the creatures for the next generation.
        for (i = newCreatures.size();i < creatures.size();i++) { //If the overall size of creatures is more than newCreatures, we remove
            creatures.pop_back();                    //the extra values because those will not be overwritten by the next loop.
            food.pop_back();
        }

        for (i = 0;i < newCreatures.size();i++) { //We replace creatures with the values of new creatures
            if (creatures.size() <= i) {
                creatures.push_back(newCreatures[i]);
                food.push_back(0);
            }
            else {
                creatures[i] = newCreatures[i];
            }
        }
        size = newCreatures.size(); //This is a reference for the next loop as the number of creatures will be altered and affect the loop conditions.
        for (i = 0;i < size;i++) {
            newCreatures.pop_back();
        }

        //Recording the number of meek and aggressive creatures on two arrays to be outputted at the end of the simulation
        mHistory[g] = aHistory[g] = 0;
        for (i = 0;i < creatures.size();i++) {
            if (creatures[i]) {
                aHistory[g] += 1;
            }
            else
                mHistory[g] += 1;
        }
    }
    //Outputting the history of the simulation as raw data.
    for (i = 0;i < 50;i++) {
        cout << mHistory[i] << " " << aHistory[i] << endl;
    }
    system("PAUSE"); return 0;
}



