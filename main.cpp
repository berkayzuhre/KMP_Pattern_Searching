#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;




long long int power(int base, int power) {

	long long int temp = 1;

	long long int mod_V = 1000000007;

	for (int i = 0; i < power; i++) {

		temp = (temp*base) % mod_V;

	}


	return temp;
}

int main(int argc, char* argv[]) {
	// below reads the input file
	// in your next projects, you will implement that part as well
	if (argc != 3) {
		cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
		return 1;
	}

	ifstream infile(argv[1]);

	string text;

	string temp_S;

	vector< vector<int> > positions;

	infile>>text;

	vector<int> ways(text.size() + 1, 0);

	positions.reserve(text.size());


	for (int i = 0; i < text.size(); i++) {
		vector<int> temp_l;
		positions.push_back(temp_l);
	}


	infile>>temp_S;

	const int nD = stoi(temp_S);

	 vector<string> dictionary;

	 dictionary.reserve(nD);

	for (int i = 0; i < nD; i++) {
		infile>>temp_S;
		dictionary.push_back(temp_S);
	}
	
	long long int mod_V = 1000000007;

	vector<long long int> a;
	
	a.reserve(text.size());

	for (int i = 0; i < text.size(); i++) {
	long long int temp;
	temp = power(26,i);
	a.push_back(temp);
	}

	for (int i = 0; i < nD; i++) {
		
		int wordSize = dictionary[i].size();

		long long int word_V=0;

		long long int text_V = 0;

		for(int k=0;k<wordSize;k++){

			int cW = dictionary[i][k] - 'a' + 1;

			word_V = (word_V + (cW*(a[wordSize - k - 1])) % mod_V)%mod_V;

		}



		for (int j = 0; j < text.size(); j++) {
			
			if (j == 0) {
				for (int k = 0; k<wordSize; k++) {

					int cT = text[k] - 'a' + 1;

					text_V = (text_V + (cT*(a[wordSize - k - 1])) % mod_V) % mod_V;

				}

			}

			else if (j + wordSize <= text.size()) {
				int c_Decrease = text[j - 1] - 'a' + 1;

				int c_Increase = text[j + wordSize - 1] - 'a' + 1;

				text_V = (text_V - ((c_Decrease*(a[wordSize - 1])%mod_V) % mod_V)) % mod_V;

				if (text_V < 0) {
					text_V = text_V + mod_V;
				}

				text_V = (text_V*26) % mod_V;

				text_V = (text_V + c_Increase) % mod_V;



			}
					
					


			if (text_V == word_V && j + wordSize<=text.size()) {
				
				positions[j].push_back(j + wordSize);
			}


		}


	}



	ways[text.size()] = 1;

	for (int i = text.size()-1; i > -1; i--) {

		for (auto x : positions[i]) {
				ways[i] = (ways[i]+ways[x])%mod_V;		

		}
	}



	ofstream myfile;
	myfile.open(argv[2]);
	myfile << ways[0];
	myfile.close();

	return 0;
}
