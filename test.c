#include <unistd.h> // close(), dup2(), pipe(), fork(), execve()
#include <sys/wait.h> // wait()
#include <fcntl.h> // open()

#define CHILD 0
#define IN 0
#define OUT 1

int	main(int argc, char *argv[], char *envp[])
{
	/* 변수 선언 */
	int pipe_fd[2];
	int infile_fd;
	int outfile_fd;
	char *cmd1[] = { "ls", NULL };			// execve() 함수의 두번 째 인자로 사용.
	char *cmd2[] = { "wc", "-l", NULL };	// execve() 함수의 두번 째 인자로 사용.
	pid_t pid;

	/* infile 열기 */
	infile_fd = open("infile", O_RDONLY); // open infile

	/* outfile 열기 */
	outfile_fd = open("outfile", O_WRONLY | O_TRUNC | O_CREAT | 0644);
	// > outfile 과 동일하게 옵션 추가.
	// O_WRONLY : 쓰기 가능하게 열기
	// O_TRUNC : 열면서 파일 사이즈를 0으로 만들기 (내용 초기화)
	// O_CREAT : 파일이 없으면 새로 만들기.
	// 0644(umask) : O_CREAT 옵션시, 만들어진 파일의 권한 설정.

	/* infile 내용을 표준 입력(fd = 0)으로 받기 */
	dup2(infile_fd, STDIN_FILENO);

	/* 기존 infile_fd 닫아주기 */
	close(infile_fd);

	/* pipe 생성 */
	// 두 개의 pipe fd를 반환 받을 배열(size = 2 이상) 필요. (매개 변수로 넣어줌)
	// pipe_fd[0] = 파이프 읽기 부분의 fd.
	// pipe_fd[1] = 파이프 쓰기 부분의 fd.
	// 파이프 쓰기 부분에 써진 내용은 파이프 읽기 부분으로 읽을 수 있음.
	pipe(pipe_fd);

	/* 자식 프로세스 생성 */
	pid = fork(); // pid = 0 (child process), pid > 0 (parent process), pid = -1 (error)
	if (pid == CHILD)
	{
		/* 자식 프로세스 */
		dup2(pipe_fd[OUT], STDOUT_FILENO); // 표준 출력으로 출력되는 내용을 pipe_fd[OUT]으로 출력.
		close(pipe_fd[IN]); // pipe_fd[IN] close.
		close(pipe_fd[OUT]); // pipe_fd[OUT] close.
		execve("/bin/ls", cmd1, NULL);
		/* execve() */
		// 첫번 째 인자 = 명령어(ls) 프로그램의 경로.
		// 두번 째 인자 = { "명령어 이름(ls)", "명령어 옵션(-l)", NULL } 형식의 배열. (맨 끝에 NULL 넣어줘야 함.)
		// 세번 째 인자 = { "KEY=VALUE", NULL } 형식의 새로 만들어서 넘겨줄 환경 변수들의 배열. (맨 끝에 NULL 넣어줘야 함.)
		// ls 명령어는 결과를 표준 출력으로 출력.
		// 전에 dup2() 함수를 사용했기 때문에 pipe_fd[OUT] 으로 출력하게 됨.
	}

	/* 부모 프로세스 */
	wait(0); // 자식 프로세스가 끝날 때까지 대기 and 자식 프로세스가 좀비 프로세스 되는 것 방지.
	
	/* 자식 프로세스가 끝나고, pipe_fd[IN]에 자식 프로세스의 결과 값이 넣어진 상태 */
	dup2(pipe_fd[IN], STDIN_FILENO); // pipe_fd[IN] 내용을 표준 입력으로 받기.
	dup2(outfile_fd, STDOUT_FILENO); // 표준 출력으로 출력되는 내용을 outfile_fd로 출력.
	close(pipe_fd[IN]); // pipe_fd[IN] close.
	close(pipe_fd[OUT]); // pipe_fd[OUT] close.
	close(outfile_fd); // outfile_fd close.
	execve("/usr/bin/wc", cmd2, NULL);
	// 표준 입력으로 받은 내용에 대해 wc 명령어 결과를 표준 출력으로 출력.
	// 전에 dup2() 함수를 사용했기 때문에 outfile_fd 로 출력하게 됨.

	return 0;
}
