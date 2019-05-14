/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 5/2/19
Purpose :- 1. Given a CFG remove epsilon production

*/

/*
	Remove epsilon production :- 

		1. S = ABAC
		2. A = aA/$
		3. B = bB/$
		4. C = c

	*After removal

		1. S = ABAC/BAC/ABC/BC/AAC/BC/AC/C
		2. A = aA/a
		3. B = bB/b
		4. C = c

	1. Removew epsilon from A use it to construct A
	2. Remove B and construct S
*/



/*

	$ as empty string
	Capital Letters as non terminal
	small letters as terminal

*/

#include <bits/stdc++.h>

using namespace std;

void printMap(map<char , vector<string> > grammer){

	map<char , vector<string> >::iterator it1;
	
	vector<string>::iterator it2;
	
    for(it1 = grammer.begin();it1!=grammer.end();it1++){

        cout<<it1->first<<"=";
        int start = 0;
         /*Avoid duplicates*/
         unordered_map<string , int> hashMap;
         
        for(it2 = it1->second.begin();it2!=it1->second.end();it2++){
        
        	if((*it2).size() != 0){
		        if(hashMap.find(*it2) == hashMap.end()){
		        
		            if(start++ != 0)
		                cout<<"/"; 
		            cout<<*it2;
		        }
            }
                   
            hashMap[*it2] = 1;
        }
        cout<<endl;
    }

}

/*Get all Indices which contains this set*/
map<int,int> getAllIndices(string prod, char c){

    map<int, int> ans;
    int index = 0;
    //cout<<"Getting Indices ..........\n";
    //cout<<"For Prod : "<<prod<<" char : "<<c<<endl;
    for(int j = 0;j < prod.size();j++){

        if(prod[j] == c){
            
            ans[index] = j;
            //cout<<ans[index]<<" "<<index<<" "<<endl;
            index++;
        }
    }
    //cout<<ans<<endl;
    return ans;
}


string removeOccurences(string temp, int n, map<int, int> index,int size){

    bitset<8> b(n);


    //cout<<"For string : "<<temp<<" and remove : "<<b<<endl;
    int count = 0;
    
    //cout<<b[0]<<endl;
    /*Remove all ocurences specified by n*/
    string newProd = temp;    
    for(int i = 0;i<size;i++){

            
            /*Remove this index*/
            if(b.test(i) == 1){
                
                //cout<<"Yes"<<endl;
                int indexRemove = i;
                indexRemove = index[indexRemove] - count;
                newProd.erase(indexRemove,1);
                count++;
            }
    }
    //cout<<"After Removal : "<<newProd<<endl;
    return newProd;

}

void changeGrammer( map<char, vector<string> > &grammer, char c){

    map<char, vector<string> >::iterator it;
    
    /*Iterate through all Terminals and produce productions*/
    for(it = grammer.begin(); it != grammer.end() ;it++){
    
        vector<string> newProduction = it->second;
        
        //cout<<"For Production : "<<it->first<<".........."<<endl;
        /*Iterate through each production*/
        //vector<string>::iterator it2;
        int length = newProduction.size();
        for(int i = 0;i<length;i++){
        
            string prod = newProduction[i];
            //cout<<"For Production : "<<prod<<"----------->"<<"For char c : "<<c<<endl;
            map<int, int> index = getAllIndices(prod, c); 
            if(index.size() > 0){          
            
                int n = 1<<(index.size());
                //cout<<"For Production got n : "<<n<<endl;
                for(int j = 1;j < n;j++){
            
                    string temp = removeOccurences(prod, j, index,n);
                    newProduction.push_back(temp);
                }
            }
        }
        
        grammer[it->first] = newProduction;
    
    }

}

/*Driver code*/
int main(){

    /*Stores Grammer for change*/
    map<char, vector<string> > grammer;

    /*Stores the null set of grammer*/    
    vector<char> nullSet;
    
    string line;
    
    cout<<"Original Grammer : "<<endl;
    while(getline(cin, line)){

        cout<<line<<endl;
        
        /*Insert into map for further use*/
        vector<string> temp;
        grammer[line[0]] = temp;
        
        /*Tokenize the string for parsing multiple productions*/
        stringstream check(line.substr(2));
			
		string intermediate; 
  
	    /* Tokenizing w.r.t. space '/' */
	    while(getline(check, intermediate, '/')){       
        
            if(intermediate.compare("$") == 0){
            
                nullSet.push_back(line[0]);
                //cout<<"Got this as nullSet : "<<line[0]<<endl;
                continue;
            }
            /*Append to vector after tokenization*/
            //cout<<intermediate<<"->"<<endl;
            grammer[line[0]].push_back(intermediate);
        
        }
         

    }
    
    cout<<"---------------------------"<<endl;
    
    /*Iterator to iterate through nullSet*/
    vector<char>::iterator it;
    
    for(it = nullSet.begin(); it != nullSet.end() ; it++){
    
        //cout<<"This removal is being carried out "<<*it<<endl;
        
        changeGrammer(grammer, *it);
        //printMap(grammer);
    }
    
    cout<<"After Removal of Epsilon Strings : "<<endl;
    printMap(grammer);
}
