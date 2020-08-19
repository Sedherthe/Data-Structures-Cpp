#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

ofstream out("out.txt");
ofstream out1("tsort.txt");

class vertex {
  public:
  	int val;
  	vertex* p; //the parent link.
  	vector<vertex*> linked;
  	int d;
  	int f;
  	string color;

  	vertex(int n) {
  		val = n;
  		p = nullptr;
  		//head = nullptr;
  		color = "white";
  		d = -1; //maybe.
  		f = 0;
  	}
};

class node {
public:
  vertex* curr;
  vertex* next;
  node(vertex* temp) {
    curr = temp;
    next = nullptr;
  }
};

int get_ind(const vector<vertex*>& v, const int x) {
  for(int i = 0; i < v.size(); ++i) {
    if(v[i]->val == x) {
      return i;
    }
  }
  return -1; //i.e if not found.
}

int get_int(string s) {
  int num;
  for(int i = s.length(); i >= 0; --i) {
    num += s[i]*pow(10,i);
  }
}

int start = 0, siz = 0;
int len;

void enqueue(vertex** arr, vertex* node, const int len) {
  if(siz == len){return;}
  arr[(start + siz)%len] =  node;
  ++ siz;
}

vertex* dequeue(vertex** arr) {
if(siz == 0){return nullptr;}
vertex* temp = arr[start];
arr[start] = nullptr;
start = (start+1)%len;
 --siz;
return temp;
}

int time;
//int ct = uv.size();
//int arr[ct];

void dfs_visit(vector<vertex* >& v, vertex* node, int* arry, int& index) {
  ++time;
  node->d = time;
  node->color = "gray";
  for(int j = 0; j < node->linked.size(); ++j) {
    if(node->linked[j]->color == "white") {
      node->linked[j]->p = node;
      dfs_visit(v, node->linked[j], arry, index);
    }
  }
  node->color = "black";
  ++time;
  arry[index] = node->val;--index;
  node->f = time;
}

int main(int argc, char* argv[]) { cout<<"came"<<endl;
  ifstream myfile("input1.graph");
  int x,y;
  vector<vertex*> uv; //denotes unique vertices.
  vector<vertex*> adj;
  while(myfile>>x) {
    bool found = false;
    for(int i = 0; i < uv.size(); ++i) {
      if(uv[i]->val == x) {
        found = true;break; //will start the loop from next i.
      }
    }
    if(!found){
    vertex* temp = new vertex(x); // val is n, color is white, parent is null.
    uv.push_back(temp);
    } //if it has not come already.
    //adj.push_back(temp);
  }
   myfile.close();

  for(int j= 0; j < uv.size();++j){cout<<uv[j]->val<<endl;}
  len = uv.size(); //defined the length of the array.
  cout<<"came1"<<endl;
  //cout<<get_ind(uv, 342)<<endl;
  //making the adjacenct list.
  ifstream myfile1("input1.graph");
  while(myfile1>>x && myfile1>>y) {
    vertex* from = uv[get_ind(uv, x)];
    vertex* to = uv[get_ind(uv, y)];
    from->linked.push_back(to);//setting up the link.
  }
  cout<<"came3"<<endl;

  //Breadth firt search.
  int source = 2034;
  vertex* arr[len];
  for(int i = 0; i < len; ++i) {
    arr[i] = nullptr;
  }
  int s_ind = get_ind(uv, source);
  uv[s_ind]->d = 0;
  enqueue(arr, uv[s_ind], len); //adding the source to the queue.
  while(siz>0) {
    vertex* temp = dequeue(arr);
    //vertex* tempo = temp;
    for(int s = 0; s < temp->linked.size();++s) {
      vertex* temp1 = temp->linked[s];
      if(temp1->color == "white") {
        temp1->color = "gray";
        temp1->d = temp->d + 1;
        temp1->p = temp;
        enqueue(arr, temp1, len);
      }
      //tempo = temp1;
    }
    temp->color="black";
  }

  for(int i = 0; i < uv.size(); ++i) {
    out<<uv[i]->val<<" "<<uv[i]->d<<endl;
  }


        /*  Topological sorting  */

int leng = uv.size();
int tsort[leng];
int index = leng-1;

for(int i = 0;i<uv.size();++i) {
  uv[i]->color = "white";
  uv[i]->p = nullptr;
  uv[i]->d = 0;
}

time = 0;

for(int i = 0; i < uv.size(); ++i) {
  if(uv[i]->color == "white") {
    dfs_visit(uv, uv[i], tsort, index);
  }
}

for(int s = 0; s< uv.size();++s) {
  out1<<tsort[s]<<endl;
}

}
