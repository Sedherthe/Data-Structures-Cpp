#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

int h_size; //need global?

int parent(const int pos) //parent node of pos.
{
  return pos/2;
}
int right(const int pos)// right node of pos.
{
  return 2*pos + 1;
}
int left(const int pos) //left node of pos.
{
  return 2*pos;
}

void max_heapify(vector<int> &pq, const int ind, const int hs)
{
  //we need to maxheapify it at the node ind.
  //the heap size is hs...so the last index is hs-1.
  int largest;
  if(left(ind) < hs && (pq[left(ind)] > pq[ind]))
  {
    largest = left(ind);
  }
  else
  {
    largest = ind; // will always come here.
  }
  if(right(ind) < hs && (pq[right(ind)] > pq[largest]))
  {
    largest = right(ind);
  }
  if(largest != ind)
  {
    int m = pq[largest];
    pq[largest] = pq[ind];
    pq[ind] = m;
    max_heapify(pq,largest,hs); //resursive call to itself.
  }
  return; //not needed.
}

void key_increase(vector<int> &pq, int ind, const int val)
{
  if(val < pq[ind]){cout<<"New key is smallelr than current key"<<endl;return;}
  else
  {
    pq[ind] = val; // we wanted to insert val at index ind.
    while(ind > 0 && (pq[parent(ind)] < pq[ind])) //when ind is 1 out.
    {
      int c = pq[parent(ind)];
      pq[parent(ind)] = pq[ind];
      pq[ind] = c;
      ind = parent(ind);
    }
  }
}

void insert_node(const int val, vector<int> &pq, int &hs)
{
  pq.push_back(-100);
  key_increase(pq,hs,val); //ll add it to the vec with max heap.
  ++hs;
}

void get_max(const vector<int> &pq)
{
 if(pq.size() == 0)//no max condition.
 {
   cout<<endl;return;
 }
 else
 {
   cout<<pq[0]<<endl; //the maximum of the vector?.
 }
}

void extract_max(vector<int> &pq, int &hs)
{
  if(pq.size() == 0)
  {
    cout<<endl;return;
  }
  else
  {
    cout<<pq[0]<<endl;
    int m = pq[0];
    pq[0] = pq[hs - 1]; //the last element.
    max_heapify(pq,0,hs);
  }
}

int main(int argc, char *argv[])
{
  ifstream myfile("samp.txt");
  vector<int> p_q;
  string s;
  h_size = 0;
  if(myfile.is_open())
  {
    while(myfile>>s)
    { cout<<s<<endl;
      if(s == "insert") //isnerting into the queue.
      { int val;cout<<"came"<<endl;
        cin>>val;
        insert_node(val,p_q,h_size);
        cout<<val<<" inserted"<<endl;
      }
      else if(s == "maximum")
      {
        get_max(p_q);
      }
    }
  }
}
