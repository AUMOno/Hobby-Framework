inet_server_dir = internet_server
output_dir = compiled
tcp_socket_obj = socket_tcp
clang_flags = -O0 -lssl -lcrypto

all:
	@tput setaf 1
	@echo 'The terminal output has been suppressed until the socket process sends a message.'
	@tput setaf 2
	@echo '|'
	@echo '||'
	@echo '|||'
	@echo '||||'
	@tput setaf 4
	@echo '----------------'
	@tput setaf 3

	@mkdir -p $(output_dir) # Will make a directory, or ignore the request error if it already exists.
	@clang -o openssl $(inet_server_dir)/$(tcp_socket_obj).c $(clang_flags) -o $(output_dir)/$(tcp_socket_obj)
	@./compiled/socket_tcp

	@tput setaf 6
	@echo '----------------'
	@tput setaf 9
	@echo '||||'
	@echo '|||'
	@echo '||'
	@echo '|'
	@tput setaf 7
	@echo 'This is the end of the makefile'