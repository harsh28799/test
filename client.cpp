#include<bits/stdc++.h>

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>

#define PORT 8080

using namespace std;

int main()
{
	int sid=socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

	connect(sid, (struct sockaddr *)&addr, sizeof(addr));

	char to[]="requesting connection!\n";
	send(sid, &to, sizeof(to), 0);

	char from[1024]={0};
	int v=read(sid, &from, sizeof(from));

	cout<<"client: "<<to<<endl;
	cout<<"server: "<<from<<endl;

	
	srand(time(0));
	int start=(int)clock();
	for(int i=0;i<50;i++)
	{
		int value;
		int key=(rand()%100);
		send(sid, &key, sizeof(key), 0);
		int a=read(sid, &value, sizeof(value));
		cout<<"key:value--->"<<key<<":"<<value<<endl;
	}
	int finish=(int)clock();

	char to2[]="Give me the hit count\n";
	send(sid, &to2, sizeof(to), 0);
	int hit;
	int a=read(sid, &hit, sizeof(hit));

	cout<<"hit ratio:"<<(hit/50)<<endl;
	cout<<"latency: "<<finish-start<<endl;

	return 0;
}
