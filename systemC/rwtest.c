#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE  10

int main()
{
	char buf[BUFFER_SIZE];
	int n;
	while((n = read(0,buf,BUFFER_SIZE)) > 0)
	{
		write(1,buf,n);
	}
	return 0;
}
