#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

int number_of_philosophers;
double time_to_die;
double time_to_eat;
double time_to_sleep;
int number_of_time_each_philosopher_must_eat;
int opt = 0;
pthread_mutex_t* forks;
pthread_mutex_t m_tab;
int tab[];

void *philo(void *i){
    long p_num = ((long) i) % number_of_philosophers;
    
    printf("%ld >> Hello!\n", p_num);
    fflush(stdout);
    return NULL;
}

int main(int argc, char *argv[]) {
  int opt;

  while((opt = getopt(argc, argv, "p:d:e:s:o:")) != -1){
    switch(opt){
    case 'p' :
	number_of_philosophers = atoi(optarg);
	break;
    case 'd' :
	time_to_die = atof(optarg);
	break;
    case 'e' :
	time_to_eat = atof(optarg);
	break;
    case 's' :
	time_to_sleep = atof(optarg);
	break;
    case 'o' :
	number_of_time_each_philosopher_must_eat = atoi(optarg);
	break;
    default  : printf("Missing arguments\n"); 
    }
  }


  /*if(argc < 4) {
	return 1;
    }
    number_of_philosophers = atoi(argv[1]);
    time_to_die = atof(argv[2]);
    time_to_eat = atof(argv[3]);
    time_to_sleep = atof(argv[4]);
    if(argc > 5) {
	opt = 1;
	number_of_time_each_philosopher_must_eat = atoi(argv[5]);
    };*/

  
    pthread_t tid[number_of_philosophers];
    forks = malloc(number_of_philosophers * sizeof(pthread_mutex_t));
    for(int i = 0 ; i < number_of_philosophers ; i++) tab[i] = 0;
    
    for(int i = 0 ; i < number_of_philosophers ; i++){
	pthread_mutex_init(&forks[i] , NULL);
    }
    
    for(int i = 0 ; i < number_of_philosophers ; i++){
	if(pthread_create(&tid[i], NULL, philo, (void *) i) != 0) exit(1);
	pthread_detach(tid[i]);
    }
    
    printf("%d\n", number_of_philosophers);
    return 0;
}
