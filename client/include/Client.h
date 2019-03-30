#ifndef CLIENT_H_
#define CLIENT_H_

class Client {
public:
	Client(const char *serverIP, int serverPort);
	virtual ~Client();
	void connectToServer();
	int getClientSocket();

protected:
	const char* serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
