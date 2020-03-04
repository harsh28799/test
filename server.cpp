#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 8080

using namespace std;

int main()
{
	int sid=socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
	int addrlen=sizeof(addr);
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=INADDR_ANY;
	addr.sin_port=htons(PORT);

	bind(sid, (struct sockaddr *)&addr, sizeof(addr));
	listen(sid, 3);

	int conn=accept(sid, (struct sockaddr *)&addr, (socklen_t *)&addrlen);

	char to[]="connection established!\n";
	char from[1024]={0};
	int v=read(conn, from, 1024);
	send(conn, &to, strlen(to), 0);

	cout<<"client: "<<from<<endl;
	cout<<"server: "<<to<<endl;

	int hit=0;

	queue <pair<int, int>> q1;

	for(int i=0;i<50;i++)
	{
		int key, value;
		int a=read(conn, &key, sizeof(key));
		cout<<"key received:"<<key<<endl;

		bool flag=true;

		queue <pair<int, int>> temp=q1;
		while(!temp.empty())
		{
			pair <int, int> w=temp.front();
			temp.pop();
			if(w.first==key)
			{
				value=w.second;
				flag=false;
			}
		}
		if(flag==true)
		{
			if(q1.size()==3)
				q1.pop();
			ifstream file;
			file.open("file.docx", ios::in);
			file.seekg(0);
			for(int k=0;k<100;k++)
			{
				int x, y;
				file>>x>>y;
				if(x==key)
				{
					value=y;
					q1.push(make_pair(key, value));
					break;
				}
			}
		}
		else
		{
			hit++;
		}
	
		send(conn, &value, sizeof(value), 0);
	}

	char req[1024]={0};
	int a=read(conn, req, 1024);
	send(conn, &hit, sizeof(hit), 0);
	cout<<"no of hits: "<<hit<<endl;

	return 0;
}
