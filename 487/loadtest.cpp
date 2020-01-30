#include<pthread.h>
#include<semaphore.h>
#include<iostream>
sem_t a,b,c,d;
void* load(void *input){
	int array_to_add[20000];
	for (int i = 0; i < 20000; ++i) {
		array_to_add[i]+=2000;
		while(array_to_add[i]>0){
			array_to_add[i] /= 2;
		}
	std::cout << array_to_add[i] << std::endl;
	}
	return NULL;
}
pthread_t *e,*f,*g,*h;
int main(int argc, char *argv[])
{
	pthread_create(e,NULL,load,NULL);
	pthread_create(f,NULL,load,NULL);
	pthread_create(g,NULL,load,NULL);
	pthread_create(h,NULL,load,NULL);
	pthread_join(*e,NULL);
	pthread_join(*f,NULL);
	pthread_join(*g,NULL);
	pthread_join(*h,NULL);
	return 0;
}
	
