#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define Thinking 0
#define Hungry 1
#define Eating 2
#define Left (ph_num + (philCount - 1)) % philCount
#define Right (ph_num + 1) % philCount
#define MAX_COUNT 100
#define DINNER_TIME 1000

int cyclesCount;
int philCount;
int* state;
int* full;
int* phil_num;
HANDLE mutex;
HANDLE* S;

void test(int ph_num)
{
	if (state[ph_num] == Hungry && state[Left] != Eating && state[Right] != Eating)
	{
		state[ph_num] = Eating;
		printf("Philospher %d takes fork %d and fork %d and start eating\n", ph_num + 1, Left + 1,
			ph_num + 1);
		ReleaseSemaphore(S[ph_num], 1, NULL);
	}
}


void take_fork(int ph_num)
{
	WaitForSingleObject(mutex, INFINITE);
	state[ph_num] = Hungry;
	printf("Philospher %d is hungry\n", ph_num + 1);
	test(ph_num);
	ReleaseSemaphore(mutex, 1, NULL);
	WaitForSingleObject(S[ph_num], INFINITE);
}


void put_fork(int ph_num)
{
	WaitForSingleObject(mutex, INFINITE);
	state[ph_num] = Thinking;
	printf("Philospher %d stoped eating, put down fork %d and fork %d and thinking\n", ph_num + 1,
		Left + 1, ph_num + 1);
	test(Left);
	test(Right);
	ReleaseSemaphore(mutex, 1, NULL);
}


DWORD WINAPI philospher(void* num)
{
	int full = cyclesCount;
	while (full != 0)
	{
		int* i = (int*)num;
		srand((int)time(0));
		Sleep((rand() + 50) % DINNER_TIME);
		take_fork(*i);
		Sleep((rand() + 50) % DINNER_TIME);
		put_fork(*i);
		full = full - 1;
	}
	return true;
}


int main()
{
	printf("Input number of cycles: ");
	scanf_s("%d", &cyclesCount);
	printf("Input number of philosophers: ");
	scanf_s("%d", &philCount);

	state = (int*)calloc(philCount, sizeof(int));
	phil_num = (int*)calloc(philCount, sizeof(int));
	S = (HANDLE*)calloc(philCount, sizeof(HANDLE));
	int i;
	HANDLE* thread_id = (HANDLE*)calloc(philCount, sizeof(HANDLE));
	mutex = CreateSemaphoreA(NULL, 1, MAX_COUNT, NULL);

	for (i = 0; i < philCount; i++)
		phil_num[i] = i;

	for (i = 0; i < philCount; i++)
		S[i] = CreateSemaphoreA(NULL, 0, MAX_COUNT, NULL);

	for (i = 0; i < philCount;i++)
	{
		thread_id[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philospher, (LPVOID)&phil_num[i], 0,
			NULL);
		printf("Philospher %d is thinking\n", i + 1);
	}

	for (i = 0; i < philCount; i++)
	{
		if (thread_id[i] != NULL)
			WaitForSingleObject(thread_id[i], INFINITE);
	}

	for (i = 0; i < philCount; i++)
	{
		if (S[i] != NULL)
			CloseHandle(S[i]);
		if (thread_id[i] != NULL)
			CloseHandle(thread_id[i]);
	}
	if (mutex != 0)
		CloseHandle(mutex);
	free(state);
	free(phil_num);
	free(thread_id);
	free(S);
}