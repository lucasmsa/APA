#ifndef PJ_FINAL_ILS_H
#define PJ_FINAL_ILS_H

#include "neighborhood.h"
#include "greedyfunction.h"
#include "VND.h"

using namespace std;

void DisturbanceFunction(vector<vector<int> >& solution, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution,vector<vector<int> >& matrix, int vehicles, int i, vector<int>& final_route, vector<vector<int>>& greedy_solution){

    srand(seed + i + 2*seed);
    seed += 3;
    int a = rand()% 3;
    vector<int> temp_distance;
    vector<vector<int>> temp_solution;

    if (a == 0){
        temp_distance = SwapFunction(solution, swap_solution, matrix, vehicles, i+100000);
        temp_solution = swap_solution;
    }
    else if (a == 1){
        temp_distance = TwoOptFunction(solution, twoOpt_solution, matrix, vehicles, i+1000);
        temp_solution = twoOpt_solution; 
    }
    else if (a == 2){
        temp_distance = InverterFunction(solution, inverter_solution, matrix, vehicles, i+0);
        temp_solution = inverter_solution;
    }

    for (int j = 0; j < greedy_solution.size(); j++)
    {
       if(temp_distance[j] < final_route[j]){

           final_route[j] = temp_distance[j];
           solution[j].clear();
           solution[j] = temp_solution[j];
    
       }   
    }


}

vector<vector<int> >ILS(vector<int >& greedy_distance,vector<int>& final_route, vector<vector<int> >& vnd_solution, int dimension, vector<vector<int> >& matrix, int vehicles, int iterations, int capacity, vector<int>& demand, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution, vector<vector<int> >& greedy_solution){
    
    int i = 0;     
    greedy_distance = GreedyFunction(matrix, vehicles, capacity, dimension, i+135+seed, demand, greedy_solution);
    final_route = VndFunction(vnd_solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,greedy_solution, greedy_distance, greedy_solution);
                
    vector<vector<int>> solution = vnd_solution;
    vector<vector<int>> temp_solution;
    vector<int>temp_distance;


    for (i = 0; i < iterations; i++)
    {
        DisturbanceFunction(solution, swap_solution, twoOpt_solution, inverter_solution, matrix, vehicles, i+220+seed, final_route,greedy_solution);
        temp_solution = solution;
        final_route = VndFunction(solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,temp_solution, final_route, greedy_solution);

    }


    int distance = 0;
    int m = 0, n = 0, sum=0;
    cout<< endl;
    cout << "\t\t\t\tILS-METAHEURISTIC" << endl;
    cout << "-----------------------------------------------------------------------------" <<endl;


    for (m = 0; m < solution.size(); m++)
    {
        for (n = 0; n < solution.at(m).size()-1; n++)
        {
            distance += matrix[solution.at(m).at(n)][solution.at(m).at(n+1)];
            cout << solution[m][n] << ", ";
        }
        cout << solution[m][n];
        sum += final_route.at(m);
        cout << "; " << endl;
        //cout << "VEICULO " << m << ", CALCULO DA DISTANCIA: " << distance << ", CALCULO DA FINAL_ROUTE: " << final_route.at(m) << endl;
    }
    cout << "Distance Travelled: " << distance <<  ", outro: " << sum << endl;
    cout << "SOLUTION SIZE (NUMBER OF ROUTES): " << solution.size() << endl;
    
    return solution;
}
#endif