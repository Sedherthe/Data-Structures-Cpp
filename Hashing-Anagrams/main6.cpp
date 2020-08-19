#include<iostream>
#include<fstream>
#include<string>

using namespace std;

ofstream out("anagrams.txt");

//Class which will contain the word and pointer to the next word in list.
class node
{
  public:
  node* next;
  string anagram;
  
  // Constructor for the node class...which is public
  node(string word)
  {
  	next = nullptr;
  	anagram = word;
  }	
};

bool is_anagram(string table, string query)
{
  if(table.length() != query.length())
  {
  	return false;
  }
  else //here length of table and query are same.
  {
    for(int j = 0;j<table.length();++j)
    { 
      bool is_there = false;
      for(int s = 0;s<query.length();++s)
      {
        if(table[j] == query[s])
        { 
          is_there = true;
          query[s] = '$';break; //will come into the first loop now.
        }
      }
      if(!is_there)
      {
      	return false;
      }
    } 	
  }
  return true;
}

int main(int argc, char* argv[])
{
  ifstream myfile(argv[1]);
  string word;
  int asc_sum, index;
  int siz = stoi(argv[2]); //converting string to integer.
  node* table[siz]; //an array of type pointer to node.
  for(int i = 0;i<siz;++i)
  {
  	table[i] = nullptr;
  }
  while(myfile>>word)
  {
  	asc_sum = 0;
  	for(int i = 0;i<word.length();++i) //asc_sum is the ascii sum of the string word.
  	{
  	  asc_sum += word[i];
  	}
    index = asc_sum % siz;
    
    if(table[index] == nullptr)//if the list is empty.
    {
      table[index] = new node(word);
    }
    else //if the list is already filled.
    {
      node* temp = new node(word); //dynamically allocating memory for node.
      temp->next = table[index];
      table[index] = temp; //here table[index] is like head.
    }
  }
  for(int i = 0;i<siz;++i)
  {
  	node* temp = table[i];
  	bool is = false;
  	while(temp != nullptr)
  	{ 
  	  is = true;
  	  temp = temp->next;
  	}
  	if(is){//cout<<endl;
    }
  }
  ifstream urfile(argv[3]);
  while(urfile>>word)
  {
  	asc_sum = 0;
  	for(int i = 0;i<word.length();++i) //asc_sum is the ascii sum of the string word.
  	{
  	  asc_sum += word[i];
  	}
    index = asc_sum % siz;
    node* temp = table[index];
  	while(temp != nullptr)
  	{ 
  	  if(is_anagram(temp->anagram, word))
  	  {
  	  	if(temp->next != nullptr) {
  	  	  out<<temp->anagram<<" ";
  	  	}
  	  	else {
  	  	  out<<temp->anagram;
  	  	}
  	  }
  	  temp = temp->next;
  	}
  	out<<endl;
  }
}