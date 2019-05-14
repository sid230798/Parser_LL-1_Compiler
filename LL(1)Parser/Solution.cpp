/*

Name :- Siddharth Nahar
Entry No :- 2016csb1043
Date :- 16/2/19
Purpose :- 

        1. Produce FIRST and FOLLOW Sets of grammer.
        2. Check if Grammer can be parsed by LL(1)
        3. Can be extended in RD
*/


/*

        Check for This Grammer :- 

			S -> ACB | Cbb | Ba
			A -> da | BC
			B -> g | ~
			C -> h | ~

		FIRST-SET :- 
		
			FIRST(S) = { d, g, h, Є, b, a}
			FIRST(A) = { d, g , h, ~ }
			FIRST(B) = { g , ~ }
			FIRST(C) = { h , ~ }
		
		FOLLOW-SET :- 
		
			FOLLOW(S) = { $ }
			FOLLOW(A)  = { h, g, $ }
			FOLLOW(B) = { a, $, h, g }
			FOLLOW(C) = { b, g, $, h }

*/

#include <bits/stdc++.h>
#include <ctype.h>

using namespace std;

unordered_map<char, int> nonTerminals;
unordered_map<char, int> Terminals;

bool isTerminal(char c){

	if(nonTerminals.find(c) == nonTerminals.end())
		return true;
		
	return false;

}

void getSetofTerminals(map<char , vector<string> > grammer){

	map<char , vector<string> >::iterator it1;
	vector<string>::iterator it2;
	
	for(it1 = grammer.begin();it1!=grammer.end();it1++){
	
		for(it2 = it1->second.begin();it2!=it1->second.end();it2++){
		
			string prod = *it2;
			for(int i = 0;i<prod.size();i++){
			
				if(isTerminal(prod[i]))
					Terminals[prod[i]] = 1;
			
			}
		
		}
	}


}

void printSet(map<char, vector<char> > grammer){

	map<char , vector<char> >::iterator it1;
	vector<char>::iterator it2;
	
	for(it1 = grammer.begin();it1!=grammer.end();it1++){
	
		cout<<it1->first<<"={";
		int i = 0;
		for(it2 = it1->second.begin();it2!=it1->second.end();it2++){
		
			if(i++ != 0)
				cout<<",";
				
			cout<<*it2;
		
		}
		
		cout<<"}"<<endl;
	
	}

}

/*Print Utility for map*/
void printMap(map<char , vector<string> > grammer){

	map<char , vector<string> >::iterator it1;
	
	vector<string>::iterator it2;

    for(it1 = grammer.begin();it1!=grammer.end();it1++){

        cout<<it1->first<<"=";
        int start = 0;
         /*Avoid duplicates*/
         unordered_map<string , int> hashMap;
         
        for(it2 = it1->second.begin();it2!=it1->second.end();it2++){
        
            if(hashMap.find(*it2) == hashMap.end()){
            
                if(start++ != 0)
                    cout<<"/"; 
                cout<<*it2;
            }
                   
            hashMap[*it2] = 1;
        }
        cout<<endl;
    }

}

/*Compute unioun of two vectors*/
vector<char> UnionSet(vector<char> s1, vector<char> s2){

	/*Create a hash_map for check of repetedness*/
	unordered_map<char, int> hashMap;
	
	/*Stores the unon result*/
	vector<char> ans;
	
	vector<char>::iterator it;
	
	for(it = s1.begin(); it != s1.end(); it++){
	
		/*Append in result and add to hash MAp*/
		/*Check if char is already present else push it*/
		if(hashMap.find(*it) == hashMap.end()){
		
			ans.push_back(*it);
		
		}
		//ans.push_back(*it);
		hashMap[*it] = 1;
	
	}
	
	for(it = s2.begin(); it!= s2.end(); it++){
	
		/*Check if char is already present else push it*/
		if(hashMap.find(*it) == hashMap.end()){
		
			ans.push_back(*it);
		
		}
	
		hashMap[*it] = 1;
	}
	
	return ans;


}

bool checkEquality(map<char, vector<char> > s1, map<char, vector<char> > s2){

	/*Check number of Elements in all vectors*/
	if(s1.size() == s2.size()){
	
		map<char, vector<char> >::iterator it;
		
		for(it = s1.begin(); it!= s1.end(); it++){
	
			if(it->second.size() != s2[it->first].size())
			
				return false;
	
		}
		
		return true;
	}
	
	return false;

}

vector<char> removeEpsilon(vector<char> list){

	int index = -1;
	
	for(int i = 0;i < list.size();i++){
	
		if(list[i] == '~')
			index = i;
	
	}
	
	if(index == -1)
		return list;
	else{
	
		list.erase(list.begin() + index); 
	
		return list;
	}

}


/*Update the follow Set of non-Terminalss*/
bool computeFollowSet(map<char, vector<char> > &followSet, map<char, vector<char> > firstSet, map<char, vector<string> > grammer, unordered_map<char, int> nullSet){

	map<char, vector<char> > newSet;
	map<char , vector<string> >::iterator it, followIt;
	vector<string>::iterator it2;
	
	/*Iterate through each grammer*/
	for(followIt = grammer.begin();followIt != grammer.end();followIt++){	
	
		vector<char> setTemp = followSet[followIt->first];
		for(it = grammer.begin();it != grammer.end();it++){
			
			for(it2 = it->second.begin(); it2 != it->second.end(); it2++){
			
				string prod = *it2;
				bool check = false;
				for(int i = 0; i <= prod.size(); i++){
				
					if(i == prod.size() && check){
						
							setTemp = UnionSet(setTemp, followSet[it->first]);
							break;
					}
						
					if(prod[i] == followIt->first){
					
						check = true;
						
					
					}else if(check){
						
						if(isTerminal(prod[i])){
						
							vector<char> single;
							single.push_back(prod[i]);
							setTemp = UnionSet(setTemp, single);
							check = false;
							break;
					
						}else{
						
							setTemp = UnionSet(setTemp, removeEpsilon(firstSet[prod[i]]));
					
							/*If it's not Epsilon Production*/
							if(nullSet.find(prod[i]) == nullSet.end()){
								check = false;
								break;
							}
						}	
						
					}
				}
			
			}
		}
		
		newSet[followIt->first] = setTemp;
		//cout<<"Every Production update : -------------------\n";
		//printSet(newSet);
	}
	
	if(!checkEquality(newSet, followSet)){
	
		followSet = newSet;
		return false;
	}
	
	return true;
}

/*Update First Set of non-Terminals*/
bool computeFirstSet(map<char, vector<char> > &firstSet, map<char, vector<string> > grammer, unordered_map<char, int> nullSet){


	bool check = false;

	map<char, vector<char> > newSet;
	map<char , vector<string> >::iterator it;
	vector<string>::iterator it2;

	/*Iterate through each grammer*/	
	for(it = grammer.begin();it != grammer.end();it++){
		
		vector<char> prev, setTemp = firstSet[it->first];
		
		for(it2 = it->second.begin(); it2 != it->second.end(); it2++){
			
			string prod = *it2;
			for(int i = 0; i < prod.size(); i++){

				/*Ignore empty string*/
				if(prod[i] == '~')
					continue;
				
				/*If it's Terminal String*/
				else if(isTerminal(prod[i])){
				
					vector<char> single;
					single.push_back(prod[i]);
					setTemp = UnionSet(setTemp, single);
					break;
				}
				
				/*If its Non-Terminal*/
				else{
				
					setTemp = UnionSet(setTemp, firstSet[prod[i]]);
					
					/*If it's not Epsilon Production*/
					if(nullSet.find(prod[i]) == nullSet.end())
						break;
						
					
				}
			}
			
			setTemp = UnionSet(setTemp, prev);
			prev = setTemp;
			
		}
		
		newSet[it->first] = setTemp;
	}
	
	if(!checkEquality(newSet, firstSet)){
	
		firstSet = newSet;
		return false;
	}
	
	return true;

}


/*Get All Possible Epsilon Productions*/
void getAllEpsilonProductions(map<char, vector<char> > &firstSet, unordered_map<char, int> &nullSet, map<char, vector<string> > grammer){

	map<char , vector<string> >::iterator it;
	vector<string>::iterator it2;

	bool check = true;
	/*Iterate through each grammer*/
	while(check){	
	
		check = false;
		for(it = grammer.begin();it != grammer.end();it++){

			if(nullSet.find(it->first) == nullSet.end()){
			
				for(it2 = it->second.begin(); it2 != it->second.end(); it2++){
				
					string prod = *it2;
					bool check2 = true;
					for(int i = 0; i < prod.size(); i++){
					
						if(nullSet.find(prod[i]) == nullSet.end()){
						
							check2 = false;
							break;
						}
					}
					
					if(check2){
						nullSet[it->first] = 1;
						firstSet[it->first].push_back('~');
						check = true;
						break;
					}
				}
			
			}
		}
		
		
	}

}

/*Store set of character for which this prod works*/
vector<char> getSetofChar(map<char, vector<char> > firstSet, map<char, vector<char> > followSet, unordered_map<char, int> nullSet, char p, string prod){

	unordered_map<char, int> previous;
	vector<char> setOfChar;
	
	if(prod[0] == '~'){
		setOfChar = followSet[p];
		return setOfChar;
	}
	
	int count = 0;
	for(int i = 0;i < prod.size();i++){
		
		if(isTerminal(prod[i])){
		
			count = 1;
			vector<char> temp;
			temp.push_back(prod[i]);
			setOfChar = UnionSet(setOfChar, temp);
			break;
		
		}
		
		setOfChar = UnionSet(setOfChar, firstSet[prod[i]]);
		
		if(find(firstSet[prod[i]].begin(), firstSet[prod[i]].end(), '~') == firstSet[prod[i]].end()){
		
			count = 1;
			break;
			
		}
	
	}
	
	if(count == 0)
		setOfChar = UnionSet(setOfChar, followSet[p]);
	
	return setOfChar;
}

/*Create LL(1) Parser Tables grammer will contain all*/
void createLLTable(map<char, vector<char> > firstSet, map<char, vector<char> > followSet, unordered_map<char, int> nullSet, map<char, vector<string> > grammer){

	/*Insert T[A,a] for every Prod A->Y first(Y) = a if first(Y) contains e then add Y prod to every rule in follow(Y)*/
	
	/*
		Table declared as unordered_map< pair<char, char> , string > T[A,a] = Production
	
	*/
	
	
	map< pair<char, char>, string > TableLL;
	
	Terminals['$'] = 1;
	unordered_map<char, int>::iterator it1, it2;
	for(it1 = nonTerminals.begin(); it1 != nonTerminals.end(); it1++){
	
		for(it2 = Terminals.begin(); it2 != Terminals.end(); it2++){
		
			TableLL[make_pair(it1->first, it2->first)] = "";
		}
	
	}
	
	map<char , vector<string> >::iterator it;
	
	vector<string>::iterator it3;
	
	for(it = grammer.begin(); it != grammer.end(); it++){
	
		for(it3 = it->second.begin(); it3 != it->second.end();it3++){
		
			vector<char> setChar = getSetofChar(firstSet, followSet, nullSet, it->first, *it3);
			for(int i = 0;i < setChar.size();i++){
			
				if(setChar[i] == '~')
					continue;
					
				if(TableLL[make_pair(it->first, setChar[i])].size() == 0)
					TableLL[make_pair(it->first, setChar[i])] = *it3;
				else{
				
					cout<<"This is not LL(1) Grammer..........."<<endl;
					return;
				}
			}
			
		}
	}
	
	cout<<"This is LL(1) Grammer.........."<<endl;
	
}


/*Driver code for Program*/
int main(){


		/*Stores Grammer for change*/
		map<char, vector<string> > grammer, pureGrammer;
				
		/*Stores first and FollowSet set of each NonTerminal and */
		map<char, vector<char> > firstSet, followSet;

		/*Stores the null set of grammer*/    
		unordered_map<char, int> nullSet;
		
		string line;
		
		cout<<"Original Grammer : "<<endl;
		
		int index = 0;
		while(getline(cin, line)){

		    cout<<line<<endl;
		    
		    /*Insert into map for further use*/
		    //vector<string> temp;
		    grammer[line[0]] = vector<string>();
		    grammer[line[0]] = vector<string>();
		 	firstSet[line[0]] = vector<char>();
		 	followSet[line[0]] = vector<char>();
		 	
		 	if(index++ == 0)
		 		followSet[line[0]].push_back('$');
		 		
		    nonTerminals[line[0]] = 1;
		    /*Tokenize the string for parsing multiple productions*/
		    stringstream check(line.substr(2));
				
			string intermediate; 
	  
			/* Tokenizing w.r.t. space '/' */
			while(getline(check, intermediate, '/')){       
		    
		    	pureGrammer[line[0]].push_back(intermediate);
		        if(intermediate.compare("~") == 0){
		        
		        	/*Insert in hash_map*/
		            nullSet[line[0]] = 1;
		            firstSet[line[0]].push_back('~');
		            //cout<<"Got this as nullSet : "<<line[0]<<endl;
		            continue;
		        }
		        /*Append to vector after tokenization*/
		        //cout<<intermediate<<"->"<<endl;
		        grammer[line[0]].push_back(intermediate);

		    
		    }
		     

		}
		
		//printMap(grammer);
		cout<<"---------------------------"<<endl;
		getSetofTerminals(grammer);
		
		getAllEpsilonProductions(firstSet, nullSet, grammer);
		//printSet(firstSet);
		
		/*
		
		Rules to compute FIRST set:-
		
			If x-> ~, is a production rule, then add Є to FIRST(x).
			If X->Y1 Y2 Y3….Yn is a production,
				FIRST(X) = FIRST(Y1)
				If FIRST(Y1) contains Є then FIRST(X) = { FIRST(Y1) – Є } U { FIRST(Y2) }
				If FIRST (Yi) contains Є for all i = 1 to n, then add Є to FIRST(X).
		
		*/
		
		/* Ignore epsilon for first step compute till we can't get any extra set*/
		/*
		map< char , vector<char> > temp;
		*/
		while(true){
		
			if(computeFirstSet(firstSet, grammer, nullSet)){
			
				break;
			}
			
		}
		
		cout<<"First Set :- "<<endl;
		printSet(firstSet);
		
		cout<<"----------------------------------\n";
		
		//printSet(followSet);
		while(true){
		
			if(computeFollowSet(followSet, firstSet, grammer, nullSet)){
			
				break;
			}
			
			//printSet(followSet);
			//cout<<"\n----------------------------------\n";
		}
		
		cout<<"Follow Set :- "<<endl;
		printSet(followSet);
		
		cout<<"----------------------------------\n";
		
		createLLTable(firstSet, followSet, nullSet, pureGrammer);
		
		return 0;
		
}
