#include<iostream>
#include<fstream>
#include<vector>

using namespace std ;

// Command line example
// input.graph topological_sort.txt
int main(int argc, char* argv[]){

	fstream fin("tsort.txt", ios::in) ;
	vector<int> topsort ;
	int u,v ;
	bool isright = true, found_u, found_v ;

	while( fin >> v )
		topsort.push_back(v) ;

	fin.close() ;
	fin.open("input1.graph", ios::in) ;

	int sz = topsort.size() ;
	while( fin >> u ){


		fin >> v ;
		found_u = found_v = false ;
		for(int i=0; i<sz ; i++){

			if( topsort[i] == u ){

				found_u = true ;

				for(int j=i+1; j<sz ; j++){
					if( topsort[j] == v )
						found_v = true ;
				}

				if( !(found_u && found_v) ){// not found v after u for directed edge u->v
					cout << u << " " << v <<"\n" ;
					isright = false ;
					break ;
				}

			}
		}
	}

	if(isright)
		cout << "file is" << " seems to be topologically sorted!\n" ;
	else
		cout <<"Please check for the above edges again.\nv1 must have occured before v2.\nYour graph may not be sorted properly or there maybe a bug in my code.\n" ;
	return 0 ;
}

