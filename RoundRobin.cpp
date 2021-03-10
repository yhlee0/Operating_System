//라운드로빈 구현


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//라운드 로빈은 도착시간 순서대로 배열시켜야 한다.

int burst_t[100];      //동작 시간
int arr_t[100];        //도착 시간
int wait_t[100];       //대기 시간
int total_t[100];      //모든 프로세스의 전체 동작 시간
int rem_t[100];       //남은 동작 시간

void swap(int* aa, int* bb) //*aa와 *bb의 값을 바꾸는 함수
{
	int temp = *aa;
	*aa = *bb;
	*bb = temp;
}




int generate_process(int n) {

	printf("프로세서 번호\t프로세스의 버스트타임\t프로세스의 도착시간\n");
	srand(time(NULL)); //rand 함수 호출 전에 선언하여 시간을 기준으로 초기화되는 난수 생성하도록 함
	for (int i = 0; i < n; i++) //n이 0이거나 음수인 경우 아예 프로세서가 만들어지지 않음
	{
		burst_t[i] = rand() % 50 + 1; //버스트타임=1이상 50이하의 수로 구성된 난수 생성
		arr_t[i] = rand() % 50 + 1; //도착시간=1이상 50이하의 수로 구성된 난수 생성
		rem_t[i] = burst_t[i]; //어차피 처음엔 동작시간과 남은 동작시간이 같기 때문
		//printf("%d \t\t %d \t\t %d\n", i+1, burst_t[i],arr_t[i]); //확인용
	} //for문에서 입력받은 n만큼 버스트타임, 도착시간, 남은동작시간을 각각 생성해여 배열에 저장

	//프로세스를 도착순으로 정렬 (insertion sort 알고리즘 사용)
	int i, j, key, temp1, temp2;
	i = 0;
	for (j = 1; j < n; j++) {
		key = arr_t[j];
		temp1 = burst_t[j];
		temp2 = rem_t[j];
		i = j - 1;
		while (i >= 0 && arr_t[i] > key) {
			arr_t[i + 1] = arr_t[i];
			burst_t[i + 1] = burst_t[i];
			rem_t[i + 1] = rem_t[i];
			i = i - 1;
		}
		arr_t[i + 1] = key;
		burst_t[i + 1] = temp1;
		rem_t[i + 1] = temp2;
	}

	for (i = 0; i < n; i++)
		printf("%d \t\t\t %d \t\t\t %d\n", i + 1, burst_t[i], arr_t[i]);
	//도착 순서대로 정렬된 것을 '프로세서 번호, 버스트타임, 도착시간' 순서대로 출력한다.

}

int RR(int n, int timeQuantum) {

	int count = 0;
	int tt = 0;//전체소요시간
	int temp = 0;
	float ava_wait_t = 0;//평균 대기시간
	float ava_total_t = 0ㅣ//평균소요시간
	int i;



	while (1) {
		for (i = 0, count = 0; i < n; i++) {
			temp = timeQuantum; //temp에 timeQuantum값 대입
			if (rem_t[i] == 0) {
				count++;
				//printf("%d  %d  %d\n", i,  n , count);
				continue;

			}
			if (rem_t[i] > timeQuantum)
					//프로세서의 남은 동작 시간이 timeQauntum보다 크면
				rem_t[i] = rem_t[i] - timeQuantum; 
					//rem_t[i]에 (남은동작시간-타임퀀텀)의 값으로 갱신
			else if (rem_t[i] >= 0) //만약 남은 시간이 0보다 크거나 같으면 실행
			{
				temp = rem_t[i];
				rem_t[i] = 0;
			}
			tt = tt + temp; //tt(총 소요시간)에 temp의 값을 더함
			total_t[i] = tt; //total_t[i]에 각 프로세서 별로 총 소요시간을 저장한다.
			//printf("%d , %d, %d, %d, %d\n", i, count,n, rem_t[i], total_t[i]);
		}

		if (n == count)
			break;
	}

	for (i = 0; i < n; i++) {
		wait_t[i] = total_t[i] - burst_t[i];
		ava_wait_t = ava_wait_t + wait_t[i];
		ava_total_t = ava_total_t + total_t[i];
	}

	ava_wait_t = ava_wait_t / n; //n으로 나눠서 평균대기시간을 구함
	ava_total_t = ava_total_t / n; //n으로 나눠서 평균소요시간을 구함

	//프로세스 번호, 버스트시간, 대기시간, 소요시간 출력
	printf("프로세스 번호 \t 버스트시간 \t 대기시간\t 소요시간 \n");
	for (i = 0; i < n; i++)
		printf("%d \t\t %d \t\t %d \t\t %d \n", i + 1, burst_t[i], wait_t[i], total_t[i]);
	//평균 대기시간, 평균 소요시간을 출력
	printf("평균 대기 시간 : %f", ava_wait_t);
	printf("\n평균 소요 시간 : %f", ava_total_t);
}
int main() {
	int n; //'프로세서 개수'를 위해 변수 선언
	int timeQuantum; //'타임퀀텀'을 위해 변수 선언
//입력
	printf("100 이하의 프로세서의 개수를 입력하세요.\n"); 
	scanf("%d", &n); //프로세서 개수를 n에 저장
	printf("타임퀀텀을 입력하세요.\n");
	scanf("%d", &timeQuantum); //timeQuantum 입력받아 저장
	generate_process(n); //n을 generate_process함수에 인수로 보냄
	RR(n, timeQuantum); //n이랑 timeQuantum을 RR함수에 인수로 보냄
}
