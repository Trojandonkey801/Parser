/**
 * This file provides the functions that creates the reader and changer queues.
 * It operates by creating a queue of function pointers and parameters, initialized
 * in queue.h
 * When it reads a string, it parses the job, and then creates struct.
 * It then pushes it back onto a queue, and allows for pulling.
 *
 */
#include "queue.h"
#define  Q_SIZE 50
string sreader_q[Q_SIZE];
int sread_func_c = 0;
int sread_func_s = 0;
int sread_func_e = 0;
string schange_q[Q_SIZE];
int schange_func_c = 0;
int schange_func_s = 0;
int schange_func_e = 0;
reader reader_q[Q_SIZE];
int read_func_c = 0;
int read_func_s = 0;
int read_func_e = 0;
changer change_q[Q_SIZE];
int change_func_c = 0;
int change_func_s = 0;
int change_func_e = 0;
/**
 * This is the main function that pushes a job into the queue.
 * It either reads in search, insert, or delete from the command string.
 * It then pushes the correct string into the queue.
 * and then creates a struct, and then pushes it back on the queue
 * @param string job
 * 		The job that should get parsed and pushed back into a queue.
 */
void spush_func(string job){
	//When the command is a search
	if(job.find("search") != string::npos){
		sreader_q[sread_func_e] = job;
		sread_func_e = (sread_func_e + 1)%Q_SIZE;
		sread_func_c++;
	}
	//When the command is an insert
	if(job.find("insert") != string::npos){
		schange_q[schange_func_e] = job;
		schange_func_e = (schange_func_e + 1)%Q_SIZE;
	schange_func_c++;
	}
	if(job.find("delete") != string::npos){
		schange_q[schange_func_e] = job;
		schange_func_e = (schange_func_e + 1)%Q_SIZE;
	schange_func_c++;
	}
}

/**
 * The function that pulls from the queue of readers.
 * If the queue is empty, then it returns a canary String value, so that
 * the workers can quit.
 */
string spull_reader(){
	if(sread_func_c == 0)
		return "NOENTRYLEFT";
	sread_func_c--;
	string temp =  sreader_q[sread_func_s];
	sread_func_s = (sread_func_s + 1)%Q_SIZE;
	return temp;
}

/**
 * The function that pulls from the queue of changers(insert/delete)
 * If the queue is empty, then it returns a canary String value, so that
 * so that the workers can quit
 */
string spull_changer(){
	if(schange_func_c == 0)
		return "NOENTRYLEFT";
	schange_func_c--;
	string temp =  schange_q[schange_func_s];
	schange_func_s = (schange_func_s + 1)%Q_SIZE;
	return temp;
}
/**
 * This is the main function that pushes a job into the queue.
 * It either reads in search, insert, or delete from the command string.
 * It then creates the corresponding function pointer, takes the param
 * and then creates a struct, and then pushes it back on the queue
 * @param string job
 * 		The job that should get parsed and pushed back into a queue.
 */
void push_func(string job){
	//When the command is a search
	if(job.find("search") != string::npos){
		struct reader temp =
		{&search,strip_paren(job)};
		read_func_c++;
		reader_q[read_func_e] = temp;
		read_func_e = (read_func_e + 1)%100;
	}
	//When the command is an insert
	if(job.find("insert") != string::npos){
		struct changer temp =
		{&insert_node,strip_paren(job)};
		change_func_c++;
		change_q[change_func_e] = temp;
		change_func_e = (change_func_e + 1)%100;
	}
	if(job.find("delete") != string::npos){
		struct changer temp =
		{&del_from_tree,strip_paren(job)};
		change_func_c++;
		change_q[change_func_e] = temp;
		change_func_e = (change_func_e + 1)%100;
	}
}

/**
 * The function that pulls from the queue of readers.
 * If the queue is empty, then it returns an empty struct, so that
 * the workers can quit.
 */
struct reader pull_reader(){
	if(read_func_c == 0){
		struct reader temp = {NULL,-1};
		return temp;
	}
	read_func_c--;
	struct reader temp = reader_q[read_func_s];
	read_func_s = (read_func_s + 1)%100;
	return temp;
}

/**
 * The function that pulls from the queue of changers(insert/delete)
 * If the queue is empty, then it returns an empty struct,
 * so that the workers can quit
 */
struct changer pull_changer(){
	if(change_func_c == 0){
		struct changer temp = {NULL,-1};
		return temp;
	}
	change_func_c--;
	struct changer temp = change_q[change_func_s];
	change_func_s = (change_func_s + 1)%100;
	return temp;
}
//happy thanksgiving, my love. im eternally grateful for you
