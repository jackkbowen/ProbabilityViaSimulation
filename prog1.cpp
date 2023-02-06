/**********************************************
	C++ code for project 1 in
	CSE 107 in 2022 winter, UC Santa Cruz,
			for Prof. Chen Qian.
**********************************************/
/*
	Student name:
	UCSC email: jmbowen@ucsc.edu
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

#include "marsaglia-rng.cpp"

using namespace std;

/*
Make a scatter plot of the distribution for these three RNG.
You'll generate num = 10,000 random number in range [0, num).
Make a single scatter plot using matplotlib with the x-axis being 
index of number and the y-axis being the number.

Since it's not easy to plot directly in C++,
You'll need to output your random number to a txt file first,
and then do the scatter plot in Google sheet.
Make sure to label your axis and title your plot appropriately.
*/
void distribution_random()
{
	ofstream inFile("randomData.txt");
    srand(0);

	for (int i = 0; i < 10000; i++)
	{
		int random = rand() % 10000;
		inFile << random << endl;
	}

	inFile.close();
}

void distribution_KISS()
{
    unsigned int k;

	ofstream inFile("KISSData.txt");
    
    for (int i = 0; i < 10000; i++)
    {
        k = KISS % 10000;
        inFile << k << endl;
    }
}


void distribution_SHR3()
{
    uint32_t s;
	ofstream inFile("SHR3Data.txt");

    for (int i = 0; i < 10000; i++)
    {
        s = SHR3 % 10000;
        inFile << s << endl;
    }
}



bool sim_one_game(int n, float p){
    /*
    Write code to simulate one ping pong game to n points
    return the result of win/lose.
    True for win, and False for lose.
    */

    int yourScore = 0;
    int opponentScore = 0; 
    double randomNum;

    while ((yourScore != n && opponentScore != n))
    {
        randomNum = rand()/(double)RAND_MAX;
        //cout << "Rand = " << randomNum << endl;
        //cout << "P = " << p << endl;
        //cout << "Your Score = " << yourScore << endl;
        //cout << "Opponent Score = " << opponentScore << endl; 

        if (randomNum > p)
        {
            opponentScore++;
        }
        else
            yourScore++;
    }

    
    if ((yourScore > n && (yourScore-opponentScore) <= 2 || (opponentScore > n && (opponentScore-yourScore) <= 2)))
    {
        while ((yourScore > n && (yourScore-opponentScore) <= 2 || (opponentScore > n && (opponentScore-yourScore) <= 2)))
        {
            randomNum = rand()/double(1);

            if (randomNum > p)
            {
                opponentScore++;
            }
            else
                yourScore++;
        }
    } 
    

    if (yourScore > opponentScore)
    {
        return true;
    }

    else    
        return false;

}

float pingpong(int n = 21, float p = 0.3, int ntrials = 5000, int seed = 0){
    /*
    Write code to simulate a ping pong game to n points,
    where the probability of you winning a single point is p.
    You must win by 2; for example, if the score is 21 − 20, 
    the game isn’t over yet. Simulate ntrials # of games.
    :param n: The number of points to play to.
    :param p: The probability of YOU winning a single point.
    :param ntrials: The number of trials to simulate.
    :return: returns the probability YOU win the overall game.
    You can ONLY use the system function rand() to generate randomness.
    You need to generate a random float from the interval [0, 1).

    */
   float totalScore = 0;
   srand(seed);

   for (int i = 0; i < ntrials; i++)
   {
    if (sim_one_game(n,p) == true)
        totalScore++;
   }

    cout << "Total Score - " << totalScore << endl;
   return totalScore / (float) ntrials;

}

void plot_output(){
    /*
    Consider the result of diffenrent p in {0, 0.04, 0.08,...,0.96, 1.0}
    and plot a figure with x-axis being p, and the y-axis being the 
    probability of winning the overall game (use your previous function).
    Plot 3 “curves” in different colors, one for each n in {3,11,21}.

    You'll output your probability result to a txt file in this fuction.
    And then do the plot in Google sheet.
    Make sure to label your axis and title your plot appropriately, 
    as well as include a  legend!
    */

   float prob[] = {0, 0.04, 0.08, 0.12, 0.16, 0.2, 0.24, 0.28, 0.32, 0.36, 0.40, 0.44, 0.48, 0.52, 0.56, 0.60, 0.64, 0.68, 0.72, 0.76, 0.80, 0.84, 0.88, 0.92, 0.96, 1};
   int curves[] = {3, 11, 21};
   float data;
   int count = 1;

   ofstream inFile("pingpongData.txt");

   for (int i = 0; i < 3; i++)
   {
    for (int j = 0; j < 26; j++)
    {
        data = pingpong(curves[i], prob[j], 5000, 5);
        inFile << data << endl;
        count++;
    }
    inFile << endl;
   }

} 


int main()
{
	cout << "Testing Random" << endl;
	distribution_random();

    cout << "Testing KISS" << endl;
    distribution_KISS();

    cout << "Testing SHR3" << endl;
    distribution_SHR3();

    cout << "Testing Ping Pong" << endl;
    plot_output();
    // You can test out things here. Feel free to write anything below.
    // Example of rng usage:
	/*
    unsigned int i;
    uint32_t k;
    for(i = 0; i< 10; i++){
        k = KISS;
        printf("%"PRIu32"\n", k);
        printf("%d\n", k%100);
    }

    for(i = 0; i< 10; i++){
        k = SHR3;
        printf("%"PRIu32"\n", k);
        printf("%d\n", k%100);
    }
	*/

}
    
