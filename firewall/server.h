
#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h> 
# include <sys/socket.h>
# include <netinet/in.h>
#include <netdb.h>

#include <ctime>
#include <iostream>
#include <unordered_map>
#include <tuple>


class Server {

public:

	Server();
	~Server();

	bool	is_blocked_user(int ip);
	int		check_amount_per_week(int ip, int current_time);
	void 	add_to_db(std::pair, int time);
	void 	block_user(int ip);
private:

	std::unordered_map<int, std::pair<unsigned int, std::string>> m_db;


};

#endif
