#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream file;
	file.open("file.docx", ios::in);
	int search=(rand()%100)+1;
	int key, value;
	for(int i=0;i<100;i++)
	{
		file>>key;
		file>>value;
		if(key==search)
		{
			cout<<key<<":"<<value<<endl;
			break;
		}	
	}

	return 0;
}
