#include "TSP.h"
TSP::TSP(){numNodes = 4; checkEdges = true;ga_elitism = true;sa_elitism = false;}
TSP::TSP(int num) {numNodes = num; checkEdges = true;ga_elitism = true;sa_elitism = false;}

////////////////////
////Strategy Pattern
////////////////////
void TSP::load(string path){
    AdjacencyMatrix fullMatrix = FileRead::read_graph_unweighted_matrix("../../Data/Graph/graph.txt");
    ///Limit number of nodes in graph
    for(int r = 0; r < numNodes+1; r++){
        vector<bool> newRow;
        for(int c = 0; c < numNodes+1; c++) newRow.push_back(fullMatrix[r][c]);
        graph.push_back(newRow);
    }

    map<int,Node> allPositions = FileRead::readPositions_map_node("../../Data/Graph/positions.txt");
    ///Limit number of nodes in positions
    for(auto it : allPositions) {
        if (it.first <= numNodes) positions.insert(it);
    }

    DistanceMatrix fullDMat = FileRead::read_distance_matrix("../../Data/Graph/");
    ///Limit number of nodes in dMat
    for(int r = 0; r < numNodes; r++){
        vector<float> newRow;
        for(int c = 0; c < numNodes; c++) newRow.push_back(fullDMat[r][c]);
        dMat.push_back(newRow);
    }

    CityList fullCl = FileRead::read_city_list("../../Data/Graph/");
    ///Limit number of nodes in citylist
    for(int i = 0; i < numNodes; i++){
        citylist.push_back(fullCl[i]);
    }

    PositionsVector fullPos = FileRead::readPositions_vector("../../Data/Graph/positions.txt");
    ///Limit number of nodes in pos
    for(int i = 0; i < numNodes; i++){
        pos.push_back(fullPos[i]);
    }
}
void TSP::select(string selection){
    if(selection == "Brute Force") activeAlg = &TSP::brute_force;
    if(selection == "Brute Force Recursive") activeAlg = &TSP::brute_force_recursive;
    if(selection == "Dynamic Programming") activeAlg = &TSP::dynamic_programming;
    if(selection == "Genetic Algorithm") activeAlg = &TSP::genetic_algorithm;
    if(selection == "Simulated Annealing") activeAlg = &TSP::simulated_annealing;
    if(selection == "Simulated Annealing 2") activeAlg = &TSP::simulated_annealing_2;
    activeAlgName = selection;
}
void TSP::execute(){
    using namespace chrono;
    auto start = high_resolution_clock::now();
    resultPath = (this->*activeAlg)();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    executionTime = duration.count();
}
void TSP::display(){
    cout << "Display Adjacency Matrix:\n\t   ";
    for(int c = 1; c < graph.size(); c++){
        cout << c << " ";
    }
    cout << "\n\t";
    for(int r = 1; r < graph.size(); r++){
        if(r < 10) cout << r << "  ";
        else cout << r << " ";
        for(int c = 1; c < graph.size(); c++){
            cout << graph[r][c] << " ";
        }
        if(r < graph.size()-1) cout << "\n\t";
    }
    cout << endl << endl;
}
void TSP::stats(){
    cout << "Stats:\n\t";
    //1.00000000
    //1000000.00
    long conversion = 1000000.0;
    long executionSeconds = executionTime/conversion;
    long minutesConversion = 60000000.0;
    long executionMinutes = executionTime/minutesConversion;
    cout << activeAlgName << " executed in ";
    if(executionMinutes > 1){
        cout << executionMinutes << " minutes ";
    }else if(executionSeconds > 1){
        cout << executionSeconds << " seconds ";
    }else{
        cout << executionTime << " microseconds ";
    }
    cout << "on " << numNodes << " nodes.\n\t";

    for(int i = 0; i < resultPath.first.size(); i++){
        cout << resultPath.first[i];
        if(i != resultPath.first.size()-1) cout << ",";
    }
    cout << " (cost " << resultPath.second << ")" << endl;
}
void TSP::save(string filePath) {
    FileWrite::str_append(filePath, activeAlgName + "," + to_string(numNodes) + "," + to_string(executionTime) + "," + to_string(resultPath.second) + "\n");
}
void TSP::configure(string configuration) {
    if(configuration == "SA Edges On") checkEdges = true;
    if(configuration == "SA Edges Off") checkEdges = false;
    if(configuration == "SA Elitism On") sa_elitism = true;
    if(configuration == "SA Elitism Off") sa_elitism = false;
    if(configuration == "GA Elitism On") ga_elitism = true;
    if(configuration == "GA Elitism Off") ga_elitism = false;
}
void TSP::passArgs(int, int) {}

//////////////
////Algorithms
//////////////
pair<Path,float> TSP::brute_force(){
    ///Generate all hamiltonian paths
    Paths paths;
    Path newPath;
    for(int i = 1; i < graph.size(); i++) newPath.push_back(i);
    newPath.push_back(1);
    do{
       bool valid = true;
       for(int i = 0; i < newPath.size()-1; i++){
           if(!graph[newPath[i]][newPath[i+1]]){
               valid = false;
               break;
           }
       }
       if(valid) paths.push_back(newPath);
    }while(next_permutation(newPath.begin()+1,newPath.end()-1));

    ///Find cost of each path
    vector<float> costs;
    for(auto& p : paths){
        float cost = 0;
        for(int n = 0; n < p.size()-1; n++){
            cost += dMat[p[n]-1][p[n+1]-1];
        }
        costs.push_back(cost);
    }

    ///Find minimum cost path
    int minIndex = min_element(costs.begin(),costs.end())-costs.begin();
    float minCost = *min_element(costs.begin(),costs.end());
    return make_pair(paths[minIndex],minCost);
}
pair<Path,float> TSP::brute_force_recursive(){
    Paths paths;
    Path path;
    for(int i = 1; i < graph.size(); i++) path.push_back(i);
    path.push_back(1);
    int n = path.size();
    brute_force_recursive_util(paths,path,1,n-2);

    /*for(int p = 0; p < paths.size(); p++){
        for(int node = 0; node < paths[p].size(); node++){
            cout << paths[p][node] << " ";
        }
        cout << endl;
    }*/

    ///Lambda for calculating distance between two nodes
    auto calcDistance = [this](int from,int to) -> float {
        float x1 = positions.find(from)->second.x;
        float y1 = positions.find(from)->second.y;
        float z1 = positions.find(from)->second.z;
        float x2 = positions.find(to)->second.x;
        float y2 = positions.find(to)->second.y;
        float z2 = positions.find(to)->second.z;
        return sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
    };

    ///Find cost of each path
    vector<float> costs;
    for(auto& p : paths){
        float cost = 0;
        for(int node = 0; node < p.size()-1; node++){
            cost += calcDistance(p[node],p[node+1]);
        }
        costs.push_back(cost);
    }

    ///Find minimum cost path
    int minIndex = min_element(costs.begin(),costs.end())-costs.begin();
    float minCost = *min_element(costs.begin(),costs.end());
    return make_pair(paths[minIndex],minCost);
}
pair<Path,float> TSP::dynamic_programming(){
    ///Adapted from https://github.com/CarlEkerot/held-karp/blob/master/held-karp.py
    int n = dMat.size();

    map<pair<int,int>,pair<float,float>> C;

    for(int k = 1; k < n; k++){
        pair<int,int> key = make_pair((1 << k),k);
        pair<float,float> val = make_pair(dMat[0][k],0);
        C[key] = val;
    }

    for(int subset_size = 2; subset_size < n; subset_size++){
        Paths subsets;
        combinations cs(n-1, subset_size);
        while (!cs.completed)
        {
            combinations::combination_t c = cs.next();
            subsets.push_back(c);
        }
        for(auto subset : subsets){
            int bits = 0;
            for(auto bit : subset){
                bits |= 1 << bit;
            }

            // Find the lowest cost to get to this subset
            for(auto k : subset){
                int prev = bits & ~(1 << k);

                vector<pair<float,int>> res;
                for(auto m : subset){
                    if(m == 0 || m == k) continue;
                    pair<int,int> key = make_pair(prev,m);
                    pair<float,int> it = make_pair((C.find(key)->second.first+dMat[m][k]),m);
                    res.push_back(it);
                }
                pair<int,int> key = make_pair(bits,k);
                float min = 99999;
                int minInd = 0;
                for(int i = 0; i < res.size(); i++){
                    if(res[i].first < min){
                        min = res[i].first;
                        minInd = i;
                    }
                }
                C[key] = res[minInd];
            }
        }
    }//end for subset_size

    // We're interested in all bits but the least significant (the start state)
    int bits = (pow(2,n) - 1) - 1;

    // Calculate optimal cost
    vector<pair<float,int>> res;
    for(int k = 1; k < n; k++){
        pair<int,int> key = make_pair(bits,k);
        res.push_back(make_pair((C.find(key)->second.first+dMat[k][0]),k));
    }
    float min = 99999;
    int minInd = 0;
    for(int i = 0; i < res.size(); i++){
        if(res[i].first < min){
            min = res[i].first;
            minInd = i;
        }
    }
    pair<float,int> opt = res[minInd];
    pair<float,int> parent = res[minInd];

    // Backtrack to find full path
    Path p;
    for(int i = 0; i < n-1; i++){
        p.push_back(parent.second);
        int new_bits = bits & ~(1 << parent.second);
        pair<int,int> key = make_pair(bits,parent.second);
        pair<float,int> und = C[key];
        parent = C[key];
        bits = new_bits;
    }

    // Add implicit start state, reverse, add return to start node, return
    p.push_back(0);
    reverse(p.begin(),p.end());
    p.push_back(0);
    for(int & i : p) i++;
    return make_pair(p,opt.first);
}
pair<Path,float> TSP::genetic_algorithm(){
    ///Adapted from http://www.theprojectspot.com/tutorial-post/applying-a-genetic-algorithm-to-the-travelling-salesman-problem/5
    int populationSize = 30;
    const int numberGenerations = 5000;//Number of generations to evolve
    srand(time(nullptr)); //Seed rand

    vector<int> testing;

    Population p = Population(citylist, populationSize);
    Tour fittest = p.getFittest();
    Genetics g;
    g.setElitism(ga_elitism);


    for(int i = 0; i < numberGenerations; i++){
        p = g.evolve(p);
    }
    fittest = p.getFittest();

    Path rp;
    for(auto c : fittest.tour) rp.push_back(c.id+1);
    rp.push_back(fittest.tour[0].id+1);
    float rc = fittest.getDistance();
    return make_pair(rp, rc);
}
pair<Path,float> TSP::simulated_annealing(){
    ///Adapted from http://www.theprojectspot.com/tutorial-post/simulated-annealing-algorithm-for-beginners/6

    srand(time(nullptr)); //Seed rand
    float temp = 10000;//initial temp
    float coolingRate = 0.0003;

    Tour currentSolution;
    currentSolution.createIndividual(citylist);

    //set as current best
    Tour best = currentSolution.tour;

    while(temp > 1){
        //create new neighbor tour
        Tour newSolution;
        if(sa_elitism) newSolution = best.tour;
        else newSolution = currentSolution.tour;

        //get a random position in the tour
        int tourPos1 = randomInt(0,newSolution.getTourSize()-1);
        int tourPos2 = randomInt(0,newSolution.getTourSize()-1);

        //Get the cities at selected positions in the tour
        City citySwap1 = newSolution.tour[tourPos1];
        City citySwap2 = newSolution.tour[tourPos2];

        //Swap them
        newSolution.setCity(tourPos2, citySwap1);
        newSolution.setCity(tourPos1, citySwap2);

        //Get energy of solutions
        int currentEnergy,neighborEnergy;
        if(checkEdges){
            currentEnergy = currentSolution.getDistance();
            neighborEnergy = currentSolution.getDistance();
        }else{
            currentEnergy = currentSolution.getDistance_noEdges();
            neighborEnergy = currentSolution.getDistance_noEdges();
        }

        //Decide if we should accept the neighbor
        if(acceptanceProbability(currentEnergy, neighborEnergy, temp) > mathRandom()){
            currentSolution = newSolution.tour;
        }

        //Keep track of best solution found
        float currentDistance,bestDistance;
        if(checkEdges){
            currentDistance = currentSolution.getDistance();
            bestDistance = best.getDistance();
        }else{
            currentDistance = currentSolution.getDistance_noEdges();
            bestDistance = best.getDistance_noEdges();
        }
        if(currentDistance < bestDistance){
            best = currentSolution.tour;
        }

        //cool system
        temp *= (1-coolingRate);
    }

    Path rp;
    for(int i = 0; i < best.tour.size(); i++) rp.push_back(best.tour[i].id+1);
    rp.push_back(best.tour[0].id+1);
    float rc;
    if(checkEdges) rc = best.getDistance();
    else rc = best.getDistance_noEdges();
    return make_pair(rp,rc);
}
pair<Path,float> TSP::simulated_annealing_2(){
    srand(time(nullptr)); //Seed rand

    Path path;
    for(int i = 1; i < numNodes+1; i++){
        path.push_back(i);
    }
    float minCost = FLOAT_MAX;
    Path minPath = path;
    random_shuffle(path.begin()+1,path.end());

    float initialTemp = 999;
    float coolingRate = 0.1;
    float minTemp = 0.99;
    float currTemp = initialTemp;
    float rand_prob = 99;
    float rand_cool = 0.01;

    while(currTemp > minTemp){
        currTemp -= coolingRate;
        rand_prob -= rand_cool;
        if(rand_prob >= 92) rand_cool += 0.001;

        int random = (rand() % 101);
        if(random <= rand_prob) {
            int rotation = (rand() % 4) + 4;
            random_shuffle(path.begin() + 1, path.end());
            if (rotation % 4 == 0) rotate(path.begin()+1, (path.begin() + rotation), path.end());
            float dist = 0;
            for (int i = 0; i < path.size() - 1; i++) dist += dMat[path[i] - 1][path[i+1] - 1];
            dist += dMat[path[path.size()-1]-1][path[0]-1];
            if (dist < minCost) {
                minCost = dist;
                minPath = path;
                minPath.push_back(path[0]);
            }
        }else{
            int rotation = (rand() % 4) + 4;
            rotate(path.begin()+1, (path.begin() + rotation), path.end());
            float dist = 0;
            for(int i = 0; i < path.size()-1; i++) dist += dMat[path[i]-1][path[i+1]-1];
            dist += dMat[path[path.size()-1]-1][path[0]-1];
            if(dist < minCost){
                minCost = dist;
                minPath = path;
                minPath.push_back(path[0]);
            }
        }
    }

    return make_pair(minPath,minCost);
}

/////////////
////Utilities
/////////////

///for Simulated Annealing
float TSP::acceptanceProbability(int energy, int newEnergy, float temperature) {
    if(newEnergy < energy) return 1.0;
    return exp((energy-newEnergy)/temperature);
}
int TSP::randomInt(int min, int max) {
    return rand() % ((max-min)) + (min+1);
}
float TSP::mathRandom() {
    return (rand() % (100) + (0))/100.0;
}

///for Brute Force
void TSP::brute_force_recursive_util(Paths& paths, Path path, int l, int r) {
    if(l == r){
        paths.push_back(path);
    }
    else{
        for(int i = l; i <= r; i++){
            swap(path[l],path[i]);
            bool valid = true;
            for(int j = 0; j < path.size()-1; j++) if(!graph[path[j]][path[j+1]]) valid = false;
            if(valid) brute_force_recursive_util(paths,path,l+1,r);
            swap(path[l],path[i]);
        }
    }
}

///for GA
AdjacencyMatrix TSP::graph;


















