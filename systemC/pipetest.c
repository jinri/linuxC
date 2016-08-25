#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main()
{
int pfds[2];
if ( pipe(pfds) == 0 )
{
    if ( fork() == 0 )//子进程
    {
        close(1);//关闭标准输出
        close( pfds[0] );//关闭管道读
        dup2( pfds[1], 1 );//管道的写文件描述符复制到进程的输出
        execlp( "ls", "ls","-l", NULL );//执行ls -l 输出写入管道
    }
    else
    {
        close(0);
        close( pfds[1] );
        dup2( pfds[0], 0 );//管道的读文件描述符复制到进程的输入
		wait(NULL);
        execlp( "wc", "wc", "-l", NULL );//执行wc -l 将管道读取数据作为wc命令的输入
     }
}
return 0;
}
