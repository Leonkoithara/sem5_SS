#include <iostream>
#include <malloc.h>
using namespace std;

int main()
{
    int n, avg_waiting=0, avg_tat=0, i, j;

    cout << "Enter number of processes:";
    cin >> n;

	int *bt = (int*)malloc(n*sizeof(n));
	int *waiting_time = (int*)malloc(n*sizeof(n));
	int *tat = (int*)malloc(n*sizeof(n));


    cout<<"Enter Process Burst Time\n";
    for(i = 0;i < n;i++)
    {
        cin>>bt[i];
    }
 
 
    for(i=0;i<n;i++)
    {
        waiting_time[i]=0;
        for(j=0;j<i;j++)
            waiting_time[i]+=bt[j];
    }
 
    cout<<"\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";
 
    for(i = 0;i < n;i++)
    {
        tat[i]=bt[i]+waiting_time[i];
        avg_waiting += waiting_time[i];
        avg_tat += tat[i];
        cout<<"\nP["<<i+1<<"]"<<"\t\t"<<bt[i]<<"\t\t"<<waiting_time[i]<<"\t\t"<<tat[i];
    }
 
    avg_waiting/=i;
    avg_tat /= i;

    cout<<"\n\nAverage Waiting Time:"<<avg_waiting;
    cout<<"\nAverage Turnaround Time:"<<avg_tat;
 
    return 0;
}
