#ifndef CODE_TSP_H
#define CODE_TSP_H
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <stack>
#include <chrono>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <random>
#include <cmath>
#include "FileRead.h"
#include "FileWrite.h"
#include "Algorithm.h"
using namespace std;

typedef vector<int> Path;
typedef vector<Path> Paths;

struct combinations
{
    ///Referenced from https://stackoverflow.com/a/9432150
    typedef vector<int> combination_t;
    // initialize status
    combinations(int N, int R) :
            completed(N < 1 || R > N),
            generated(0),
            N(N), R(R)
    {
        for (int c = 1; c <= R; ++c)
            curr.push_back(c);
    }

    // true while there are more solutions
    bool completed;

    // count how many generated
    int generated;

    // get current and compute next combination
    combination_t next()
    {
        combination_t ret = curr;

        // find what to increment
        completed = true;
        for (int i = R - 1; i >= 0; --i)
            if (curr[i] < N - R + i + 1)
            {
                int j = curr[i] + 1;
                while (i <= R-1)
                    curr[i++] = j++;
                completed = false;
                ++generated;
                break;
            }

        return ret;
    }
private:

    int N, R;
    combination_t curr;
};

class TSP: public Algorithm {
private:
    int numNodes;
    //AdjacencyMatrix graph;
    PositionsVector pos;
    DistanceMatrix dMat;
    CityList citylist;
    map<int,Node> positions;
    pair<Path,float>(TSP::*activeAlg)();
    pair<Path,float> resultPath;
    string activeAlgName;
    long executionTime;

    ///GA configurations
    bool ga_elitism;

    ///SA Configurations
    bool checkEdges;
    bool sa_elitism;

public:

    static AdjacencyMatrix graph;
    ///Constructors
    TSP();
    explicit TSP(int);

    ///Strategy Pattern
    void load(string filePath);
    void execute();
    void display();
    void stats();
    void select(string);
    void save(string filePath);
    void configure(string);
    void passArgs(int,int);

    ///Algorithms
    pair<Path,float> brute_force();
    pair<Path,float> brute_force_recursive();
    pair<Path,float> dynamic_programming();
    pair<Path,float> genetic_algorithm();
    pair<Path,float> simulated_annealing();
    pair<Path,float> simulated_annealing_2();

    ///Utilities
    void brute_force_recursive_util(Paths&,Path,int,int);
    float acceptanceProbability(int,int,float);
    int randomInt(int,int);
    float mathRandom();

    ///Structs
    struct Tour{
        vector<City> tour;
        float distance = 0;
        float fitness = 0;
        int size;
        double distanceTwoCities(City city1, City city2){
            float xDist = abs(city1.x - city2.x);
            float yDist = abs(city1.y - city2.y);
            float zDist = abs(city1.z - city2.z);
            float dist = sqrt((xDist*xDist) + (yDist*yDist) + (zDist*zDist));
            if(!graph[city1.id+1][city2.id+1]){
                dist = FLOAT_MAX;
            }
            return dist;
        }
        double distanceTwoCities_noEdges(City city1, City city2){
            float xDist = abs(city1.x - city2.x);
            float yDist = abs(city1.y - city2.y);
            float zDist = abs(city1.z - city2.z);
            return sqrt((xDist*xDist) + (yDist*yDist) + (zDist*zDist));
        }

    public:
        Tour(){size=0;}
        Tour(vector<City> cities){
            createIndividual(cities);
            size = tour.size();
        }
        void createIndividual(vector<City> cities){
            tour = cities;
            random_shuffle(tour.begin()+1, tour.end());
        }
        double getDistance(){
            if(distance == 0){
                int size = tour.size();
                for(int i = 0; i < size-1; i++){
                    distance += distanceTwoCities(tour[i],tour[i+1]);
                }
                distance += distanceTwoCities(tour[0], tour[tour.size()-1]);
            }
            return distance;
        }
        double getDistance_noEdges(){
            if(distance == 0){
                int size = tour.size();
                for(int i = 0; i < size-1; i++){
                    distance += distanceTwoCities_noEdges(tour[i],tour[i+1]);
                }
                distance += distanceTwoCities_noEdges(tour[0],tour[tour.size()-1]);
            }
            return distance;
        }
        double getFitness(){
//            return 1/getDistance();
            return 1/getDistance_noEdges();
        }
        int getTourSize(){
            size = tour.size();
            return size;
        }

        void setCity(int i, City c){
            tour[i] = c;
        }
        void setCity(City c){
            tour.push_back(c);
            size++;
        }
    };

    struct Population{
        vector<Tour> tours;
        CityList cl;
        int size = 0;
    public:
        Population(CityList clist, int popSize){
            cl = clist;
            for(int i = 0; i < popSize; i++){
                tours.push_back(cl);
            }
            size = tours.size();
        }
        Population(){
            size = 0;
        }
        Tour getFittest(){
            Tour fittest = tours[0];
            for(int i = 1; i < size; i++){
                if(fittest.getFitness() < tours[i].getFitness()) fittest = tours[i];
            }
            return fittest;
        }
        void addTour(Tour t){
            tours.push_back(t);
            size++;
        }
        Tour getTour(int i){
            return tours[i];
        }
    };

    struct Genetics {
        const double mutationRate = .075;
        const int tournamentSize = 5;
        bool elitism = true;
        vector<Tour> tours;

        Tour tournament(Population p) {
            Population tourney;
            int selectionRange = p.size;
            for (int i = 0; i < tournamentSize; i++) {
                int randomTour = rand() % selectionRange;
                tourney.addTour(p.getTour(randomTour));
            }
            Tour fit = tourney.getFittest();
            return fit;
        }

        //Tournament that excludes one tour from population
        Tour tournament(Population p, Tour t) {
            Population tourney;
            int selectionRange = p.size - 1;
            int size = t.size;
            string p1Tour = "";
            for (int i = 0; i < size; i++) {
                p1Tour += t.tour[i].id;
            }
            int i = 0;
            while (i < tournamentSize) {
                int randomTour = rand() % selectionRange;
                for (int j = 0; j < size; j++) {
                    if (p.getTour(randomTour).tour[j].id != p1Tour[j]) {
                        tourney.addTour(p.getTour(randomTour));
                        i++;
                        break;
                    }
                }
            }
            return tourney.getFittest();
        }

        //Randomly mutate individuals based on mutation rate
        void mutate(Tour t) {
            int tSize = t.getTourSize();
            for (int i = 0; i < tSize; i++) {
                if (double(rand() / RAND_MAX) <= mutationRate) {
                    int swap = rand() % tSize;//random city to swap
                    City c1 = t.tour[i];
                    City c2 = t.tour[swap];
                    t.setCity(swap, c1);
                    t.setCity(i, c2);
                }
            }
        }

        //Cross a set of parents, return child
        Tour cross(Tour parent1, Tour parent2) {
            int tSize = parent1.getTourSize();
            Tour child = Tour();
            unordered_set<int> citiesOnTour;//Holds ids of cities on tour, prevents repeats
            int split1 = 1 + rand() % (tSize / 2);//how much of tour to take from first half of parent1
            int split2 = rand() % (tSize / 2);//how much of tour to take from second half of parent1
            split2 = tSize - split2;//Where to start taking chromosomes from parent1
            for (int i = 0; i < split1; i++) {
                child.setCity(parent1.tour[i]);
                citiesOnTour.insert(parent1.tour[i].id);
            }
            for (int i = split2; i < tSize; i++) {
                child.setCity(parent1.tour[i]);
                citiesOnTour.insert(parent1.tour[i].id);
            }
            //Fill in missing cities using parent 2
            int index = 0;
            while (child.getTourSize() != tSize) {
                if (citiesOnTour.count(parent2.tour[index].id) == 0) {
                    child.setCity(parent2.tour[index]);
                }
                index++;
            }
            return child;
        }

    public:
        //Evolves for one generation
        Population evolve(Population p){
            int size = p.size;
            Population nextGen = Population();
            int eliteOffset = 0;
            if(elitism){//saves fittest individual
                eliteOffset = 1;
                nextGen.addTour(p.getFittest());
            }
            for(int i = eliteOffset; i < size; i++){
                Tour parent1 = tournament(p);
                Tour parent2 = tournament(p, parent1);
                Tour child = cross(parent1, parent2);
                nextGen.addTour(child);
            }
            for(int i = eliteOffset; i < size; i++){//Mutate next generation
                mutate(nextGen.getTour(i));
            }
            return nextGen;
        }
        void setElitism(bool in){elitism = in;}
    };
};


#endif //CODE_TSP_H
