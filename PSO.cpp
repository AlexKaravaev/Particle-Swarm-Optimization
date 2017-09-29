#define N 5
#define f 2
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
#define UPPER_BOUND 1000.0
#define LOWER_BOUND 0.0
#define MAX_VEL 1
using namespace std;

double bestFitness = 0.0;
double gb;
int iter = 0;
map<double*, double > Fitness;
map<double*, double > Fitnessold;
map<double*, double > Velocity;
map<double*, double > OldVelocity;
map<double*, double > LocalBest;
double c1 = 1;
double c2 = 2;
double m = 0.5;
double particles[N][f];
ofstream res1;
ofstream res2;
//uniform_real_distribution<double> unif(LOWER_BOUND,UPPER_BOUND);
//default_random_engine re;



double findRes(double CS[f]){
	double res = 0;
	for ( int i=0; i < f ; i++)
	{
		res += pow(CS[i],3);
	}
	return res;
}


void init(){
	for (int i=0;i<N;i++){
		for(int j = 0; j<f;j++){
			particles[i][j] = LOWER_BOUND + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(UPPER_BOUND-LOWER_BOUND))) ;
		}
	}
	for(int i = 0; i < N; i++){
		Velocity[particles[i]] = 0;
		LocalBest[particles[i]] = findRes(particles[i]);
		//Fitnessold[particles[i]] = 0;
		//Fitness[particles[i]] = 0;
		gb = findRes(particles[i]);
	}
	
}


void ChangeState(){

	for (int i = 0; i < N; i ++){
		for(int j = 0;j < f; j++){
			if(particles[i][j] <= UPPER_BOUND && particles[i][j] >= LOWER_BOUND){
				if(particles[i][j] < 0)
					particles[i][j] = particles[i][j] - Velocity[particles[i]];
				else
					particles[i][j] = particles[i][j] + Velocity[particles[i]];
			}
			if(particles[i][j] > UPPER_BOUND)
				particles[i][j] = UPPER_BOUND;
			if(particles[i][j] < LOWER_BOUND)
				particles[i][j] = LOWER_BOUND;
		}
	} 
}

void printRes(){
	for(int i = 0;i<N;i++){
		cout << endl <<"Particle number " << i + 1 << " is: ";
		for(int j = 0;j<f;j++){
			cout<<particles[i][j] << " ";
		}
		cout << endl;
	}
	
}

void ChangeVel(){
	for(int i =0;i<N;i++){
		Velocity[particles[i]] = m*Velocity[particles[i]] + c1*(rand() % 2) * (LocalBest[particles[i]] - findRes(particles[i]))+ c2*(rand()%2) * (gb - findRes(particles[i])); 
		if(abs(Velocity[particles[i]]) > MAX_VEL){
			if(Velocity[particles[i]] > 0)
				Velocity[particles[i]] = MAX_VEL;
			if(Velocity[particles[i]] < 0)
				Velocity[particles[i]] = -1* MAX_VEL;
		}
		//OldVelocity[particles[i]] = Velocity[particles[i]]; 
	}
	
	
}

void compareFitness_and_Local(){
	for (int i = 0;i < N; i++){
		if(findRes(particles[i]) < gb){
			gb = findRes(particles[i]);
		}
		if(findRes(particles[i]) < LocalBest[particles[i]]){
			LocalBest[particles[i]] = findRes(particles[i]);
		}
		//cout << gb << " " << LocalBest[particles[i]] << endl;
	}
}

bool Success(){
	for(int i = 0;i<N;i++){
		if(findRes(particles[i]) == 0){
			cout << "Winning Particle is particle number " << i+1 << " : ";
			for(int j = 0;j<f;j++){
				cout << particles[i][j] << " ";
			}  
			cout << endl;
			return 1;
		}
	}
	return 0;
}

void writeRes(){
	for(int i= 0;i<N;i++){
		for(int j = 0;j<f;j++){
			if(j == 0)
				res1 << particles[i][j] << "	" ;
			if(j == 1)
				res2 << particles[i][j] << "	";
		}
		res1 << endl;
		res2 << endl;
	}
}

int main(){
	srand(time(NULL));
	init();
	printRes();
	
	res1.open("res1.txt");
	res2.open("res2.txt");
	do{
		iter++;
		writeRes();
		compareFitness_and_Local();
		ChangeVel();
		ChangeState();
		ChangeState();

	}while(iter < 5000);
	
	res1.close();
	res2.close();
	printRes();
	//cout <<endl<< findRes(particles[1]);
	cout<< endl;
	cout << "Iterations: " << iter << endl;
	
	return 0;
}

