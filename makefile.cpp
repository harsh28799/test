#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ofstream file;
	file.open("file.docx", ios::out);
	srand(time(0));
	for(int i=0;i<100;i++)
	{
		int key=i+1;
		int value=rand()%1000000;
		file<<key<<' '<<value<<'\n';
	}
	return 0;
}
