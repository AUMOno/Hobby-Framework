@echo off

set inet_server_dir=internet_server
set output_dir=compiled
set tcp_socket_obj=socket_tcp

:start_of_process:

set gcc_flags=-lws2_32

set /p command=Windows-native: { wb for Windows build } Docker: Has the container been built yet? { dy, or dn } 

echo Your input was: %command%

if "%command%"=="wb" (
	if not exist %output_dir% mkdir %output_dir%
	gcc %inet_server_dir%/%tcp_socket_obj%.c %gcc_flags% -o %output_dir%/%tcp_socket_obj%.exe
	"./compiled/socket_tcp.exe"
	pause
	exit

) else if "%command%"=="dn" (
	echo The container is being built. Please allow time for Docker to run its process.
	docker build ./docker -t c_threaded_server
	pause
	exit

) else if "%command%"=="dy" (
	echo The container is being started. Please allow time for Docker to run its process.
	powershell -command docker run -p 127.0.0.1:256:256 --user=root -it -v "${pwd}:/root/env" --rm c_threaded_server
	pause
	exit

) else (
	echo The request which has been received was not recognized.
	pause
	exit
)