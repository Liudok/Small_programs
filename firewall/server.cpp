
#include "server.h"

Server::Server() {}

void Server::add_to_db(std::pair mes, int time) {
	std::pair p{
			time,
			mes.second
	};
	m_db.insert(mes.first, p);

}

Server::~Server() {}