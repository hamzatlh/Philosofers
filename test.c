#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void redirect_output(char *file)
{
    int fd;
	int fds[2];
    int old;
    pid_t pid;

	pipe(fds);
    fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fds[1], "nourdin12", 9);
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		char str[10];
    	if (fd < 0)
        	return ;
		read(fds[0], str, 9);
		// str[9] = 0;
    	dup2(fd, STDOUT_FILENO);
		printf("%s\n", str);
		// exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

int main()
{
	printf("hna\n");
    redirect_output("txt.txt");
	// printf("hello\n");
    return 0;
}
