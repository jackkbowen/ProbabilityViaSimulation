/* =============================================================
# You may define helper functions, but DO NOT MODIFY
# the parameters or names of the provided functions.
# =============================================================
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <random>

using namespace std;

/*
The data for this problem is provided in pokemon.txt and follows the
following format.
Col 1: pokemon_id: A unique identifier for the Pokemon.
Col 2: is_legendary: A 1 if the Pokemon is legendary, and 0 otherwise.
Col 3: height: The height of the Pokemon in meters.
Col 4: weight: The weight of the Pokemon in kilograms.
Col 5: encounter_prob: The probability of encountering this Pokemon 
in the wild grass. Note the sum of this entire column is 1, since when
you make an encounter, exactly one of these Pokemon appears.
Col 6: catch_prob: Once you have encountered a Pokemon, the probability 
you catch it. (Ignore any mechanics of the actual game if you've played 
a Pokemon game in the past.)
*/

float* part_a(char* filename){
    /*
    Compute the proportion of Pokemon that are legendary, the average
    height, the average weight, the average encounter_prob, and average 
    catch_prob. 
    :param filename: The path to the file as described in the pset.
    :return: An array of length 5 with these 5 quantities.
    */
    ifstream inFile(filename);

    int pokemon_id[25];
    int is_legendary[25];
    float Plegendary;
    float height[25]; 
    float avgHeight;
    float weight[25];
    float avgWeight;
    float encounter_prob[25];
    float avgEncounter;
    float catch_prob[25];
    float avgCatch;

    for (int i = 0; i < 25; i++)
    {
        inFile >> pokemon_id[i] >> is_legendary[i] >> height[i] >> weight[i] >> encounter_prob[i] >> catch_prob[i];
    }

    for (int i = 0; i < 25; i++)
    {
        Plegendary += is_legendary[i];
        avgHeight += height[i];
        avgWeight += weight[i];
        avgEncounter += encounter_prob[i];
        avgCatch += catch_prob[i];
    }
    static float avg[5];
    avg[0] = Plegendary/(float)25;
    avg[1] = avgHeight/(float)25;
    avg[2] = avgWeight/(float)25;
    avg[3] = avgEncounter/(float)25;
    avg[4] = avgEncounter/(float)25;

    return avg;
}


float* part_b(char* filename){
    /*
    Compute the proportion of Pokemon that are legendary, the average
    height, the average weight, the average encounter_prob, and average 
    catch_prob OF ONLY those Pokemon STRICTLY heavier than the median weight. 
    :param filename: The path to the file as described in the pset.
    :return: A numpy array of length 5 with these 5 quantities.
    */

    ifstream inFile(filename);

    int pokemon_id[25];
    int is_legendary[25];
    float Plegendary;
    float height[25]; 
    float avgHeight = 0;
    float weight[25];
    float avgWeight = 0;
    float encounter_prob[25];
    float avgEncounter = 0;
    float catch_prob[25];
    float avgCatch = 0;

    for (int i = 0; i < 25; i++)
    {
        inFile >> pokemon_id[i] >> is_legendary[i] >> height[i] >> weight[i] >> encounter_prob[i] >> catch_prob[i];
    }

    for (int i = 0; i < 25; i++)
    {
        if (weight[i] > 10.9318)
        {
            Plegendary += is_legendary[i];
            avgHeight += height[i];
            avgWeight += weight[i];
            avgEncounter += encounter_prob[i];
            avgCatch += catch_prob[i];
        }
    }
    static float avg[5];
    avg[0] = Plegendary/(float)12;
    avg[1] = avgHeight/(float)12;
    avg[2] = avgWeight/(float)12;
    avg[3] = avgEncounter/(float)12;
    avg[4] = avgEncounter/(float)12;

    return avg;
    
}


float part_c(char* filename, int ntrials=5000){
    /*
    Suppose you are walking around the wild grass, and you wonder: how
    many encounters do you expect to make until you ENCOUNTER each Pokemon 
    (at least) once? 
    :param filename: The path to the file as described in the pset.
    :param ntrials: How many simulations to run.
    :return: The (simulated) average number of ENCOUNTERS you expect to 
    make, until you ENCOUNTER each Pokemon (at least) once.
    Hint(s): You only need to use one of the columns for this part!
    */
    ifstream inFile(filename);

    int pokemon_id[25];
    int is_legendary[25];
    float Plegendary;
    float height[25]; 
    float avgHeight = 0;
    float weight[25];
    float avgWeight = 0;
    float encounter_prob[25];
    float avgEncounter = 0;
    float catch_prob[25];
    float avgCatch = 0;

    float numEncounters[25] = {};
    int avgEncounters = 0;
    float randomNum;
    vector<int> tracker;
    

    for (int i = 0; i < 25; i++)
    {
        inFile >> pokemon_id[i] >> is_legendary[i] >> height[i] >> weight[i] >> encounter_prob[i] >> catch_prob[i];
    }

    const int nrolls = ntrials;
    const int nstars = 25;
    default_random_engine generator;
    discrete_distribution<int> distribution {encounter_prob[0] * 10000, encounter_prob[1] * 10000, encounter_prob[2] * 10000, encounter_prob[3] * 10000, encounter_prob[4] * 10000, encounter_prob[5] * 10000, encounter_prob[6] * 10000, encounter_prob[7] * 10000, encounter_prob[8] * 10000, encounter_prob[9] * 10000, encounter_prob[10] * 10000, encounter_prob[11] * 10000, encounter_prob[12] * 10000, encounter_prob[13] * 10000, encounter_prob[14] * 10000, encounter_prob[15] * 10000, encounter_prob[16] * 10000, encounter_prob[17] * 10000, encounter_prob[18] * 10000, encounter_prob[19] * 10000, encounter_prob[20] * 10000, encounter_prob[21] * 10000, encounter_prob[22] * 10000, encounter_prob[23] * 10000, encounter_prob[24] * 10000};

    for (int n = 0; n < ntrials; n++)
    {
        while (tracker.size() != 25)
        {
            int numPokemon = distribution(generator);
            avgEncounters++;

            //cout << "tracker size" << tracker.size() << endl;

            if (tracker.size() == 0)
                tracker.push_back(numPokemon);

            //cout << "Num Pokemon " << numPokemon << endl; 

            for (int i = 0; i < tracker.size(); i++)
            {
                if ((i == tracker.size() - 1) && tracker.at(i) != numPokemon)
                {
                    tracker.push_back(numPokemon);
                }

                if (tracker.at(i) == numPokemon)
                {
                    //cout << "Found Pokemon Num " << numPokemon << " and in tracker " << tracker.at(i) << endl;
                    break;
                }
            }
        }
        tracker.clear();
    }

    return avgEncounters/ntrials;
    
}


float part_d(char* filename, int ntrials=5000){
    /*
    Suppose you are walking around the wild grass, and you wonder: how
    many encounters do you expect to make until you CATCH each Pokemon 
    (at least) once? 
    :param filename: The path to the file as described in the pset.
    :param ntrials: How many simulations to run.
    :return: The (simulated) average number of ENCOUNTERS you expect to 
    make, until you CATCH each Pokemon (at least) once.
    Hint(s):
    1. You only need to use two of the columns for this part!
    2. You may want to use rand(...).
    */
    ifstream inFile(filename);

    int pokemon_id[25];
    int is_legendary[25];
    float Plegendary;
    float height[25]; 
    float avgHeight = 0;
    float weight[25];
    float avgWeight = 0;
    float encounter_prob[25];
    float avgEncounter = 0;
    float catch_prob[25];
    

    float numCatches[25] = {};
    int avgCatch = 0;
    float randomNum;
    vector<int> tracker;
    

    for (int i = 0; i < 25; i++)
    {
        inFile >> pokemon_id[i] >> is_legendary[i] >> height[i] >> weight[i] >> encounter_prob[i] >> catch_prob[i];
    }

    const int nrolls = ntrials;
    const int nstars = 25;
    int avgCatches;
    default_random_engine generator;
    discrete_distribution<int> distribution {encounter_prob[0] * 10000, encounter_prob[1] * 10000, encounter_prob[2] * 10000, encounter_prob[3] * 10000, encounter_prob[4] * 10000, encounter_prob[5] * 10000, encounter_prob[6] * 10000, encounter_prob[7] * 10000, encounter_prob[8] * 10000, encounter_prob[9] * 10000, encounter_prob[10] * 10000, encounter_prob[11] * 10000, encounter_prob[12] * 10000, encounter_prob[13] * 10000, encounter_prob[14] * 10000, encounter_prob[15] * 10000, encounter_prob[16] * 10000, encounter_prob[17] * 10000, encounter_prob[18] * 10000, encounter_prob[19] * 10000, encounter_prob[20] * 10000, encounter_prob[21] * 10000, encounter_prob[22] * 10000, encounter_prob[23] * 10000, encounter_prob[24] * 10000};
    
    for (int n = 0; n < ntrials; n++)
    {
        while (tracker.size() != 25)
        {
            int numPokemon = distribution(generator);
        
            randomNum = rand()/(double)RAND_MAX;
            avgCatches++;

            //cout << "Random Num: " << randomNum << " Catch prob " << catch_prob[numPokemon];

            if (randomNum < catch_prob[numPokemon])
            {
                //cout << "tracker size" << tracker.size() << endl;

                if (tracker.size() == 0)
                    tracker.push_back(numPokemon);

                //cout << "Num Pokemon " << numPokemon << endl; 

                for (int i = 0; i < tracker.size(); i++)
                {
                    if ((i == tracker.size() - 1) && tracker.at(i) != numPokemon)
                    {
                        tracker.push_back(numPokemon);
                    }

                    if (tracker.at(i) == numPokemon)
                    {
                        //cout << "Found Pokemon Num " << numPokemon << " and in tracker " << tracker.at(i) << endl;
                        break;
                    }
                }
            }
        }
        tracker.clear();
    }

    return avgCatches/ntrials;
    
}


int main(){
    // You can test out things here. Feel free to write anything below.
    char filename[] = "data/pokemon.txt";



	//Print the results of part_a to d here.

    float *a = part_a(filename);
    cout << "Part A Results" << endl << "Legendary Pokemon Proportion: " << *(a) << endl << "Average Height: " << *(a + 1) << endl << "Average Weight: " << *(a + 2) << endl << "Average Enounter Probability: " << *(a + 3) << endl << "Average Catch Probability: " << *(a + 4) << endl;

    float *b = part_b(filename);
    cout << endl << "Part B Results" << endl << "Legendary Pokemon Proportion: " << *(b) << endl << "Average Height: " << *(b + 1) << endl << "Average Weight: " << *(b + 2) << endl << "Average Enounter Probability: " << *(b + 3) << endl << "Average Catch Probability: " << *(b + 4) << endl;
    
    srand(1);
    float c = part_c(filename);
    cout << endl << "Part C Results" << endl << "Average Number of Encounters: " << c << endl;

    float d = part_d(filename);
    cout << endl << "Part D Results" << endl << "Average Number of Catches: " << d << endl;
    



    

}