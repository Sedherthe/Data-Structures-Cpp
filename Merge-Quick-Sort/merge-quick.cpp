#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

ofstream mout("merge_sort.out");
ofstream qout("quick_sort.out");

int partition(vector<int> &qs, int start, int endd)
{ 
  int ini = start - 1;
  int cnst;
  int check = qs[endd];
  for(int j = start;j<endd;++j)
  {
    if(qs[j] <= check)
    {
      ++ini;
      cnst = qs[j]; //swapping the elements at ini+1 and jth positions.
      qs[j] = qs[ini];
      qs[ini] = cnst;
    }
  }
  cnst = qs[ini+1]; //swapping the last element...into the middle.
  qs[ini+1] = qs[endd];
  qs[endd] = cnst;
  return ini+1;
}

void quick_sort(vector<int> &qs,int start, int endd)
{   
  if(start>=endd){return;}
   int wall = partition(qs,start,endd);
   quick_sort(qs,start,wall-1);
   quick_sort(qs,wall+1,endd);
}

void merge(vector<int> &ms, int start, int mid, int end)
{
   vector<int> copy;int rmid; 
   rmid = mid + 1;
   int big = start;

   while(start <=  mid && rmid <= end)
   {
      if((ms[start] >= ms[rmid])) // decreasing order...including equality.
      {
         copy.push_back(ms[start]);
         ++start;
      }
      else if(ms[rmid] > ms[start])
      {
         copy.push_back(ms[rmid]);
         ++rmid;
      }
   }
   if(start > mid)
   {
      while(rmid <= end)
      {
         copy.push_back(ms[rmid]);
         ++rmid;
      }
   }
   else if(rmid > end)
   {
    while(start <= mid)
    {
      copy.push_back(ms[start]);
      ++start;
    }
   }
   
   int j=0;
   for(int h = big;h<=end;++h) //copying the sorted array back into ms.
   {  
    ms[h] = copy[j];
    ++j;
   }
}

void msort(vector<int> &ms,int start, int end)
{
   if(start == end) return;
   int mid = (start+end)/2;//mid point.
   msort(ms, start,mid);
   msort(ms, mid+1, end);
   merge(ms, start, mid, end);
}

int main(int argc, char *argv[])
{
  ifstream myfile(argv[1]);vector<int> ms;vector<int> q_sort;
  int numb;
  while(myfile>>numb) //storing the numbers in a vector.
  {
    ms.push_back(numb); q_sort.push_back(numb);
  }
  msort(ms,0, ms.size() - 1);//calling merge sort algo.
  quick_sort(q_sort,0,q_sort.size()-1);
  for(int i = 0;i<q_sort.size();++i){qout<<q_sort[i]<<endl;}
  for(int i = ms.size()-1; i>=0;--i)
  {
    mout<<ms[i]<<endl;
  }
}