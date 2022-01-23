@echo off

set inet_server_dir=internet_server
set output_dir=compiled
set tcp_socket_obj=socket_tcp

:start_of_process:

set gcc_flags=-lws2_32

echo Hello.
echo.
echo You have a choice to either build from Windows natively, or via an Ubuntu Docker container.
echo.
echo Windows-native uses the command 'wb' ; that stands for Windows build.
echo Docker needs to process if your container is built yet 'db', or 'dr' ; Docker build, or Docker run.
echo.
echo ________________
set /p command=Input your command, and then press enter: 

echo Your input was: %command%

if "%command%"=="wb" (
	if not exist %output_dir% mkdir %output_dir%
	gcc %inet_server_dir%/%tcp_socket_obj%.c %gcc_flags% -o %output_dir%/%tcp_socket_obj%.exe
	"./compiled/socket_tcp.exe"
	pause
	exit

) else if "%command%"=="db" (
	echo The container is being built. Please allow time for Docker to complete its process.
	docker build ./docker -t c_threaded_server
	pause
	exit

) else if "%command%"=="dr" (
	echo The container is being started. Please allow time for Docker to complete its process.
	echo.
	powershell -command docker run -p 127.0.0.1:256:256 --user=root -it -v "${pwd}:/root/env" --rm c_threaded_server
	pause
	exit

) else (
	echo The request received was not recognized.
	pause
	exit
)