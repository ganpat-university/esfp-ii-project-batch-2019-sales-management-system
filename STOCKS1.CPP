#include"iostream"
#include"fstream"
#include"cstring"
#include"stdio.h"
#include"stdlib.h"
#include"unistd.h"
#include"/home/deep/Desktop/getch.cpp"
using namespace std;
class stock
{
private:
	int itm, stk, prc;
	char n[20];
public:
	stock()
	{
		itm = stk = prc = 0;
		strcpy(n, "/0");
	}

	stock(int a, int b, char *c, int d)
	{
		itm = a;
		stk = b;
		strcpy(n, c);
		prc = d;
	}

	void input()
	{
		cout << "enter item number: ";
		cin >> itm;
		cout << "enter item name: ";
		cin >> n;
		cout << "enter no. of items in stock: ";
		cin >> stk;
		cout << "enter the price of the item: ";
		cin >> prc;
	}


	void show()
	{
		cout << "\n" << itm << "\t" << n << "\t" << stk << "\t" << prc;
	}

	void recitm(int a)
	{
		itm = a;
	}
	void recn(char a[])
	{
		strcpy(n,a);
	}
	void recstk(int a)
	{
		stk = a;
	}
	void recprc(int a)
	{
		prc = a;
	}
	int retitm()
	{
		return itm;
	}
	int retstk()
	{
		return stk;
	}
	char *retn()
	{
		return n;
	}
	int retprc()
	{
		return prc;
	}



	//Add a record to stock
	void addstk()
	{
		fstream a2;
		stock m2;
		a2.open("stock.dat", ios::app | ios::binary);
		if (!a2)
			cout << "unable to open";
		else
		{
			m2.input();
			if (strlen(m2.retn())<3)
				cout << "enter a name with atleast 3 character\n";
			else if (m2.retstk()<100)
				cout << "stock entered should be minimum 100\n";
			else if (m2.retprc() <= 1)
				cout << "enter a price more than rs.1\n";
			else
			{
				a2.write((char *)&m2, sizeof(m2));
				cout << "record inserted\n";
			}
			a2.close();
		}
	}


	//display all records
	void dispitm()
	{
		fstream a3;
		stock m3;
		int x, k;
		a3.open("stock.dat", ios::in | ios::binary);
		if (!a3)
			cout << "unable to open";
		else
		{

				cout << "\nitem no  name stock price";
				while (!a3.eof())
				{
					m3.show();
					a3.read((char *)&m3, sizeof(m3));
				}
			
			a3.close();
		}
	}


	//delete a record from stock
	void delstk()
	{
		fstream a4, b4;
		stock m4;
		int z, found = 0;
		a4.open("stock.dat", ios::in | ios::binary);
		b4.open("list.dat", ios::out | ios::binary);
		if (!a4 || !b4)
			cout << "stock empty";
		else
		{
			cout << "\nenter the item no. which we want delete from the list ";
			cin >> z;
			while (!a4.eof())
			{
				found=1;
				a4.read((char *)&m4, sizeof(m4));
				if (z != m4.retitm())
					b4.write((char *)&m4, sizeof(m4));
			}
			if (found == 0)
			{
				unlink("list.dat");
				cout << "item no." << z << "not found\n";
			}
			else
			{
				unlink("stock.dat");
				cout << z << "item no record deleted";
				z = rename("list.dat", "stock.dat");
			}
			a4.close();
			b4.close();
		}
	}

	//To update a record from stock
	void updstk()
	{
		fstream a;
		stock m;
		int x, found = 0, p, q;
		char n[20];
		a.open("stock.dat", ios::in | ios::out | ios::binary);
		if (!a)
			cout << "enter item no: to search ";
		cin >> x;
		a.read((char *)&m, sizeof(m));
		while (!a.eof())
		{
			if (m.retitm() == x)
			{
				found = 1;
				break;
			}
			a.read((char *)&m, sizeof(m));
		}
		if (found == 0)
			cout << "item no: not exist";
		else
		{
			cout << "1.change the item no.\n";
			cout << "2.change name\n";
			cout << "3.change no. of stock\n";
			cout << "4.change price of the item\n";
			cout << "5.exit\n\n";
			cin >> q;
			switch (q)
			{
			case 1:
				cout << "enter new item no. ";
				cin >> p;
				m.recitm(p);
				break;
			case 2:
				cout << "enter new name ";
				cin >> n;
				m.recn(n);
				break;
			case 3:
				cout << "enter new stock ";
				cin >> p;
				m.recstk(p);
				break;
			case 4:
				cout << "enter new price of item ";
				cin >> p;
				m.recprc(p);
				break;
			default:
				cout << "\nsorry....wrong choice";
				goto man;
			}
			a.seekg(-(long)sizeof(m), ios::cur);
			a.write((char *)&m, sizeof(m));
			cout << "stock record updated";
		man:
			a.close();
		}
	}
};

	
int main()
	{
		int ch;
		stock sl;
		do
		{
			system("clear");
			cout<<"---------------------------Sales Management System------------------------------";
			cout << "1.Add a record to stock\n2.display all records\n3.delete a record from stock\n4.update record from stock\n5.exit\n\n\n";
			cout << "enter your choice:";
			cin >> ch;
			switch (ch)
			{
			case 1: sl.addstk(); break;
			case 2: sl.dispitm(); break;
			case 3: sl.delstk(); break;
			case 4: sl.updstk(); break;		
			case 5: exit(0); break;
			}
		getch();
		getch();
		} while (1);
	return 0;
	}
