#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

int number_of_philosophers;
double time_to_die;
double time_to_eat;
double time_to_sleep;
int number_of_time_each_philosopher_must_eat;
int opt = 0;
pthread_mutex_t* forks;
pthread_mutex_t m_tab;
int tab[] = {0,0,0,0,0};

void *philo(void *i){
    long p_num = ((long) i) % number_of_philosophers;
    printf("p%ld started to exist.\n", p_num);
    while(1){
    // lock tab
	pthread_mutex_lock(&m_tab);
	if(tab[p_num + 2]){
	    // unlock tab
	    pthread_mutex_unlock(&m_tab);
	    printf("p%ld >> ZZZ\n", p_num);
	    fflush(stdout);
	} else {
	    // put true to locked forks
	    tab[p_num + 1] = 1;
	    tab[p_num]     = 1;
	
	    // unlock tab
	    pthread_mutex_unlock(&m_tab);

	    pthread_mutex_lock(&forks[p_num + 1]);
	    pthread_mutex_lock(&forks[p_num]);
	    //wait
	    printf("p%ld >> MIAM MIAM MIAM\n", p_num);
	    fflush(stdout);
	
	    //unlock fi
	    //unlock fi+1
	    printf("p%ld >> WAS GOOD\n", p_num);
	    pthread_mutex_unlock(&forks[p_num + 1]);
	    pthread_mutex_unlock(&forks[p_num]);

	    //lock tab
	    pthread_mutex_lock(&m_tab);
	
	    //put false to unlocked forks
	    tab[p_num + 1] = 0;
	    tab[p_num]     = 0;
	
	    //unlock tab
	    pthread_mutex_unlock(&m_tab);
	}
    }
    
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
