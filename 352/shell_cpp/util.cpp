#include "util.h"
int identify_string(string toID){
	for (int i = 0; i < 11; ++i) {
		if(toID.compare(codes[i]) == 0){
			return i;
		}
	}
	return 4;
}

/*
 * This is a util function to print out the vector
 */
void print_vec(vector<string>* toprint){
	cout << "----------" << endl;
	cout << "printing vector" << endl;
	for (int i = 0;i<toprint->size();i++) {
		cout << toprint->at(i) << endl;
	}
	cout << "size:" << toprint->size() << endl;
	cout << "----------" << endl;
}

/**
 * This function takes a string and breaks it up to its components according to " ", ";", "|", and other 
 * reserved keywords
 * The function then places these values inside the vector pointer
 * @input string to break apart
 */

int find(char tofind, vector<char> dividers){
	for (int i = 0; i < dividers.size(); ++i) {
		if(tofind == dividers.at(i))
			return 1;
	}
	return 0;
}

void write_to_file(int fd[]){
	ofstream myfile;
	myfile.open ("example.txt");
	myfile << fd[PIPE_READ];
}
void break_string(string input, vector<string> * topush,char divider,int keep){
	string temp = "";
	for (int i = 0; i< input.length(); ++i){
		if(input.at(i) == divider){
			if(temp.length()>0)
				(*topush).push_back(temp);
			if(keep == 1)
				(*topush).push_back(string(1,input.at(i)));
			temp = "";
		}
		else
			temp += input.at(i);
	}
	(*topush).push_back(temp);
}

void break_string(string input, vector<string> * topush, vector<char> dividers,int keep){
	string temp = "";
	for (int i = 0; i< input.length(); ++i){
		if(find(input.at(i),dividers)){
			if(temp.length()>0)
				(*topush).push_back(temp);
			if(keep == 1)
				(*topush).push_back(string(1,input.at(i)));
			temp = "";
		}
		else
			temp += input.at(i);
	}
	(*topush).push_back(temp);
}

vector<string> read_file(string filename){
	vector<string> topass_back;
	ifstream myfile;
	string line;
	myfile.open (filename);
	if (myfile.is_open())
	{
		while (getline (myfile,line) )
		{
			topass_back.push_back(line);
		}
		myfile.close();
	}
	return topass_back;
}
