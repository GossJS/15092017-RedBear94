#include <iostream>
#include <cstdlib> // ��� system
#include <fstream>
#include <string>
#include <vector>
#include <locale.h>

// ���������� �.�. s4107 - ���������� ��������� �������� 

using namespace std;

// ��������� ������� �������
inline void rus( void ) 
    {     
        setlocale( LC_CTYPE, ".1251" );
        setlocale( LC_MONETARY, ".1251" );

        return;
    }

struct info //��������� info - ���������������� ��������������� ������ �� ����� � ip
{
	vector<string> ip;
    vector<string> platform;
};

int main() 
{ 
	rus();	// ��������� ������� �������
	cout << "��������� ������ ������" << endl;
	
	// ������ ����� ��������
	string platforms[] = {"Linux", "iPhone", "iPad", "Macintosh", "X11", "Windows", "Windows NT 6.2"};
	//						0		1			2		3			4		5				6(5)
	string platforms_name_for_print[] = {"Android", "iPhone", "iPad", "Mac OS", "Linux", "Windows"};
	int mass_platforms[6] = {0, 0, 0, 0, 0, 0};

	// �������� ����� ��� ���������� ������ � ���������� res
	ifstream file("info.txt",ios::in);
	if (!file) {
		cout<<"���� �� ������!"<<endl;
		cout<<"��������� ���� � ������ info.txt � ����� � ����������"<<endl;
		system("pause");
		exit(1);
	}
	char buf[15000]; 
	vector<string> res; 
	int k = 0;
	do{ 
		file.getline(&buf[0],sizeof(buf)); 
		res.push_back(buf); 
		k++;
	}while(!file.eof()); 
	
	// ������� ���������
	info statistica;
	string tmp, tmp2;
	bool flag,flag2,flag3 = false;
	// �������������� ������ �� res � �� ������ � ���������
	for (int i=0; i<res.size(); i++)
	{
		for(int j=0; j<res[i].size(); j++)
		{
			if (res[i][j] != ' ' && flag != true)
			{
				tmp += res[i][j];
			}
			else
			{
				flag = true;
			}
			
			if(res[i][j] == '(')
			{
				flag2 = true;
			}
			else
			{
				if(res[i][j] == ';' || res[i][j] == ')')
				{
					flag2 = false;
					flag3 = true;
				}
				else
				{
					if (flag2 == true)
					{
						if (flag3 !=true)
						{
						tmp2 += res[i][j];
						}
					}
				}
			}
		}
		statistica.ip.push_back(tmp);
		statistica.platform.push_back(tmp2);
		flag = false;
		flag2 = false;
		flag3=false;
		tmp = "";
		tmp2 = "";
	}
	
	// ������� ���������� ������� ip ������	� ������������ ������ ip_counter
	int n = statistica.ip.size(), *ip_counter;
	ip_counter = (int*) malloc(n * sizeof(ip_counter[0])); 
	for (int i=0; i<statistica.ip.size(); i++)
	{
		ip_counter[i] = 0;
	}

	for(int i=0; i<statistica.ip.size(); i++)
	{
		for(int j=0; j<statistica.ip.size(); j++)
		{
			if(statistica.ip[i]==statistica.ip[j])
			{
				ip_counter[i] += 1;
			}
		}
	}
	
	// ���������� ����� ����������� ��������
	for(int i=0; i<statistica.platform.size(); i++)
	{
		for (int j=0; j<6; j++)
		{
			if(statistica.platform[i] == platforms[j])
			{
				mass_platforms[j] += 1;
			}
		}
		if(statistica.platform[i] == platforms[6])
		{
			mass_platforms[5] += 1;
		}
	}

	//����� ����������� ������������ ������ + ���-�� ����������� (����� ���� � ������������ ip)
	/*
	for(int j=0; j<statistica.ip.size(); j++)
		{
			cout << statistica.ip[j] <<" " << statistica.platform[j] << " " << ip_counter[j] << endl;
		}
	*/

	// ���-�� ��������� ����� �� ������������ ����������
	cout << endl << "����� ���� ��������:" << endl;
	for(int i=0; i<6; i++)
	{
	cout << platforms_name_for_print[i] << " " << mass_platforms[i] << endl;
	}

	// ������ ip � ������������ ������ ���������
	int max = ip_counter[0];
	int max_ip;
	for(int i=0; i<statistica.ip.size(); i++)
	{
		if (ip_counter[i] > max) 
		{
			max = ip_counter[i];
			max_ip = i;
        }
	}
	cout << endl << "����� ������ IP - ������: " << statistica.ip[max_ip] << endl;

	// ��������� �������� IP � �� ����� ����������� (��� ����������) 
	int counter = 0;
	vector<string> ip_norm,ip_5_max;
	int * conect_counter = (int*) malloc(n * sizeof(conect_counter[0])); 
	for (int i=0; i<statistica.ip.size(); i++)
	{
		conect_counter[i] = 0;
	}
	int num = 0;
	for(int i=0; i<statistica.ip.size(); i++)
	{
		for(int j=0; j<ip_norm.size(); j++)
		{
			if (ip_norm[j]==statistica.ip[i])
			{
				counter = 1;
			}
		}
		if (counter != 1)
		{
			ip_norm.push_back(statistica.ip[i]);
			conect_counter[num] = ip_counter[i];
			++num;
		}
		counter=0;
	}
	
	/*
	cout << endl;
	for(int i=0; i<ip_norm.size(); i++)
	{
		cout << ip_norm[i] << " " << conect_counter[i] << endl;
	}
	*/

	// ����� 5-�� ip � ������������ ������ ����������� 
	// (������������� ������� � ����������)
	int temp;
	string temp2;
	for(int i=0; i<ip_norm.size() - 1; i++)
	{
		for(int j=0; j<ip_norm.size() - i - 1; j++)
		{
			if (conect_counter[j] < conect_counter[j + 1]) {
                // ������ �������� �������
                temp = conect_counter[j];
                conect_counter[j] = conect_counter[j + 1];
                conect_counter[j + 1] = temp;
				temp2 = ip_norm[j];
                ip_norm[j] = ip_norm[j + 1];
                ip_norm[j + 1] = temp2;
            }
		}
	}

	cout << endl;
	cout << "������ ����� ���� ��������:" << endl;
	for(int i=0; i<5; i++)
	{
		cout << ip_norm[i] << " " << conect_counter[i] << endl;
	}
	cout << endl;

	// ���������� ������
	free(ip_counter);

	cout << "������ ��������� ���������" << endl;

	system("pause"); // ���� ������������ MS Visual Studio
    return 0; 
}