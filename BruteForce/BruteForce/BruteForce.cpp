#include "pch.h"

using namespace std;
using namespace std::chrono;

thread thr[16];
time_point<system_clock> refz;
const string nextS[2] = { "    ", "~~~~" }, cautat = "test1";
char pas = 0, lit = 32, gasit = 0;
unsigned long long int comp = 0;

void chain(string &model, char &crt) {
	for (char i = crt - 1; i >= 0; i--)
	{
		model[i]++;
		if (model[i] == 127)
		{
			model[i] = ' ';
			if (i == 0)
			{
				model += ' ';
				crt++;
			}
		}
		else break;
	}
}

char incrSiVerifica(string model, char crt) {
	while (model[crt] != 127)
	{
		if (model == cautat)
		{
			int timp = duration_cast<seconds>(system_clock::now() - refz).count();
			cout << endl << "A FOST GASIT SIRUL ( " << model.c_str() << " ) din "
				<< comp << " incercari, " << timp << "s, ~"
				<< comp / timp << " comparari / sec." << endl << endl;
			gasit++;
			break;
		}
		model[crt]++;
		comp++;
	}
	return 0;
}

void Brute(string start, string end) {
	char crt = start.length() - 1, fin = end.length();

	cout << "------------------AM INCEPUT THREAD " << this_thread::get_id() << " cu: |" 
		<< start.c_str() << "| pana la |" << end.c_str() << "|-----------------------" << endl;

	while ((start < end || start.length() < fin) && gasit == 0)
	{
		if (incrSiVerifica(start, crt)) return;
		chain(start, crt);
	}
	cout << "!!!!! THREAD " << this_thread::get_id() << " TERMINAT !!!!!" << endl;
}

int main()
{
	unsigned int timp;
	char i, threads = thread::hardware_concurrency();
	refz = system_clock::now();

	while (true) {
		for (i = 0; i < threads; i++)
		{
			thr[i] = thread(Brute, lit + nextS[0], lit + nextS[1]);
			this_thread::sleep_for(milliseconds(20));
			lit++;
		}
		for (i = 0; i < threads; i++)
			thr[i].join();

		timp = duration_cast<seconds>(system_clock::now() - refz).count();
		cout << endl << "Litera " << lit + 0 << "(" << lit << "): | Comps:" 
			 << comp << " | Time:" << timp << "s | Avg. comps/sec:"<< comp / timp << endl << endl;
			

		if (gasit == 1) { system("pause"); exit(0); }
	}
	return 0;
}
