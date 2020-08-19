
#include<iostream>
#include<string>
#include<fstream>
#include<vector>


using namespace std;

// This funciton tells if the string 's' has repeated before or not.
bool is_not_there(const vector<string> &v,const  string s, int *index)
{
 for(int j=0;j<v.size();j++)
  {
    if(v[j]==s){*index =j;return false;}
  }
  return true;
}



int main(int argc, char *argv[])  //argv[1] contains the input file.
{
  char ch;
  int edgeno = 0; // gives the total number of edges.

  ofstream out1("task1.out"); // creating a file to output task1.
  ofstream out2("task2.out"); // creating a file to output task2.
  ofstream out3("task3.out"); // creating a file to output task3.

  FILE *f1;
  f1 = fopen(argv[1],"r");
  while((ch = getc(f1)) != EOF)
  {
    if(ch == '\n') edgeno++;
  }
  fclose(f1); // closed the file..

  vector<string> vertex(edgeno*2); // vector which stores all the vertices given in the array.
  string line;
  ifstream myfile (argv[1]);
  if (myfile.is_open())    // Extracting the vertices from the given graph.
  {
    int i=-1;
    while(getline (myfile,line))
    {
      i++;
      for(char x:line)
      {
        if(x==' ') ++i;
        else vertex[i]= vertex[i] + x;
      }
    }
  }

  vector<string> points; // The vector which stores all the unique vertices.
  vector<int> deg; // The vector which stores the degrees of all the unique vertices.
  for(int i=0;i<vertex.size();i++)
  {
    string str = vertex[i];
    int index =0;

    if(is_not_there(points, str, &index)) // checks if the vertex has already come or not.
    {
      points.push_back(str);
      deg.push_back(1);
    }
    else
    {
      deg[index] += 1;
    }

  }

  out1<<points.size()<<" "<<edgeno<<endl;// Task1 output.
  for(int i=0;i<points.size();++i){
    out1<<points[i]<<endl;
  }// Task1 output.

  for(int i=0;i<points.size();++i){
    out2<<points[i]<<" "<<deg[i]<<endl;
  }// Task2 output.

  // Insertion sort...

  int t,s;
  for(s=1;s<deg.size();++s)
  {
    int key = deg[s];
    string tkey = points[s];
    t = s-1;
    while((deg[t]>key) && (t>=0))
    {
      deg[t+1]=deg[t];
      points[t+1]=points[t];
      --t;
    }
    deg[t+1] = key;
    points[t+1] = tkey;
  }

  // Task3 output.
  for(int i=0;i<points.size();i++){
    out3<<points[i]<<" "<<deg[i]<<endl;
  } 

}
