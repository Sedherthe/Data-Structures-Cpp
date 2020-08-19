#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

ofstream out1("bst.out"); //creating the output file.

int sizes = 0;
int no_in;
int no_pre = 0;
int no_post = 0;

class node
{
public: //making all the members public.
  int key;
  node *parent;
  node *left;
  node *right;

  node(int val) // the constructor for the class node;
  { 
    key = val;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
  }
};

class Tree
{
  node *root;
  public:
    Tree() // constructor for the class Tree.
    {
      root = nullptr;
    }
    node* getroot() // function to get the root of the tree.
    {
      return root;
    }
    void insert(const int val)
    {  
       node *naya = new node(val);//now all parent, left and right are nullptr..and key is val.

       if(root == nullptr)
       {
          root = naya; 
          out1<<val<<" inserted"<<endl;sizes++;    
       } 

       else //inserting only at the leaf positions*
       { 
          node *prev;
          node *temp = root;
          while(temp != nullptr)
          {
            if(val > temp->key) //if val to be inserted is greater then the value in tree go right.
            { 
              prev = temp; //storing the parent pointer.
              temp = temp->right;
            }
            else // else if its lesser or equal to the value in tree insert in the left side.
            { 
              prev = temp; //storing the parent pointer.
              temp = temp->left;
            }
          }

          if(val > prev->key) // if val is greater than the last node..
          {
            prev->right = naya;
            naya->parent = prev;
            out1<<val<<" inserted"<<endl;++sizes;
          }
          else // if val is less than or equal to the last node..
          {
            prev->left = naya;
            naya->parent = prev;
            out1<<val<<" inserted"<<endl;++sizes;
          }
       }
    }
    
    
    void inorder(node *branch) // here branch is the root...initially.
    {  
      if(branch == nullptr) return;
      inorder(branch->left);
      ++no_in; 
      if(no_in < sizes){out1<<(branch->key)<<" ";}
      else {out1<<(branch->key);}
      inorder(branch->right);
    }
    
    void preorder(node *branch)
    {
      if(branch == nullptr) return;
      ++no_pre;
      if(no_pre<sizes){out1<<branch->key<<" ";}
      else{out1<<branch->key;}
      preorder(branch->left);
      preorder(branch->right);
    }

    void postorder(const node *branch)
    {
      if(branch == nullptr) return;
      postorder(branch->left);
      postorder(branch->right);
      ++no_post;
      if(no_post<sizes){out1<<branch->key<<" ";}
      else {out1<<branch->key;}
    }

    void search(const int val)//search for the value val in the tree.
    {
      node *temp = root;
      while(temp != nullptr)
      {
        if(temp->key == val)
        {
          out1<<val<<" found"<<endl;
          return;
        }
        else
        {
          if(val > temp->key) temp = temp->right;
          else temp = temp->left;
        }
      }
      out1<<val<<" not found"<<endl;return; //if no element of the given val found.
    }

    int minimum(node* branch)
    {
      node *temp = branch;
      node *prev = temp;
      while(temp != nullptr)
      { 
        prev = temp;
        temp = temp->left;   
      }
      return prev->key;
    }

    int maximum(node* branch)
    {
      node *temp = branch;
      node *prev = temp;
      while(temp != nullptr)
      {
        prev = temp;
        temp = temp->right;
      }
      return prev->key;
    }

    node * getptr(const int val)//returns the pointer to the node stroring the given value.
    {
      node *temp = root;

      while(temp != nullptr)
      {
        if(temp->key == val)
        {
          return temp;
        }
        else
        {
          if(val > temp->key)
          {
            temp = temp->right;
          }
          else
          {
            temp = temp->left;
          }
        }
      }

      return temp;	
    }

    void successor(const int val)
    { 
      if(root == nullptr)//root = null case is not taken inside max function.
      {
        out1<<val<<" does not exist"<<endl;return;
      }
      if(val == maximum(root))//heres the problem if root is nullptr.
      {
        out1<<"successor of "<<val<<" does not exist"<<endl;return;
      }

      node *temp = getptr(val);
      if(temp == nullptr)
      {
        out1<<val<<" does not exist"<<endl;return; //you'llget segmentation error if no return here.
      }

      if(temp->right != nullptr)
      {
        out1<<minimum(temp->right)<<endl;return;
      }
      //else the successor will be the first ancestor when x will be to its left.
      //that is we want the element next greatest to the current element.
      else
      { 
        node *y = temp->parent;

        while(y-> right == temp && y != nullptr)//because we dont have null parent.
        {
          temp = y;
          y = temp->parent;
        }
        out1<<y->key<<endl;return;
      }
    }

    void predecessor(const int val)
    {
      if(root == nullptr)
      {
        out1<<val<<" does not exist"<<endl;return;
      }
      else if(val == minimum(root))
      {
        out1<<"predecessor of "<<val<<" does not exist"<<endl;return;
      }
      node *temp = getptr(val);
      if(temp == nullptr)
      {
        out1<<val<<" does not exist"<<endl;return;
      }
      else if(temp->left != nullptr)
      {
        out1<<maximum(temp->left)<<endl;return;
      }
      else
      {
        node *y = temp->parent;
        while(y->left == temp && y != nullptr)
        {
          temp = y;
          y = temp->parent;
        }
        out1<<y->key<<endl;return;
      }
    }

    void transplant(node *loc, node *fin)
    {
      if(loc->parent == nullptr) //condition for root node.
      {
        root = fin;
      }
      else if(loc->parent->left == loc)
      {
        loc->parent->left = fin;
      }
      else 
      {
        loc->parent->right = fin;
      }
      if(fin != nullptr)
      {
        fin->parent = loc->parent;
      }
    }

    void deleteit(const int val)
    { 
      if(root == nullptr)
      {
        out1<<val<<" does not exist"<<endl;return;
      }
      node *temp = getptr(val);

      if(temp == nullptr)
      {
        out1<<val<<" does not exist"<<endl;return;
      }

      else if(temp->left == nullptr)
      { 
        transplant(temp, temp->right); // here assignment and parent link are taken care of.
      }
      else if(temp->right == nullptr)
      { 
        transplant(temp, temp->left);
      }
      else
      { 
        int min = minimum(temp->right);
        
        node* temp1 = getptr(min);
        if(temp1->parent != temp) //this takes care of the right
        { 
          transplant(temp1, temp1->right);
          temp1->right = temp->right;
          temp1->right->parent = temp1;
        }
        transplant(temp, temp1);
        temp1->left = temp->left;
        if(temp1->left != nullptr){temp1->left->parent = temp1;}
      }

      --sizes;out1<<val<<" deleted"<<endl;
    }
};

int main(int argc, char *argv[])
{  
   Tree t; // declaring our bst.

   ifstream myfile (argv[1]);
   string s;
   int n;
    
   if(myfile.is_open())
   {
     while(myfile>>s)
     { 
        if(s == "insert")
         { 
          myfile>>n;
          t.insert(n);//calling the insert function.
         }
         else if(s == "in-order")
         {
          t.inorder(t.getroot());//calling the inorder function.
          out1<<endl;
          no_in = 0;
         }
         else if(s == "pre-order")
         {
           t.preorder(t.getroot());
           out1<<endl;
           no_pre = 0;
         }
         else if(s == "post-order")
         {
           t.postorder(t.getroot());
           out1<<endl;
           no_post = 0;
         }
         else if(s == "search")
         {
           myfile>>n;
           t.search(n);
         }
         else if(s == "minimum")
         {
           if(t.getroot() == nullptr)
           {
             out1<<endl;
           }
           else
           {
           out1<<t.minimum(t.getroot())<<endl;
           }
         }
         else if(s == "maximum")
         {
           if(t.getroot() == nullptr)
           {
             out1<<endl;
           }
           else
           {
             out1<<t.maximum(t.getroot())<<endl;
           }
         }
         else if(s == "successor")
         {
           myfile>>n;
           t.successor(n);
         }
         else if(s == "predecessor")
         {
           myfile>>n;
           t.predecessor(n);
         }
         else if(s == "delete")
         {
           myfile>>n;
           t.deleteit(n);
         }
         else if(s == "root")
         {
           out1<<"root is "<<(t.getroot())->key<<endl;
         }
      }
    }
}
