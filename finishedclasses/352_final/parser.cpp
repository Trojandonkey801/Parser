/**
 * This file provides the parser utility functions in order to * deal with the text, parse the file, and put them into the
 * respective locations and vectors
 *
 */
#include "parser.h"
ifstream inputfile;
vector<string> topass;
vector<string> read_t;
string read_s;
string read_m;
vector<string> read_c;

/**
 * Function to open the file, and push back each of the lines of string
 * into a string.
 * @param string inFile the name of the file to handle.
 */
void fileOpen(string inFile){
	inputfile.open(inFile);
	if(!inputfile){
		cout << "FILE IS NOT FOUND, or other error has occured" << endl;
		exit(1);
	}
	else{
		ifstream fileIn(inFile);
		string templine;
		while(getline(fileIn,templine)){
			istringstream iSS(templine);
			if(iSS.str().length() != 0){
				topass.push_back(iSS.str());
			}
		}
	}
}

/**
 * The function that reads in the number of search functions.
 * @param string input
 * 			The string containing the string "Search threads"
 */
string read_s_name(string input){
	string toparse = "";
	if(input.find("Search threads:") != string::npos){
		bool read = false;
		for (int i = 0; i < input.size(); ++i) {
			if(input.at(i)== ':'){
				read = true;
				continue;
			}
			if(read)
				toparse += input.at(i);
		}
	}
	return stripout(toparse);
}

/**
 * The function that reads in the number of modify functions.
 * @param string input
 * 			The string containing the string "Modify threads"
 */
string read_m_name(string input){
	string toparse = "";
	if(input.find("Modify threads:") != string::npos){
		bool read = false;
		for (int i = 0; i < input.size(); ++i) {
			if(input.at(i)== ':'){
				read = true;
				continue;
			}
			if(read)
				toparse += input.at(i);
		}
	}
	return stripout(toparse);
}

/**
 * The function that reads in each of the invocations to the functions,
 * seperated by "|"
 * @param string input
 * 			The string containing the string "|" and the invocations
 */
vector<string> read_c_name(string input){
	vector<string> toreturn;
	stringstream SStream(input);
	string buffer;
	char divider = '|';
	while(getline(SStream,buffer,divider)){
		if(stripout(buffer).length() != 0){
			toreturn.push_back(stripout(buffer));
		}
	}
	return toreturn;
}

/**
 * The function that reads in each of the initial trees
 * seperated by ","
 * @param string input
 * 			The string containing the string "," and the tree nodes
 */
vector<string> read_t_name(string input){
	vector<string> toreturn;
	stringstream SStream(input);
	string buffer;
	char divider = ',';
	while(getline(SStream,buffer,divider)){
		if(stripout(buffer).length() != 0){
			toreturn.push_back(stripout(buffer));
		}
	}
	return toreturn;
}
/**
 * A old function that reads in a tree, and pushes back each tree element
 * into a vector
 * @param string input
 * 		A string that contains each of the lines of a tree
 */
vector<string> read_tree(string input){
	vector<string> toreturn;
	std::istringstream f(input);
	std::string line;
	while (std::getline(f, line)) {
		toreturn.push_back(line);
	}
	return toreturn;
}

/**
 * A helper function that removes all spaces
 * @param string tostrip
 * 		the string to strip of ' '
 * @return string
 * 		the string that no longer contains ' '
 */
string strip(string tostrip){
	string toreturn = "";
	for (int i = 0; i < tostrip.size(); ++i) {
		if(tostrip.at(i) != (' ')){
			toreturn += tostrip.at(i);
		}
	}
	return toreturn;
}

/**
 * A helper function that removes outer spaces
 * @param string tostrip
 * 		the string to strip of ' '
 * @return string
 * 		the string that no longer contains ' '
 */
string stripout(string tostrip){
	string temp = "";
	bool beg = false;
	for (int i = 0; i < tostrip.size(); i++) {
		if(tostrip.at(i) != ' ')
			beg = true;
		if(beg){
			temp += tostrip.at(i);
		}
	}
	beg = false;
	string tempp = "";
	for (int i = temp.length()-1; i >= 0 ; i--) {
		if(temp.at(i) != ' ')
			beg = true;
		if(beg){
			tempp = temp.at(i) + tempp;
		}
	}
	return tempp;
}

/**
 * A helper function that removes outer parentheses.
 * Used to call in tree values
 * @param string tostrip
 * 		the string to strip of ( and  )
 * @return string
 * 		the string that no longer contains ( and )
 */
int strip_paren(string tostrip){
	string toreturn = "";
	bool startread = false;
	for (int i = 0; i < tostrip.length(); ++i) {
		if(tostrip.at(i) == '('){
			startread = true;
			continue;
		}
		if(tostrip.at(i) == ')'){
			break;
		}
		if(startread){
			toreturn += tostrip.at(i);
		}
	}
	return stoi(toreturn);
}

/**
 * helper function that prints out each value in a vector
 * @param vector<string> toprint 
 * 		the vector to print
 */
void print_vec(vector<string> toprint){
	cout << "----------" << endl;
	cout << "printing vector" << endl;
	for (int i = 0;i<toprint.size();i++) {
		cout << toprint.at(i) << endl;
	}
	cout << "size:" << toprint.size() << endl;
	cout << "----------" << endl;
}

/**
 * utility function to fill in missing commas
 *
 */
string fix_tree(string tofix){
	for (int i = 0; i < tofix.length(); ++i) {
		if(i < tofix.length()-1)
			if(tofix.at(i) == 'b' || tofix.at(i) == 'r' || tofix.at(i) == 'f')
				if(tofix.at(i+1) != ',')
					tofix.at(i) = ',';
	}
	return tofix;
}
/**
 * utility function that calls the helper functions to parse the lines.
 *
 */
void parselines(){
	int index = 0;
	string tree = "";
	//Parses in until it fids "Search"
	while(topass.at(index).find("Search") == string::npos){
		tree += fix_tree(topass.at(index));
		index++;
		if(index == topass.size())
			break;
	}
	//call read_t_name in order to parse the tree names
	read_t = read_t_name(tree);
	//Parses in until it fids "Modify"
	while(topass.at(index).find("Modify") == string::npos){
		read_s = read_s_name(topass.at(index));
		index++;
		if(index == topass.size())
			break;
	}
	while(topass.at(index).find("||") == string::npos){
		read_m = read_m_name(topass.at(index));
		index++;
		if(index == topass.size())
			break;
	}
	//Parses in until it fids "||"
	//Start reading commands
	string commands = "";
	while(index < topass.size()){
		commands += topass.at(index);
		index++;
	}
	read_c = read_c_name(commands);
}

/**
 * Utility function to printout the preorder of the final tree
 *
 *
 */

void preorder_print(node_t *root, bool right){
	if(root == NULL)
		return;
	if(root == NIL){
		std::cout << "f";
		if(!right)
			cout << ",";
	}
	else{
		std::cout << root->key;
		if(root->color == 0){
			std::cout << "b,";
		}
		else{
			std::cout << "r,";
		}
		preorder_print(root->left,false);
		preorder_print(root->right, right & true);
	}
}
