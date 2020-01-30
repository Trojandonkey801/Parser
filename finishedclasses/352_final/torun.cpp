/**
 * Main function that is responsible for running the program
e* This creates the reader and writer loops, and then creates the appropriate
 * threads.
 *
 */
#include <unistd.h>
#include "torun.h"
#include <pthread.h>
#include <semaphore.h>
#include <chrono>
sem_t tree;
sem_t readers_t;
sem_t writers_t;
sem_t writer_pull_t;
sem_t output_t;
sem_t waiting_readers_t;
/**
 * Function that splits the input vector into left and right recursive trees.
 * The first element is the root, and it returns the recursively generated
 * left and right trees
 * This is used to take the preorder tree, and create the correct functions
 * @param vector<string> tofind
 * 		The vector containing the root, and left and right trees
 * @return vector<vector<string>>
 * 		returns a vector containing left and right trees
 */
vector<vector<string>> split(vector<string> tofind){
	vector<string> left;
	vector<string> right;
	if(tofind.at(0) != "f"){
		int root = stoi(tofind.at(0).substr(0,tofind.at(0).length()-1));
		int i;
		for (i = 1; i < tofind.size(); ++i) {
			if(tofind.at(i) == "f"){
				continue;
			}
			else{
				int secval = stoi(tofind.at(i).substr(0,tofind.at(i).length()-1));
				if(secval<root){
					left.push_back(tofind.at(i));
				}
				else{
					break;
				}
			}
		}
		for (int j = i; j < tofind.size(); j++) {
			if(tofind.at(j) != "f")
				right.push_back(tofind.at(j));
		}
	}
	vector<vector<string>> toreturn;
	toreturn.push_back(left);
	toreturn.push_back(right);
	return toreturn;
}

/**
 * The function that takes the total tree string, and creates the correct
 * initialized tree.
 * @param vector<string> toinit
 * 		The vector containing the strings for the tree
 * @return node_t*
 * 		Returns the head node after recursively creating the tree
 */
node_t *hard_init(vector<string> toinit){
	if(toinit.size() == 0){
		return NIL;
	}
	node_t *root = create_hard(toinit.at(0));
	vector<vector<string>> temp = split(toinit);
	link(root,hard_init(temp.at(0)),true);
	link(root,hard_init(temp.at(1)),false);
	return root;
}

/**
 * Function that creates the jobs, and pushes them
 * to the vector
 */
void handle_jobs(){
	for (int i = 0; i < read_c.size(); ++i) {
		push_func(read_c.at(i));
	}
}
int read_size = 0;
int change_size = 0;
vector<pthread_t> reader;
vector<pthread_t> changer;

/**
 * Initializes the correct number of readers to a vector,
 * with an initial pthread value of 0
 */
void init_readers(){
	for (int i = 0; i < stoi(read_s); ++i) {
		reader.push_back(0);
	}
}

/**
 * Initializes the correct number of changers to a vector,
 * with an initial pthread value of 0
 */
void init_changers(){
	for (int i = 0; i < stoi(read_m); ++i) {
		changer.push_back(0);
	}
}

/**
 * Helper function that uses a semaphore to write out.
 * @param string towrite
 * 		The string to print
 */
void thread_writer(string towrite){
	sem_wait(&output_t);
	std::cout << towrite << std::endl;
	sem_post(&output_t);
}
int readers = 0;
int waiting_readers = 0;

/**
 * The main reader loop in the reader/writers problem
 * The skeleton code is pulled from the slides provided in class
 */
void *reader_loop(void *input){
	do {

		// Reader incremeents waiting reader
		sem_wait(&waiting_readers_t);
		waiting_readers++;
		sem_post(&waiting_readers_t);

		sem_wait(&tree);

		//Once insdie, decrement waiting reader count
		sem_wait(&waiting_readers_t);
		waiting_readers--;
		sem_post(&waiting_readers_t);
		// The number of readers has now increased by 1
		readers++;
		//If this is the first reader, it signals the writer to wait
		if (readers==1)
			sem_wait(&writers_t);

		//release, so that other readers can also enter
		sem_post(&tree);
		//pull struc that contains a reader instruction
		//and param
		sem_wait(&readers_t);
		struct reader temp = pull_reader();
		sem_post(&readers_t);

		bool leave = false;
		//Check if there are any more instructions
		if(temp.read_func == NULL && temp.param == -1){
			leave = true;
		}
		else{
			bool result = temp.read_func(temp.param);
			sem_wait(&output_t);
			if(result)
				std::cout << "search(" << temp.param <<
					")-> true, performed by thread:" << pthread_self()<< std::endl;
			else
				std::cout << "search(" << temp.param << 
					")-> false, performed by thread:" << pthread_self() << std::endl;
			sem_post(&output_t);
		}

		sem_wait(&tree);  //reader is done, it is now going to leave
		readers--;

		//The last reader out allows the other readers in
		if (readers == 0)
			sem_post(&writers_t);         // writers can enter

		sem_post(&tree); // reader leaves
		if(leave)
			break;
	} while(true);
	return NULL;
}
/**
 * Writers half of the reader/writers problem
 * The skeleton code is pulled from the slides in the notes
 * @param void *input
 * 		The void param required for thread functions
 *
 */
void *writers_loop(void *input){
	do {
		// writer requests for critical section
		bool leave = false;
		sem_wait(&writers_t);
		struct changer temp = pull_changer();
		if(temp.change_func == NULL && temp.param == -1)
			leave = true;
		else{
			temp.change_func(temp.param);
		}
		sem_post(&writers_t);
		if(leave)
			break;
	} while(true);
	return NULL;
}

/**
 * initializer function for all of the sempahores
 *
 */
void init_sems(){
	sem_init(&tree, 0, 1);
	sem_init(&readers_t, 0, 1);
	sem_init(&output_t, 0, 1);
	sem_init(&waiting_readers_t, 0, 1);
	sem_init(&writer_pull_t, 0, 1);
	sem_init(&writers_t, 0, 1);
}
/*
 * The main function
 * The main function does several things. It starts by measuring the code execution.
 * It then creates the jobs, initializes the readers, and the creates the threads.
 * It waits for all of the created threds to join.
 * The it prints out the time, and the preorder of the tree
 */

int main(int argc, char *argv[])
{
	auto start = std::chrono::system_clock::now();
	string filename;
	if(argc>1)
		filename = argv[1];
	else{
		std::cout << "NO FILE WAS PROVIDED" << std::endl;
		exit(1);
	}
	free(NIL);
	NIL = create_node(-1,NULL);
	NIL->color = BLACK;
	NIL->right = NULL;
	NIL->left = NULL;
	fileOpen(filename);
	parselines();
	head = hard_init(read_t);
	init_sems();
	handle_jobs();
	init_readers();
	init_changers();
	//Creating the readers and changer threads
	for (int i = 0; i < changer.size(); ++i) {
		pthread_create(&changer.at(i),NULL,writers_loop,NULL);
	}
	for (int i = 0; i < reader.size(); ++i) {
		pthread_create(&reader.at(i),NULL,reader_loop,NULL);
	}
	//waiting for the reader changer threads to join
	for (int i = 0; i < reader.size(); ++i) {
		pthread_join(reader.at(i),NULL);
	}
	for (int i = 0; i < changer.size(); ++i) {
		pthread_join(changer.at(i),NULL);
	}
	//std::cout << correctness(head,0) << std::endl;
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "finished computation at " << std::ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << "s\n";
    preorder_print(head,true);
	//Clean, and free all the nodes
	clean_tree(head);
	//Clean, and free the NIL node.
	free(NIL);
	return 0;
}
