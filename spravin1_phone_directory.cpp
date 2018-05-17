#include <iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<ctime>

using namespace std;

int size;	//size of the directory

/**
   class defined for storing the directory  
*/

class directory
{
public:
  directory (char *first, char *last, char *number)	//default constructor with three arguments to store the values in the directory
  {
    strcpy (first_name, first);
    strcpy (last_name, last);
    strcpy (phone_number, number);

  }
  
  directory ()			//default constructor with no arguments
  {

  }

  void parse (string s);	//function for parsing the string and storeing the parsed value into directory

  void print (void);		//functio for printing the output

  char first_name[100];
  char last_name[100];
  char phone_number[100];


};


directory pd[1000];		//object declaring

/**
   print funtion to print the directory
*/
void directory::print (void)
{
  cout << first_name << " " << last_name << "," << phone_number << endl;
}



/**
   parsing each line in the text file and storing the values in directory
*/

//count number of lines in directory
int directory_size (string s)
{
  ifstream myfile;
  myfile.open (s.c_str ());
  string str;
  int lines = 0;
  while (getline (myfile, str))
    {
      lines = lines + 1;
    }
  myfile.close ();
  return lines;
}



//parsing each line of a string
void directory::parse (string s)
{
  stringstream ss (s);
  string line[2];
  string name[2];
  char first[100];
  char last[100];
  char number[100];
  string token;
  int i = 0;

  while (getline (ss, token, ','))
    {
      line[i] = token;
      i++;
    }

  int j = 0;
  stringstream sss (line[0]);
  while (getline (sss, token, ' '))
    {
      name[j] = token;
      j++;
    }

  strcpy (first_name, name[0].c_str ());
  strcpy (last_name, name[1].c_str ());
  strcpy (phone_number, line[1].c_str ());

}




/**
   funtion declarations
*/

void merge_sort (directory array[], int l, int r);					//merge sort declaration

void merge(directory left[], directory right[], directory array[], int nl , int nr);	//merge funtion declration

void quicksort (directory array[], int p, int r);	//function for the quicksort

int partition (directory array[], int p, int r);	//function for the piviot element in the quicksort

void binary_search(directory d[], int l , int h ,char *x, char *y);	//Binary sort




/**
   funtion definitions
*/


/**
   function definition for merge sort
*/
void merge_sort (directory array[], int l , int r){
   
   int length = r - l + 1;
    
    if(length < 2){
        return;
    }
    
    int mid = length/2;
    directory left[mid];
    directory right[length - mid];
    int i;
    
    for( i=0; i < mid ; i++){
        left[i] = array[i];
    }
    
    for( i=mid ; i < length ; i++){
        right[i - mid] = array[i];
        
    }

    merge_sort(left, 0 , mid-1);
    merge_sort(right, 0 , length - mid-1);
    merge(left,right,array,mid,length-mid);  
}



/**
  merge fuction for the merge sort
*/
void merge(directory left[], directory right[], directory array[], int l , int r){
    
    int i = 0;
    int j = 0;
    int k = 0;
    
    int nl = l;
    int nr = r;
    
    while(i < nl && j < nr){
        if(strcmp(left[i].last_name,right[j].last_name) < 0){
            array[k] = left[i];
            k = k+1;
            i = i+1;
        }
        else if((strcmp(left[i].last_name,right[j].last_name) == 0) && (strcmp(left[i].first_name,right[j].first_name) <= 0) ){
            array[k] = left[i];
            k = k+1;
            i = i+1;
        }
        else if(strcmp(left[i].last_name,right[j].last_name)>0){
            array[k] = right[j];
            k=k+1;
            j=j+1;
        }
        else if(strcmp(left[i].last_name,right[j].last_name) == 0 && (strcmp(left[i].first_name,right[j].first_name) >= 0) ){
            array[k] = right[j];
            k=k+1;
            j=j+1;
        }
        
    }
    
    while(i < nl){
        array[k] = left[i];
        i = i +1;
        k = k +1;
    }
    
    while(j < nr){
        array[k] = right[j];
        j = j +1;
        k = k +1;
    }
}


/**
   function defintion for the randomized Quick sort
*/


/**
   random varible selection function between two numbers
*/
int random (int low, int high)
{
  srand (time (NULL));
  int n = rand () % (high - low + 1) + low;
  return n;
}


/**
   Qicksort Algorithm
*/
void quicksort (directory array[], int p, int r)
{
  if (p < r)
    {
      int i = random (p, r);	//random piviot element selection
      directory temp;
      temp = array[i];
      array[i] = array[r];
      array[r] = temp;
      int q = partition (array, p, r);	//partition the array
      quicksort (array, p, (q - 1));	//sorting the leftpart of the array of piviot element
      quicksort (array, (q + 1), r);	//sorting the right part of the array of the piviot element 
    }
}


/**
  partition of array and sending the piviot element to quick sort
*/
int partition (directory array[], int p, int r)
{

  directory x = array[r];
  int i = p - 1;
  int j = p;

  for (j; j <= r - 1; j++)
    {

      if (strcmp(array[j].phone_number, x.phone_number)<0 || strcmp(array[j].phone_number, x.phone_number)==0)
	{
	  i = i + 1;
	  directory temp;
	  temp = array[i];
	  array[i] = array[j];
	  array[j] = temp;
	}
    }
  directory t;
  t = array[i + 1];
  array[i + 1] = array[r];
  array[r] = t;
  return i + 1;
}




/**
   binary search fuction implementation for dublicates values also 
*/
void binary_search(directory d[], int l , int h ,char *x, char *y){
    
    int low = l;
    int high = h;
    int mid = 0;
    int flag = 0;
    
    while(low <= high){
        mid = (low+high)/2;
        if(strcmp(y,d[mid].last_name)==0 && strcmp(x,d[mid].first_name)==0){
            flag = 1;
            cout<<"location in the directory is "<<mid+1<<endl;
            d[mid].print();
            
            int left = mid-1;
            int right = mid+1;
            while(strcmp(y,d[left].last_name)==0 && strcmp(x,d[left].first_name)==0){
                cout<<"location in the directory is "<<left+1<<endl;
		d[left].print();
                left--;
            }
            
            while(strcmp(y,d[right].last_name)==0 && strcmp(x,d[right].first_name)==0){
                cout<<"location in the directory is "<<right+1<<endl;
                d[right].print();
                right++;
            }
            
            break;
        }
        else if(strcmp(y,d[mid].last_name) > 0){
            low = mid + 1;
        }
        else if(strcmp(y,d[mid].last_name) < 0){
            high = mid - 1;
        }
    }
    if(flag==0){
        cout<<"Name not found"<<endl;
    }
}



/**
  checking the element present in the directory or not
*/
int check(char* fname, char* lname, char* phone)
{
int flag =0;
	for(int i=size-1;i>-1;i--){
		if(strcmp(pd[i].first_name,fname)==0 && strcmp(pd[i].last_name, lname)==0 && strcmp(pd[i].phone_number, phone)==0){
			flag=1;
			return i;
			break;
		}
	}
	if(flag == 0){
		return -1;	
	}
}



/**
  finding the element for deleting the entry in the directory
*/
int find(char* fname, char* lname)
{
int flag =0;
	for(int i=size-1;i>-1;i--){
		if(strcmp(pd[i].first_name,fname)==0 && strcmp(pd[i].last_name, lname)==0){
			flag=1;
			return i;
			break;
		}
	}
	if(flag == 0){
		return -1;	
	}
}





/*
* create function declration
*/
void create(string s){
size = directory_size (s);
ifstream myfile (s.c_str ());
string str;
for (int it = 0; (getline (myfile, str)); it++)
    {
      pd[it].parse(str);

    }
 myfile.close ();
	
}



/**
   sorting the directory with mergesort and quicksort
*/
void sortDirectory(){

merge_sort(pd, 0, size-1);
int i=0, j=1;

while(i<size && j<size ){

    if(strcmp(pd[i].first_name, pd[j].first_name) == 0 && strcmp(pd[i].last_name, pd[j].last_name) ==0){
	j=j+1;      
	int k = j;

		if(strcmp(pd[i].last_name, pd[k].last_name) !=0 || strcmp(pd[i].first_name, pd[k].first_name) != 0){
            		quicksort(pd,i,k-1);
        	}
        
    }else if(strcmp(pd[i].last_name, pd[j].last_name) !=0 || strcmp(pd[i].first_name, pd[j].first_name) != 0){
        i=j;
        j++;
    }
}

}


/*
* insert the entry function
*/
void insertEntry(char* name,char* phone)
{	
	char fname[100];
	char lname[100];
 	string s1[2], s3;
  	int j = 0;
  	s3 = name;
  	string token;
  	stringstream ss(s3);
  	while (getline (ss, token,' '))
    	{
      		s1[j] = token;
         cout<<s1[j]<<endl;
      		j++;
    	}
	strcpy(fname, s1[0].c_str());
	strcpy(lname, s1[1].c_str());
	
	int f = check(fname, lname, phone);

	if(f == -1){
	size = size +1;

    	strcpy(pd[size-1].first_name, s1[0].c_str());
    	strcpy(pd[size-1].last_name, lname);
    	strcpy(pd[size-1].phone_number, phone);
	cout<<"Entry is successfully inserted"<<endl;
	}
	else if(f > -1){
		cout<<"Entry already exist in the directory"<<endl;
	}

}


/**
   searching in the directory
*/
void searchDirectory(char* name){

	string s1[1], s3;
	char fname[100];
	char lname[100];
  	int j = 0;
  	s3 = name;
  	string token;
  	stringstream ss(s3);
  	while (getline (ss, token, ' '))
    	{
      		s1[j] = token;
      		j++;
    	}

    strcpy(fname, s1[0].c_str());
    strcpy(lname, s1[1].c_str());
    binary_search(pd,0,size-1,fname,lname);
}


/**
 Delete entry function definition
*/

void deleteEntry(char* name)
{
	string s1[1], s3;
	char f_name[100];
	char l_name[100];
  	int j = 0;
  	s3 = name;
  	string token;
  	stringstream ss(s3);
  	while (getline (ss, token, ' '))
    	{
      		s1[j] = token;
      		j++;
    	}

    	strcpy(f_name, s1[0].c_str());
    	strcpy(l_name, s1[1].c_str());
    	int f = find(f_name, l_name);
	
	if(f < 0){
		cout<< "Unable to delete as entry not found"<<endl;
	}
	else{
		for(int i=f;i<size-1;i++){
			pd[i] = pd[i+1];
		}
		size = size -1;
		cout<<"Entry successfully deleted"<<endl;
	}
}


main(int argc, char *argv[]){
	
	string s1 = argv[1];
	create(s1);
	sortDirectory();
	cout<<" PHONE DIRECTORY \n"<<endl;

	for(int k = 0 ; k<size ; k++){ 		//printing the sorted directory
    		pd[k].print();
	}
 
	string name_in;
	string phone_in;
	string sname;
	string dname;
	string sub[1];
	string token;
	//stringstream ss;
	int in=0;
    
    int choice;
       do{
	cout<<endl;
	cout<<"********************************"<<endl;
        cout<<"Insert           (press 1)"<<endl;
        cout<<"Search           (press 2)"<<endl;
        cout<<"Delete           (press 3)"<<endl;
        cout<<"Show Directory   (press 4)"<<endl;
        cout<<"Exit             (press 5)"<<endl;
        cin>>choice;
        
        switch(choice){
            case 1: cout<<"insert is selected: \n"<<endl;
		   
		    char name_i[200];
		    char phone_i[100];
		    cout<<"Enter the name only of the person in the format of First_name Last_name\n";
		    cin.ignore();
		    getline(cin,name_in);
		    cout<<"Enter the phone number of the person in the format of (xxx) xxx-xxxx\n";
		    cin.ignore();
		    getline(cin,phone_in);
		    phone_in = " ("+phone_in;
		    strcpy(name_i, name_in.c_str());
		    strcpy(phone_i, phone_in.c_str());
		    insertEntry(name_i,phone_i);
		    sortDirectory();
            break;
            case 2: cout<<"Search is selected: \n"<<endl;
		    char s_name[200];
		    cout<<"Enter the name of the person\n";
		    cin.ignore();
		    getline(cin,sname);
		    strcpy(s_name, sname.c_str());
		    searchDirectory(s_name);
		   
			
            break;
            case 3: cout<<"Delete is selected: \n"<<endl;
		    char d_name[200];
		    cout<<"Enter the name of the person\n";
		    cin.ignore();
		    getline(cin,dname);
		    strcpy(d_name, dname.c_str());
		    deleteEntry(d_name);
            break;
            case 4: cout<<"Show Directory is selected: \n"<<endl;
		    for(int k = 0 ; k<size ; k++){
    			pd[k].print();
		    }
            break;
            case 5: cout<<"Exit is selected"<<endl;
            exit(1);
            break;
            default: cout<<"wrong choice \n"<<endl;
        }
    }while(choice!=5);
    
    
}
