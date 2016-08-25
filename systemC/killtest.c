#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
void main()
{
        pid_t pid;
        int status;
        if((pid = fork()) < 0)//创建一个子进程
        {
                printf("fork() error!\n");
                exit(-1);
        }
        else if(pid == 0)//让子进程处于休眠状态
        {
                printf("this is the child process!!\n");
                sleep(1000);
        }
        else
        {
                sleep(1);
                int i = waitpid(pid, &status, WNOHANG);//跳用waitpid函数来返回子进程的状态
                printf("%d\n",i);
                printf("the state is %d\n",status);
                kill(pid,SIGKILL);//跳用kill函数传递SIGKILL命令
             //kill(pid,SIGINT);//跳用kill函数传递SIGINT命令
                sleep(3);//等待kill执行完毕
                int j = waitpid(pid, &status, WNOHANG);//查看进程结束的返回状态！
                printf("%d\n",j);
                printf("the state is %d\n",status);
        }
}
