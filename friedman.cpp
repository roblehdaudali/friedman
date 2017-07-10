#include <iostream>
#include <cmath>
using namespace std;

// need to balance two functions K and R
// K and R determine the block reward
// over time K block reward gets bigger and R block reward gets smaller
// need to have a smooth transition so no sudden jumps in block rewards



float calc_percent_per_block (float annual_rate, int blocks_per_year)

{
  //function that takes in annual rate
  //and converts to per block rate
  float percent_per_block;

  percent_per_block = log(1 + annual_rate) / blocks_per_year;

  return (percent_per_block);
}


float calc_K_reward(float total_coins, float K_per_block)
{
    //function to calculate friedman block reward
    //this part of the block reward grows over time depending on the total coins in issue
    //it is a function of K and the total coins in issue

    float K_reward;
    K_reward = total_coins * K_per_block;
    return (K_reward);
}

float calc_R_reward(float prev_block, float R_per_block)
{
    //function to calculate reducing part of the block reward - R
    //this block reward planes out over time
    //it is a function of the reward of the previous block and R, the rate of reduction

    float R_reward;
    R_reward = prev_block + (prev_block * R_per_block);
    return (R_reward);
}

float calc_block_reward (float K_reward, float R_reward)
{
    //this functions compares the two rewards and
    //returns the highest one. This enables the K
    //rule to kick in to maintain K% growth in the
    //long run once R_reward has sufficiently diminished

    if (K_reward > R_reward)
        return (K_reward);
    else
        return (R_reward);
}


float calc_total_coins(float genesis_block_reward, float K_per_block, float R_per_block, int block_height, float blocks_per_year)
{
    //function to calculate total coins
    float total_coins = genesis_block_reward;
    float block_reward = genesis_block_reward;
    float K_reward = 0;
    float R_reward = 0;

    for (int i = 0; i <= block_height; i++)
    {
            // this is the main part of the function which calculates
            // the block reward and the total coins
            K_reward = calc_K_reward(total_coins, K_per_block);
            R_reward = calc_R_reward(block_reward, R_per_block);
            block_reward = calc_block_reward(K_reward, R_reward);
            total_coins += block_reward;

        // this part of the function is a test to output the coins
        // and block rewards over time to check the block switchover
        // is smooth
        int x = blocks_per_year/4;

        if (i%x == 0)
            {
            cout << i << " = " << i/blocks_per_year << " years" << endl;
            cout << "--------------------------" << endl;
            cout << "Block reward = " << block_reward << endl;
            cout << "R block reward = " << R_reward << endl;
            cout << "K block reward = " << K_reward << endl;
            cout << "Total coins = " << total_coins << endl << endl;
            }
    }
    cout << "Final" << endl;
    cout << "Block reward = " << block_reward << endl;
    cout << "R block reward = " << R_reward << endl;
    cout << "K block reward = " << K_reward << endl;
    return (total_coins);
}



int main()
{
    // starting parameters

    float genesis_block_reward = 100;
    float minutes_per_block = 2;
    // K is the percentage rate used to inflate the block in the friedman stage
    // K is positive
    float K = 0.032;
    // R is the percentage rate used to reduce the blocks in the transition phase
    // R is negative
    float R = -0.24;

    float blocks_per_hour = 60 / minutes_per_block;
    float blocks_per_day = blocks_per_hour * 24;
    float blocks_per_year = blocks_per_day * 365;

    //per block rates
    float K_per_block = calc_percent_per_block(K, blocks_per_year);
    float R_per_block = calc_percent_per_block(R, blocks_per_year);

    //number of years
    int years = 10;

    int block_height;

    float total_coins;

    block_height = years * blocks_per_year;

    total_coins = calc_total_coins(genesis_block_reward, K_per_block, R_per_block, block_height, blocks_per_year);

    cout << "Total coins = " << total_coins << endl;

    return 0;
}
