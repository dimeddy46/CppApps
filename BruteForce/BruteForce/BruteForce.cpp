#include "pch.h"

using namespace std;
using namespace std::chrono;

mutex mu; 
thread thr[16];
time_point<system_clock> refz;
const string cautat = "findme1";
const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
//const string alphabet = "abcdefghijklmnopqrstuvwxyz";

char n = (char)alphabet.length() - 1;
bool gasit = false;
//unsigned long long int comp = 0;
// ---------------start letter, number of letters, array used for generating permutations -------
void BruteForce(char startJump, char letCount, int x[32])
{
	char i, j;
	unsigned int timp;

	for (i = 0; i <= n && !gasit ; i++)
	{
		x[startJump] = i;	
		if (startJump == letCount)	// we got a permutation
		{
			string model;
			for (j = 1; j <= letCount; j++)	// create a string with it
				model += alphabet[x[j]];

			if (x[0] != x[letCount - 4])		// output settings(when the 5th letter from right to left changes,
			{					// it outputs current stats). x[0] = last 5th letter
				x[0] = x[letCount - 4];
				mu.lock();
				timp = (unsigned int)duration_cast<seconds>(system_clock::now() - refz).count();
				cout << model << " TIME:" << timp << "s " << " THR: " << this_thread::get_id() << endl;
				mu.unlock();
			}

			if (model == cautat)	// if starting string matches permutation
			{
				mu.lock();
				timp = (unsigned int)duration_cast<seconds>(system_clock::now() - refz).count();
				cout << "--------------- A FOST GASIT SIRUL " << model << " in " << timp << "s ---------------------" << endl;
				gasit = true;
				mu.unlock();
			}
		}
		else BruteForce(startJump + 1, letCount, x);
	}
}

int main() {
	char i, threads = thread::hardware_concurrency(), let5 = 0, letCount = 4;
	vector<future<void>> tasks;
	refz = system_clock::now();

	while (!gasit) {
		int x[16][32] = {};
		for (i = 0; i < threads; i++)
		{
			if (let5 <= n)	// threads run until alphabet is still available
			{
				x[i][1] = let5;	// initialize 5th letter
				let5++;
				tasks.push_back(async(launch::async, BruteForce, 2, letCount, x[i]));
			}
			else break;	// TODO: can't get to next [letCount] until all threads with current [letCount] are done
		}

		for (auto &&task : tasks)// wait for threads to end
			task.get();
		tasks.clear();	

		if (let5 > n)	// if 5th letter has completed cycle, restart and increase number of letters
		{
			let5 = 0;
			letCount++;
		}
		cout << "--------BATCH ENDED--------" << endl;
	}
	system("pause");
}
