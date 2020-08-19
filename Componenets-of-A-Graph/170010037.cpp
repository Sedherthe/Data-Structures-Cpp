#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

ofstream out("components.txt");

class node{
  public:
  	int val;
  	node* p;//link to the parent node.
  	int rank;
  	node(int n){
      val = n;
      rank = 0;
      node* p = nullptr;
  	}
};

vector<int> uniq_elem;
vector<node*> u_add;

node* get_add(const int x) { 
  int i;
  for(i = 0; i < uniq_elem.size();++i) {
  	if(uniq_elem[i] == x){break;}
  }
  //now at i x is stored in the unique elem array.
  return u_add[i]; //address of the ith unique element.

}

//set the parent of the node of the element to itself.
void makeset(node* element) {
  element->p = element;
  //element->rank = 0;
}

node* findset(node* element) {
  node *temp = element;
  while(temp->p != temp) {
  	temp = temp->p;
  }
  return temp; //returning the node whose parent is itself...i.e, root node.
}

void union_set(node* el1, node* el2) {
  node* temp1 = findset(el1);
  node* temp2 = findset(el2);
  if(temp1 == temp2) { //i.e, if they are already in the same set.
  	return;
  }
  //now both are pucca in the different sets.
  if(temp1->rank > temp2->rank) { //if rank of temp1 is greater.
  	temp2->p = temp1;
  }
  else {
  	temp1->p = temp2;
  	if(temp1->rank == temp2->rank) {
  	  ++temp2->rank;
  	}
  }
}


int main(int argc, char * argv[]) {
  ifstream myfile(argv[1]);
  int x, y; //representing the edges.
  //taking in all the unique elements.
  while(myfile>>x){
  	bool found = false;
    for(int i = 0;i<uniq_elem.size();++i) {
      if(uniq_elem[i] == x){found = true;break;}
    }
    if(!found) {
      uniq_elem.push_back(x);
    }
  }

  //now make set for all the unique elements.
  for(int i = 0; i < uniq_elem.size();++i) {
  	node* temp = new node(uniq_elem[i]);
  	u_add.push_back(temp); //this array contains the address of all the unique elements.
  }

  for(int i = 0; i<uniq_elem.size();++i) {
  	//cout<<uniq_elem[i];
  	makeset(get_add(uniq_elem[i]));
  }

  ifstream myfile2(argv[1]);
  while(myfile2>>x && myfile2>>y) {
    node* x_add = get_add(x);
    node* y_add = get_add(y);

    union_set(x_add, y_add);
  }
  
  vector<node*> roots;//roots continas all the roots of comps.
  for(int i = 0;i<uniq_elem.size();++i) {
  	node* temp = get_add(uniq_elem[i]);
  	if(findset(temp) == temp) {roots.push_back(temp);}//for checking roots.
  }

  for(int i = 0;i < roots.size();++i) {
    for(int j = 0; j < uniq_elem.size();++j) {
      node* add = get_add(uniq_elem[j]);
      if(findset(add) == roots[i]) {
        cout<<uniq_elem[j];
      }
    }
    cout<<endl;
  }

}