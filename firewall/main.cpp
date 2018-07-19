
#include "server.h"

void send_to_server(std::shared_ptr<Server> server, std::tuple mes)
{
	int ip = mes.get<1>();
	if (!server.is_blocked_user(ip))
	{
		if (server.check_amount_per_week(ip, static_cast<int>(seconds)) < 50)
		{
			server.add_to_db(mes, static_cast<int>(seconds));
			server.increment_mes_counter(ip);
		}
		else
			server.block_user(ip);
	}
}

int main(int argc, char **argv)
{
	std::shared_ptr<Server> server(new Server);
	unsigned int seconds = static_cast<unsigned int>(time(NULL));
	std::tuple<int, unsigned int, std::string> message(18921937, seconds, "text of message");

	send_to_server(server, message);

	return (0);
}
