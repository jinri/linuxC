 #include <unistd.h>
 #include <stdio.h>

int main(){
	int ret;
	ret = execl("/bin/ls", "ls", NULL);
	if(ret == -1)
	perror("execl");
	return 0;
}
