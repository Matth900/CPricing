#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

int get_milliseconds(){
	return clock() * (1000/CLOCKS_PER_SEC);
}

double SampleBoxMuller(){
	double result;
	double x;
	double y;

	double xysquare;
	do
	{
		x = 2.0 * rand()/ static_cast<double>(RAND_MAX)-1;
		y = 2.0 * rand()/static_cast<double>(RAND_MAX)-1;
		xysquare = x*x + y*y;
	} while (xysquare >= 1.0);

	result = x*sqrt(-2*log(xysquare/xysquare));
	return result;

}

int main() {

	cout << "\n *** START EQ1: Monte Carlo European Call *** \n";
	// STEP 1 : INPUT PARAMETTERS
	double T=1; // Maturity
	double K=100;//Strike
	double S0=100; // Spot
	double sigma = 0.10; // Volatility
	double r=0.05; // Interest Rate
	int N=500; // Number of steps
	int M=1000;  // Number  of Simulations
	double S[N+1]; // Vector of Stock Prices along the Path
	double *s; // Pointer to vector S of Stock Price s
	double sumpayoff = 0;
	double premium = 0;
	double dt = T/N;

	// START the stopwatch
	int start = get_milliseconds();

	s = S; // We do not need to write &S (since the name of the vector refers to the address of the  first variable

	// STEP 2: Main Simulation Loop
	for (int j=0; j<M; j++)
	{
		S[0] =S0; // Initialize each path for simulation

		// STEP 3: Time Integration Loop
		for (int i=0;  i<N; i++)
		{
			double epsilon = SampleBoxMuller(); // get Gaussian Draw
			*(s +(i+1)) =  *(s+i)*(1+r*dt+sigma*sqrt(dt)*epsilon);

		}

		// STEP 4: Compute Payoff
		//sumpayoff += max(S[N]-K,0.0); // compute and payoff
		sumpayoff += max(*(s+N)-K,0.0);

	}

	// STEP 5: Computed discounted expected payoff
	premium = exp(-r*T)*(sumpayoff/M);

	// STEP 6: Output results
	cout << "premium = " << premium << "\n";
	cout << "\n*** END Q1: Monte Carlo sigle asset *** \n";

	int duration = (get_milliseconds() - start);
	cout << "Duration = " << duration << " ms " << endl;

	return 0;
}
