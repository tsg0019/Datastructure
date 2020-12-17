#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "queueADT.h"
#define N (simulStats->numCust)
#define S (simulStats->totSvcTime)
#define W (simulStats->totWaitTime)
typedef struct {
	int custNum;	//손님의 대기번호
	int arriveTime;	//손님의 도착시간
	int startTime;	//손님의 응대시작시간
	int svcTime;	//손님이 요구하는 응대시간(1~10사이 integer number)
}custStatus;
typedef struct simStats{//이 구조체는 simulation전반적인 state를 저장하기 위해 존재
	int numCust;	//응대한 총 손님 수
	int totSvcTime;	//응대한 총 시간
	int totWaitTime;//응대한 총 시간
	int maxQueueSize;	// 수용할 수 있는 최대 대기열 수
}simStats;
void decide_parameters(int* days_to_simulation, int* numb_of_workers);
int gen_xtoy(int x, int y);
bool iscusarr(void);
void generate_cus(QUEUE* queue,int* arriveTime, int* custNum);
void setsimStats(simStats* simulStats);
void process_serving(QUEUE* queue, simStats* simulStats, int* numb_of_workers);
void watingprocess(QUEUE* queue,simStats* simulStats);
void one_day_simulation(QUEUE* queue, int* currenttime, int* custNum, simStats* simulStats,int* numb_of_workers,int* left_cust);
int main(void) {
	srand(time(NULL));
	simStats* simulStats = (simStats*)malloc(sizeof(simStats));;
	setsimStats(simulStats);
	int* days_to_simulation = (int*)malloc(sizeof(int)); *days_to_simulation = 0;
	int* numb_of_workers = (int*)malloc(sizeof(int)); *numb_of_workers = 1;
	int* left_cust = (int*)malloc(sizeof(int)); *left_cust = 0;
	decide_parameters(days_to_simulation, numb_of_workers);
	for (int i = 0 ; i < *(int*)days_to_simulation ; i++) {
		printf("\n\n*******%d번째 날 simulation 시작!", i+1);
		int* currenttime = (int*)malloc(sizeof(int)); *currenttime = 0;//현재 시간 초기화
		int* custNum = (int*)malloc(sizeof(int)); *custNum = 1;//현재 손님 수 초기화
		QUEUE* queue = createQueue();//queue변수 선언
		one_day_simulation(queue, currenttime, custNum,simulStats,numb_of_workers,left_cust);//1day에 대한 simulation 수행
	}//이 후 전체 일 수에 대한 simulation의 결과 print
	printf("\n\n===================%d일간의 simulation 결과===================\n", *days_to_simulation);
	printf("simulation 일 수 : %d\n근무자 수 : %d\n", *days_to_simulation,*numb_of_workers);
	printf("average service time : %f\n", (double)S / *days_to_simulation);
	printf("average rest time : %f\n",(double)W / *days_to_simulation);
	printf("응대하지 못한 평균 손님 수 : %f\n", (double)*left_cust / *days_to_simulation);
	printf("=============================================================\n");
	return 0;
}
void decide_parameters(int* days_to_simulation, int* numb_of_workers) {
	printf("몇일에 대해 시뮬레이션 할 지 입력해 주세요 : ");
	scanf("%d", days_to_simulation); //몇일에 대해 simulation을 수행할 지 날짜를 정함
	printf("몇명의 직원을 둘 지 입력해주세요 : ");
	scanf("%d", numb_of_workers);	//몇 명의 직원을 사용할 지 정함
	return;
}
void one_day_simulation(QUEUE* queue, int* currenttime, int* custNum, simStats* simulStats,int* numb_of_workers,int* left_cust) {
	int* temp_customer_num = (int*)malloc(sizeof(int)); *temp_customer_num = N;//simulator의 변수들을 임시저장
	int* temp_customer_svctime = (int*)malloc(sizeof(int)); *temp_customer_svctime = S;
	int* temp_customer_waittime = (int*)malloc(sizeof(int)); *temp_customer_waittime = W;
	while (*currenttime < 480) {	//하루에 480분 동안만 장사
		if (iscusarr()) {		//is customer arrived? (단,손님은 1분에 최대 1명만 도착한다 가정)
			if (((queue->count) + 1) > (simulStats->maxQueueSize)){		//queue의 max를 넘어서게되는 case
				(*currenttime)++;
				simulStats->totSvcTime++;
			}
			else {
				generate_cus(queue, currenttime, custNum);	//해당 시간에 손님이 도착했다면 손님에 관한 정보를 생성 후 enqueue해 줌
			}
		}
		if (!emptyQueue(queue)) {	//queue가 빈상태가 아니라면 현재는 서빙을 하고 있다는 뜻
			process_serving(queue, simulStats, numb_of_workers);
		}
		else {						//queue가 비어있다면 현재는 쉬는시간
			watingprocess(queue, simulStats);
		}
		(*currenttime)++;
	}
	printf("\n<%d분동안의 응대 분석 결과 보고>", *currenttime);
	printf("\n마지막 queue의 count : %d", queue->count);
	printf("\n총 고객 수 : %d\ntotal sevice time: %d", N - *temp_customer_num, S - *temp_customer_svctime);
	printf("\ntotal rest time : %d \n", W - *temp_customer_waittime);
	*temp_customer_num = N;//각각의 변수의 값 최신화
	*temp_customer_svctime = S;//최신화를 해야만 그 다음 날짜의 data를 구할 수 있음
	*temp_customer_waittime = W;
	*left_cust += queue->count;
	destroyQueue(queue);
	return;
}
int gen_xtoy(int x, int y){//x~y사이 integer값을 uniformy random하게 generate하는 함수
	return (rand() % (y - x + 1)) + x;
}
bool iscusarr(void) {	//customer이 도착했는지 1/4의 확률로 나타남
	if (gen_xtoy(1,4) == 4) {
		return true;
	}
	return false;
}
void generate_cus(QUEUE* queue,int* currenttime,int* custNum) {
	custStatus* customer = (custStatus*)malloc(sizeof(custStatus));
	if (!customer)
		printf("손님 생성에 overflow가 발생\n");
	customer->arriveTime = *currenttime;		//현재의 시간이 곧 손님의 도착시간임
	customer->custNum = *custNum;			
	(*custNum)++;								//손님수 증가
	customer->startTime = NULL;				//서빙시작시간은 아직 미정이므로NULL
	customer->svcTime = gen_xtoy(1, 10);	//손님을 서빙하는데 1~10분 소요
	enqueue(queue, customer);	//customer이라는 구조체를 enqueue함, 즉, dataPtr은 customer이라는 구조체를 가리킴
	return;
}
void setsimStats(simStats* simulStats) {	//선언한 구조체를 초기화하는 역할을 하는 함수
	simulStats->maxQueueSize = 1000000;
	simulStats->numCust = 0;
	simulStats->totSvcTime = 0;
	simulStats->totWaitTime = 0;
	return;
}
void process_serving(QUEUE* queue, simStats* simulStats,int* numb_of_workers) {
	custStatus* ptrcust;	//dequeue한 dataPtr의 정보를 받는 구조체포인터
	if ((*(custStatus*)(queue->front->dataptr)).svcTime > *numb_of_workers) {
		(*(custStatus*)(queue->front->dataptr)).svcTime -= *numb_of_workers;
	}
	else {
		int iteration = *numb_of_workers;//직원의 수만큼 iteration수를 정함
		while ( (iteration >= 0) && !(emptyQueue(queue)) ) {
			if ((*(custStatus*)(queue->front->dataptr)).svcTime == 0) {
				dequeue(queue,&ptrcust);//front node의 svcTime이 0이라면 dequeue 후 svcTime을 감소시켜야 함
				simulStats->numCust++;//dequeue를 한 번 했다는 뜻은 한명의 손님을 응대 완료하였다는 뜻
			}//dequeue후에 emptyqueue가 될 수도 있으므로 if문 한번 더 수행
			if (!emptyQueue(queue))//현재 emptyqueue가 아니라면
				(*(custStatus*)(queue->front->dataptr)).svcTime--;
			iteration--;//iteration = 0이 될때까지 1씩 감소하면서 svc시간 감소시킴
		 }
	}
	simulStats->totSvcTime++;//총 svc시간 1 cycle동안 수행된 일이므로 1감소시킴
	return;
}
void watingprocess(QUEUE* queue, simStats* simulStats) {
	(simulStats->totWaitTime)++;//총 손님 대기 시간 1증가시킨 후 return
	return;
}
