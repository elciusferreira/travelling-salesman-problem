#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

#define INT_MAX 999999

int n;   // number of cities

vector<std::vector<int>> dist;   // adj matrix

int VISITED_ALL = 15;  // all cities have been visited

vector<std::vector<int>> dp;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

string get_input_filename() {
	string filename;

	cout<<"\n---------- T R A V E L L I N G  S A L E S M A N ----------"<<'\n';
	cout<<"               dynamic programming approach"<<"\n\n";
	cout<<"Type the input filename (example: pcv04.txt): ";
	getline (cin, filename);

	return filename;
}

int process_inputfile(string filename) {
	string line;
	int number;
	int i = 0;
	string file_path = "inputs_TSP/" + filename;
	ifstream myfile (file_path);

	if(myfile.is_open()) {

		while(getline(myfile,line)) {
      		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
      		vector<string> words;

	        istringstream input_as_stream(line);
	        copy(istream_iterator<string>(input_as_stream),
	             istream_iterator<string>(),
	             back_inserter(words)
	            );
	        
		    if (words.size()>1) {
			    for(int j=0; j<words.size(); j++) {
			    	number = stoi(words[j]);
			        dist[i][j] = number;
			    }
			    i++;

			} else {
				n = stoi(words[0]);
				dist.resize(n, vector<int>(n,0));
				dp.resize(16, vector<int>(n,-1));
			}
    	}
    	myfile.close();
  	}
	else cout << "Unable to open file"; 
}

/* Recursive tsp function. Mask represents a set of cities. For example, if mask
is 01101, cities number 1 and 4 are not visited yet.*/ 
int  tsp(int mask,int pos){
	if(mask==VISITED_ALL){   // check if all cities are visited
		return dist[pos][0];
	}
	if(dp[mask][pos]!=-1){  // check if value has been already computed
		return dp[mask][pos];
	}

	int ans = INT_MAX;

	// visit all the unvisited cities and take the best route
	for(int city=0; city<n; city++){

		if((mask&(1<<city))==0){   // if current city is not visited yet
			int newAns = dist[pos][city] + tsp(mask|(1<<city), city);
			ans = min(ans, newAns);
		}

	}
	return dp[mask][pos] = ans;
} 

int main(){
	process_inputfile(get_input_filename());

	cout<<"\nTravelling Saleman Distance is: "<<tsp(1,0);   // starting by the city number 0
	cout<<"\n";

	return 0;
}
