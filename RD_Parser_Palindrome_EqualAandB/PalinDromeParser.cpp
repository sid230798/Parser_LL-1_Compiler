/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 29/1/19

*/

/*---------------------------------------------

Compiler for detection of this CFG :-

    1. S = 0S0 | 1S1 | e


Recursicve descent :-

    1. Must exhaust all possiblities of search
    2. Only even length Strings are allowed
-----------------------------------------------*/

#include <iostream>
#include <string>

using namespace std;

class compiler{

    /*Input contains string and index contains current index of string*/
    public:
        string input;
        int index;
        
        compiler(string input){
            
            this->input = input;
            index = 0;
           
        }

        /*Exhaustive search*/    
        bool S(){

            /*Check end of string*/
            if(index >= input.size())
                return true;
      
            /*backptr to save index for future use*/
            int backptr = index;
            
            
            /*For 0S0*/
            if(input[index++] == '0'){
            
                if(S()){
                
                    if(input[index++] == '0'){
                    
                        return true;
                    }
                    else{
                    
                        index = backptr;    
                    }   
                }else{
                    /*If false don't return try next approach*/
                    index = backptr;
                }
            }
            
            index = backptr;
            /*For 1S1*/
            /*
            if(input[index++] == '1'){
            
                if(S()){
                
                    if(input[index++] == '1')
                        return true;
                    else
                        index = backptr;    
                    
                }else{
                    //If false don't return try next approach
                    index = backptr;
                }
            }
            
            index = backptr;
            
            //Check for Epsilon stringsd
            return true;
            */
            if(input[index++] == '0'){
            
            	if(input[index++] == '0')
            		return true;
            }
            
            index = backptr;
            //return false;
           
            return true;
        }
    
};

int main(){

    string s;
    cout<<"Enter String to be matched : ";
    cin>>s;

    /*Odd length Strings not expected*/
    /*
    if(s.size()%2 == 1){
        cout<<"Not Matched"<<endl;
        return 0;
    }*/
    compiler *obj = new compiler(s);
    if(obj->S() && obj->index == s.size())
        cout<<"String Matched"<<endl;
    else
        cout<<"Not Matched"<<endl;
}
