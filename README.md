# 42Seoul-pipex
## 목표
- 쉘 명령어를 다루는 프로그램 만들기.
- 프로그램을 ./pipex file1 cmd1 cmd2 file2 명령어로 실행시, 쉘에서 < file1 cmd1 | cmd2 > file2 를 실행한 것과 동일하게 출력되어야 함.
- file1, file2는 파일 이름이고 cmd1, cmd2는 쉘 명령어.

## 관련 개념
- 프로그램, 프로세스.
- 문맥 교환(Context Swiching), 프로세스 메모리 구조.
- 프로세스 계층 구조.
- 프로세스간 통신(IPC) 방법 중 파이프(Pipe) 방식.
- 쉘에서 명령어 동작 방식.
- 환경 변수.

## 개발 및 테스트 환경
- Intel CPU 기반 Mac.
- MacOS Version = 12.6.2

## 사용 방법
- make = Mandatory용 실행 파일 생성. (명령어 2개만 실행 가능)
- make bonus = Bonus용 실행 파일 생성. (다중 명령어 및 here_doc 실행 가능)
