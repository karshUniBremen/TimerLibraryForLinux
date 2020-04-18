/*
 * btimerTest.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: karsh
 */
#include "btimerTest.h"

using namespace std;

void print(void* arg){
	cout<< "tick tok"<<endl;
}

void print2(void* arg){
	cout<< "tick tok2"<<endl;
}



btimer t(btimer::mode_e::PERIODIC);
//btimer t2(btimer::mode_e::PERIODIC,print2,NULL);


void* btimerTest(void* arg){

	t.registerCB(print,NULL);
	t.start(3000);
   // t2.start(2000);

	int counter =0;
	while(1){
		counter++;
		cout<< "counter: "<<counter<<endl;

		if(t.isExpired()==true){
			cout<< "timer t expired"<<endl;
		}

//		if(t2.isExpired()==true){
//			cout<< "timer t2 expired"<<endl;
//		}

		if(counter== 10){
			cout<<"stopping @ "<< counter <<endl;
			t.stop();
		}

		if(counter == 20){
			cout<<"restarting @ "<< counter <<endl;
			t.start(2000);
		}

		if(counter== 30){
			cout<<"stopping @ "<< counter <<endl;
			t.stop();
		}

		if(counter>=40){
			cout<<"Timer test done: success"<< endl;
			exit(0);
		}
		sleep(1);
	}
}
