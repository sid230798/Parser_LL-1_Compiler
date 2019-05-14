/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 29/1/19

*/

/*---------------------------------------------

Compiler for detection of this CFG :-

    1. S = aSbS/bSaS/$


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
        
        bool S(){
        
            /*Check end of string*/
            if(index >= input.size())
                return true;
                
            /*backptr to save index for future use*/
            int backptr = index;
            /*For aSbS*/
            if(input[index++] == 'a'){

                if(S()){
                
                    if(input[index++] == 'b'){
                
                        if(S())
                            return true;
                
                    }
                }

            }

            index = backptr;
            
            /*For bSaS*/
            if(input[index++] == 'b'){

                if(S()){
                
                    if(input[index++] == 'a'){
                
                        if(S())
                            return true;
                
                    }
                }

            }
            
            index = backptr;
            /* Return true for epsilon */
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
