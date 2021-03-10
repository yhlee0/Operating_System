//FCFS 구현


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//도착시간 순서대로 배열시켜야함

int burst_t[100];      //동작 시간
int arr_t[100];        //도착 시간
int wait_t[100];       //대기 시간
int total_t[100];      //전체 동작 시간

void swap(int* aa, int* bb) //*aa와 *bb의 값을 바꾸는 함수
{	int temp = *aa;
	*aa = *bb;
	*bb = temp;
}

int generate_process(int n) {
	printf("프로세서 번호\t프로세스의 버스트타임\t프로세스의 도착시간\n");
	srand(time(NULL)); //rand 함수 호출 전에 선언하여 시간을 기준으로 초기화되는 난수 생성하도록 함
	for (int i = 0; i < n; i++) { //n이 0이거나 음수인 경우 아예 프로세서가 만들어지지 않음
		burst_t[i] = rand() % 50 + 1;
				       //버스트타임 = 0이상 50이하의 수로 구성된 난수 생성
		arr_t[i] = rand() % 50 + 1; //도착시간=  0이상 50이하의 수로 구성된 난수 생성

		//printf("%d \t\t %d \t\t %d\n", i+1, burst_t[i],arr_t[i]);
	}//프로세서 개수인 n만큼 버스트타임, 도착시간 생성

	//프로세스를 도착순으로 정렬 (insertion sort)
	int i, j, key, temp1;
	i = 0;
	for (j = 1; j < n; j++) {
		key = arr_t[j];
		temp1 = burst_t[j];
		i = j - 1;
		while (i >= 0 && arr_t[i] > key) {
			arr_t[i + 1] = arr_t[i];
			burst_t[i + 1] = burst_t[i];
			i = i - 1;
		}
		arr_t[i + 1] = key;
		burst_t[i + 1] = temp1;
	}

	for (i = 0; i < n; i++)
		printf("%d \t\t\t %d \t\t\t %d\n", i + 1, burst_t[i], arr_t[i]);
	//도착 시간 기준으로 정렬한 후 프로세서 번호, 버스트타임, 도착시간을 출력
}

int FCFS(int n) {
	int wt = 0; //대기시간
	int temp;
	float ava_wait_t = 0; //평균 대기시간
	float ava_total_t = 0; //평균 소요시간
	int i, j, k = 0;

	for (i = 0; i < n; i++) {
		temp = 0;
		for (j = k; j < i; j++)
			temp = temp + burst_t[j]; //이전 버스트 시간을 합해서 저장

		wt = temp - arr_t[i] + arr_t[k];//2
		if (wt <= 0) {
			k = i; //i의 값을 k에 저장하여 이전의 값을 불러올 때 사용
			total_t[i] = burst_t[i] + wait_t[i]; //소요시간 = 버스트 시간 + 대기시간
		}
		else {
			wait_t[i] = wt;
			total_t[i] = burst_t[i] + wait_t[i]; //소요시간 = 버스트 시간 + 대기시간
		}
	}

	for (i = 0; i < n; i++) {
		ava_wait_t = ava_wait_t + wait_t[i]; //대기시간을 모두 더해서 ava_wait_t에 저장
		ava_total_t = ava_total_t + total_t[i]; //소요시간을 모두 더해서 ava_total_t에 저장
	}

	ava_wait_t = ava_wait_t / n; //평균대기시간
	ava_total_t = ava_total_t / n; //평균소요시간

	//출력
	printf("프로세스 번호 \t 버스트시간 \t 대기시간\t 소요시간 \n");
	for (i = 0; i < n; i++)
		printf("%d \t\t %d \t\t %d \t\t %d \n", i + 1, burst_t[i], wait_t[i], total_t[i]);
	printf("평균 대기 시간 : %f", ava_wait_t);
	printf("\n평균 소요 시간 : %f", ava_total_t);
}

int main() {
	int n;

	printf("100 이하의 프로세서의 개수를 입력하세요.\n");
	scanf("%d", &n); //프로세서의 개수를 입력받아 n에 저장
	generate_process(n); //n을 generate_process함수에 인수로 보냄
	FCFS(n); //n을 FCFS함수에 인수로 보냄
}
