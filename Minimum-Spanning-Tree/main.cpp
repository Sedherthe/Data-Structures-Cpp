#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

ofstream out("mst_change.txt");

class vertex {
  public:
    int val;
    vertex* p;
    int r; //rank for path compression.
    //vector<vertex*> linked;

  vertex(int v) {
    val = v;
    p = this; //maybe?
    r = 0;
  }
};

class edge {
 public:
  vertex* head;
  vertex* tail;
  long long wt;

  edge(long long int n, vertex* first, vertex* last) {
    wt = n;
    head = first;
    tail = last;
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

void merge_edges(int start, int last, int mid, vector<edge*>& all) {
  int fs = start;
  int ss = mid+1;
  vector<edge*> naya;

  while(fs<=mid && ss <= last) {
    if(all[fs]->wt<all[ss]->wt) {
      naya.push_back(all[fs]);
      ++fs;
    }
    else {
      naya.push_back(all[ss]);
      ++ss;
    }
  }

  if(fs > mid) {
    while(ss <= last) {
     naya.push_back(all[ss]);
     ++ss;
    }
  }
  else if(ss > last) {
    while(fs <= mid) {
      naya.push_back(all[fs]);
      ++fs;
    }
  }
  int j = 0;
  for(int i = start; i<= last; ++i){
   all[i] = naya[j];
   ++j;
  } //copying back the sorted vector.

}


void sort_edges(int start, int last, vector<edge*>& all) {
//lets do merge sort.
 //this function is like mergesert now we should make a merge function.
 //here start is 0 and end is all.size()-1
 if(start>=last) {
   return;
 }
 int mid = (start+last)/2;
sort_edges(start,mid,all);
sort_edges(mid+1,last,all);
merge_edges(start,last,mid,all); //function which will add the sorted components.

}

vertex* find_p(vertex* v) {
  while(v->p != v) {
    v = v->p;
  }
  return v;//here v is the parent;
}

void union_eg(vertex* u, vertex* v) {
  vertex* u_p = find_p(u);
  vertex* v_p = find_p(v);

  if(u_p == v_p) {
    return; //i.e if they are already in the same tree;
  }

  if(u_p->r > v_p->r) {
    v_p->p = u_p;
  }
  else {
   u_p->p = v_p;
   if(u_p->r == v_p->r) {
     ++v_p->r;
   }
  }
}

int main(int argc, char* argv[]) {
  ifstream myfile("input2.graph");
  int x; int y;
  long long int w;
  vector<vertex*> uniq;
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

  vector<edge*> all;
  vector<edge*> min_eg;

  ifstream myfile1("input2.graph");
  while(myfile1>>x>>y>>w) {
    //vertex* temp1 = new vertex(x);
    //vertex* temp2 = new vertex(y);
    int x_ind = get_ind(uniq, x);
    int y_ind = get_ind(uniq, y);

    edge* temp3 = new edge(w, uniq[x_ind], uniq[y_ind]);
    all.push_back(temp3); //this contains all the edges.
  }

  sort_edges(0, all.size()-1, all); //a function which will sort all the edges.

  for(int i = 0; i<all.size(); ++i) {
    if(find_p(all[i]->head) != find_p(all[i]->tail)) {
      min_eg.push_back(all[i]);
      union_eg(all[i]->head, all[i]->tail);
    }
  }

  long long int t = 0;
  t += 1;
  cout<<t<<endl;
  t-=1;
  cout<<t<<endl;
  for(int i = 0; i < min_eg.size();++i) {
  t+=min_eg[i]->wt;
  out<<min_eg[i]->head->val<<"  "<<min_eg[i]->tail->val<<"  "<<min_eg[i]->wt<<endl;
  }
  cout<<"t is: "<<t<<endl;
}


