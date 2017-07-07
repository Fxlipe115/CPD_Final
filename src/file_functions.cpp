#include<iostream>
#include<fstream>
#include<list>
#include<algorithm>
#include<sstream>
#include<string>

using namespace std;

list<string> read_file(string file_path){
    // Reads a file from file_path and returns its contents in the list called "ret".
    list<string> ret;
    string line;
    ifstream afile(file_path);

    if(afile.is_open()){
        // Iterates through file adding each line to the list.
        while(getline(afile, line)) ret.push_back(line);
        afile.close();
    }

    return ret;
}

list<string> tokenize(string inp){
    // Takes a string and returns a list of its tokens, works like split() method from Python.
    // Remove punctiation.
    remove_copy_if(inp.begin(), inp.end(), ispunct);
    istringstream iss(inp);
    string aux;
    list<string> ret;

    // Iterates for each token
    while(iss){
        // Pass the token to an auxiliary string.
        iss >> aux;
        // Lower case the string.
        transform(aux.begin(), aux.end(), aux.begin(), tolower);
        ret.push_back(aux);
    }

    return ret;
}

/* For testing purposes
int main(int argc, char **argv){
    string in = argv[1];
    list<string> li = read_file(in);

    for(auto v : li) cout << v << endl;

    return 0;
}
*/
