#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

ofstream out("dijkstra.txt");

class vertex {
public:
  int val;
  vertex* p;
  int d;
  vector<vertex*> linked;

  vertex(int v){
    val = v;
    d = 100000;
  }
  bool operator<(const vertex &oth) //(1)
  {
      return d < oth.d;
  }
};

class edge{
  public:
    vertex* from;
    vertex* to;
    int w;

    edge(int wt, vertex* f, vertex* t){
      w  = wt;
      from = f;
      to = t;
    }
};

int get_ind(vector<vertex*>& v, const int val) {
  for(int i = 0; i < v.size(); ++i) {
    if(v[i]->val == val) {
      return i;
    }
  }
  return -1; //if there is no such value;
}

bool compare(const vertex*  l, const vertex*  r) //(2)
{
    return l->d > r->d;
}

 vector<vertex*> uniq;

void relax(vertex* from, vertex* to, const int wt) {
  //cout<<"r1";
  if(get_ind(uniq,to->val) == -1){return;}
  //cout<<"r2";
  if(to->d > from->d + wt) {
    to->d = from->d + wt;
    int to_ind = get_ind(uniq,to->val);
    if(to_ind != -1){
    to->p = uniq[to_ind];
    }
  }
}

int get_wt(vertex* fr, vertex* t, vector<edge*>& all){
  //cout<<"w1";
  int indi;
  for(int i = 0; i < all.size(); ++i){
  //cout<<"r.";
    if((all[i]->from->val == fr->val) && (all[i]->to->val == t->val)){
      indi = i;
      break;
    }
  }
  //cout<<"w2"<<all[indi]->w;
  return all[indi]->w;
}

int main(int argc, char* argv[]) {
  ifstream myfile("input.graph");
  int x, y , w;

  while(myfile>>x>>y>>w) {
    bool found = false;
    for(int i = 0; i < uniq.size(); ++i) {
      if(uniq[i]->val == x) {
        found = true;
        break;
      }
    }
    if(!found) {
      vertex* temp = new vertex(x);
      //temp->p = temp; //setting the parent link.
      uniq.push_back(temp);
    }

    //now doing the same thing for y.
    found = false;
    for(int i = 0; i < uniq.size(); ++i) {
      if(uniq[i]->val == y) {
        found = true;
        break;
      }
    }
    if(!found) {
      vertex* tempp = new vertex(y);
      //temp->p = temp; //setting the parent link.
      uniq.push_back(tempp);
    }
  }

  myfile.close();
  vector<vertex*> dummy;
  dummy = uniq;//storing a copy.

  int source = 14;
  int ind = get_ind(uniq, source);
  uniq[ind]->d = 0; //dist of source is 0

  sort(uniq.begin(), uniq.end(), compare);

  //for(int i = 0; i < uniq.size(); ++i){cout<<uniq[i]->val<<" "<<uniq[i]->d<<endl;} // Getting sorted.
  //cout<<"all the uniq vertices..."<<endl;
  vector<edge*> all;
  //vector<edge*> min_eg;

  ifstream myfile1("input.graph");
  while(myfile1>>x>>y>>w) {
  //vertex* temp1 = new vertex(x);
  //vertex* temp2 = new vertex(y);
  int x_ind = get_ind(uniq, x);
  int y_ind = get_ind(uniq, y);

  edge* temp3 = new edge(w, uniq[x_ind], uniq[y_ind]);
  all.push_back(temp3); //this contains all the edges.
  uniq[x_ind]->linked.push_back(uniq[y_ind]);
  //uniq[y_ind]->linked.push_back(uniq[x_ind]);
  }
  //now the vertices are sorted in descending order.
  while(uniq.size()!=0) {
  //cout<<"came"<<endl;
    sort(uniq.begin(),uniq.end(),compare);
    //cout<<"c1";
        vertex* mini = uniq[uniq.size() - 1];
        uniq.pop_back();
       // cout<<"c2";
        for(int j = 0; j < mini->linked.size(); ++j) {
        //cout<<mini->val<<" "<<mini->linked[j]->val;
          relax(mini, mini->linked[j],get_wt(mini,mini->linked[j], all));
        }
        //cout<<"endl";
  }
  //cout<<"done<<endl"<<endl;
  for(int i = 0; i < dummy.size();++i){
    if(dummy[i]->d == 100000){dummy[i]->d = -1;}
    out<<dummy[i]->val<<" "<<dummy[i]->d<<endl;
  }
}
