#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <functional>
using namespace std;
hash<string> strhash;
int appendlist[26];
vector<string> totallist;
vector<size_t> totalints;
int solution =0;
bool iselementin(string hashed){
	cout << "entering elementcheck++++++++++++++++++++++++++++++++++++" << endl;
	ifstream inputfile;	
	inputfile.open("output.txt");
	if(inputfile.is_open()){
		string sofar = "";	
		while(inputfile.good()){
			char toread;
			inputfile>>toread;
			if(toread!='a')
				sofar += toread;
			if(toread=='a'){
				if(sofar==hashed){
					return true;	
				}
				sofar = "";
			}
		}
	}
	return false;
}
void printvec(){
	for (int i = 0; i < totallist.size(); i++) {
		cout<<totallist.at(i)<<" ";
	}
}
void converter(int i1){
	ifstream inputfile;
	ofstream outputfile;
	inputfile.open("input.txt");
	inputfile>> noskipws;
	int offset=i1;
	string sofar = "";
	if(inputfile.is_open()){
		while(inputfile.good()){
			char toread;
			inputfile>>toread;
			toread = tolower(toread);
			if(toread != ' ' && toread != 10){
				toread = (toread-97+offset)%26+97;
				sofar += toread;
			}
			if(sofar !="" &&(toread == ' ' || toread == 10)){
				totallist.push_back(sofar);			
				cout<<"changed to"<<sofar<<endl;
				sofar = "";
			}
		}
	}
}
void hashvector(){
	for (int i = 0; i < totallist.size(); i++) {
		size_t hashresult = strhash(totallist.at(i));
		string toreplace = to_string(hashresult);
		totallist.at(i) = toreplace;	
		cout<<"hash value is:"<<totallist.at(i)<<endl;
	}
}
void dicchecker(){
	int counter =0;
	for (int i = 0; i <26; i++) {
		cout<<"checking offset"<<i<<"---------------------------";
		converter(i);
		hashvector();		
		for (int j = 0; j < totallist.size(); j++) {
			string tocheck = totallist.at(j);
			cout << "checking"<<tocheck<<endl;
			if(iselementin(tocheck))	
				appendlist[i]++;	
		}
		totallist.clear();
	}
}
void outputer(){
	ifstream inputfile;
	ofstream outputfile;
	inputfile.open("words.txt");
	outputfile.open("hash.txt");
	inputfile>>noskipws;	
	int counter =0;
	if(inputfile.is_open()){
		string tohash="";
		while(inputfile.good()){
			char toprint;
			inputfile>>toprint;
			toprint = tolower(toprint);
			if(toprint!=10)
				tohash+=toprint;
			cout<<toprint;
			if(toprint==10){
				size_t hashed = strhash(tohash);	
				totalints.push_back(hashed);
				outputfile<<hashed<<endl;
				tohash = "";
			}
			counter++;
		}
	}
	sort(totalints.begin(),totalints.end());
	outputfile.close();
	outputfile.open("output.txt");
	for (int i = 0; i < totalints.size(); i++) {
		string hashadd = to_string(totalints.at(i))+"a";
		outputfile<<hashadd;
	}
	outputfile.close();
}
int decider(){	
	int largest = 0;
	int index =0;
	for (int i = 0; i < 26; i++) {
		if(appendlist[i]>largest){
			largest = appendlist[i];
			index = i;
		}
	}
	int solution = 26-index;
	cout << "the solution is probably"<<solution<< endl;
	return index;
}
void decoder(){
	totallist.empty();
	converter(solution);
	cout<<"solution probably is: ";
	for (int i = 0; i < totallist.size(); i++) {
		cout << totallist.at(i) << " ";
	}
	cout<<endl;
}
int main(int argc,char *argv[]){
	if(*argv[1]=='o')
	outputer();
	dicchecker();
	solution = decider();
	decoder();
}
