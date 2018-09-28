#include <iostream>
using namespace std;
 
int main()
{
    int i,j,n,total=0,pos,temp;
    float avg_waiting_time,avg_tat;

    cout << "Enter number of process: ";
    cin >> n;

	int burst_time[n],p[n],waiting_time[n],tat[n];
 
    cout << "Enter Burst Time:\n";

    for(int i = 0;i < n;i++)
    {
        cin >> burst_time[i];
        p[i]=i+1;
    }
 
    for(int i = 0;i < n;i++)
    {
        pos=i;
        for(int j = i+1;j < n;j++)
        {
            if(burst_time[j]<burst_time[pos])
                pos=j;
        }
 
        temp=burst_time[i];
        burst_time[i]=burst_time[pos];
        burst_time[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    waiting_time[0]=0;
 
    for(int i=1;i < n;i++)
    {
        waiting_time[i]=0;
        for(int j = 0;j < i;j++)
            waiting_time[i]+=burst_time[j];
 
        total+=waiting_time[i];
    }
 
    avg_waiting_time=(float)total/n;
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=burst_time[i]+waiting_time[i];
        total+=tat[i];
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",p[i],burst_time[i],waiting_time[i],tat[i]);
    }
 
    avg_tat=(float)total/n;
    printf("\n\nAverage Waiting Time=%f",avg_waiting_time);
    printf("\nAverage Turnaround Time=%f\n",avg_tat);

	return 0;
}
