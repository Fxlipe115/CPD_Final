#include<./../lib/hash_table.hpp>
#include<iostream>
#include<fstream>
#include<list>

using namespace std;

list<string> read_file(string file_path){
    // Reads a file from file_path and returns its contents in the list called "ret".
    list<string> ret;
    string line;
    ifstream afile(file_path);
        
    if(afile.is_open()){
        while(getline(afile, line)) ret.push_back(line);
        afile.close();
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
