# 42Seoul-pipex
## 목표
- 쉘 명령어를 다루는 프로그램 만들기.
- 프로그램을 ./pipex file1 cmd1 cmd2 file2 명령어로 실행시, 쉘에서 < file1 cmd1 | cmd2 > file2 를 실행한 것과 동일하게 출력되어야 함.
- file1, file2는 파일 이름이고 cmd1, cmd2는 쉘 명령어.
```
ex)
$> ./pipex infile "ls -l" "wc -l" outfile
= 쉘에서 아래와 같이 입력했을 때처럼 동작해야 함.
$> < infile ls -l | wc -l > outfile
```
- Makefile로 프로그램 컴파일 해야하고, 리링크 방지해줘야 함.
- 예상치 못한 종료(segmentation fault, double free...)가 생기면 안되며, 메모리 누수 나면 안됨.
- 만약 에러가 발생하는 경우로 의심된다면, 쉘 명령어로 실행했을 때와 동일하게 처리하면 됨.
## 보너스
- 다중 명령어 가능하게 구현.
```
ex)
$> ./pipex file1 cmd1 cmd2 cmd3 cmd4 ... file2
```
- 첫번 째 command line 인자 값이 "here_doc"일 경우, "<, >" 가 아닌 "<< >>" 로 수행되도록 구현.
```
ex)
$> ./pipex here_doc LIMITER cmd cmd1 file
= 쉘에서 아래와 같이 입력했을 때처럼 동작해야 함.
$> cmd << LIMITER | cmd1 >> file
```
