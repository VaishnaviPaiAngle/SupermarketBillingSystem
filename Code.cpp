#include<iostream>
#include<conio.h>
#include<string.h>
using namespace std;
class item
{
protected:
	string pitems[30], npitems[30];
	string pid[30], npid[30];
	double pprice[30], npprice[30];
	int pn, npn;
public:
	void get_i()
	{
		int i;
		cout << "Enter no of perishable items\n";
		cin >> pn;
		cout << "Enter the items,id and price:\n";
		for (i = 0; i < pn; i++)
		{
			cin >> pitems[i] >> pid[i] >> pprice[i];
		}
		cout << "\nEnter no of non perishable items\n";
		cin >> npn;
		cout << "Enter the items,id and price:\n";
		for (i = 0; i < npn; i++)
		{
			cin >> npitems[i] >> npid[i] >> npprice[i];
		}
		sort_i();
	}
	void sort_i()
	{
		int i, j;
		double a, b;
		string pit, npit, pidd, npidd;
		for (i = 1; i < pn; i++)
		{
			j = i - 1;
			while (pprice[i] < pprice[j] && j >= 0)
			{
				a = pprice[i];
				pprice[i] = pprice[j];
				pprice[j] = a;

				pit = pitems[i];
				pitems[i] = pitems[j];
				pitems[j] = pit;

				pidd = pid[i];
				pid[i] = pid[j];
				pid[j] = pidd;

				i--;
				j--;
			}
		}
		for (i = 1; i < npn; i++)
		{
			j = i - 1;
			while (npprice[i] < npprice[j] && j >= 0)
			{
				a = npprice[i];
				npprice[i] = npprice[j];
				npprice[j] = a;

				npit = npitems[i];
				npitems[i] = npitems[j];
				npitems[j] = npit;

				npidd = npid[i];
				npid[i] = npid[j];
				npid[j] = npidd;

				i--;
				j--;
			}
		}

	}
	void delete_i()
	{
		int n, i, j;
		char x[30];
		cout << "Enter 1 to delete a perishable item\n";
		cout << "Enter 2 to delete a non-perishabe item\n";
		cin >> n;
		cout << "Enter the item to be deleted: ";
		cin >> x;
		switch (n)
		{
		case 1:
			for (i = 0; i < pn; i++)
				if (pitems[i] == x)
					break;

			if (i < pn)
			{
				pn = pn - 1;
				for (j = i; j < pn; j++)
				{
					pitems[j] = pitems[j + 1];
					pid[j] = pid[j + 1];
					pprice[j] = pprice[j + 1];
				}
			}
			cout << "\nItem " << x << " successfully deleted.\n";
			break;

		case 2:
			for (i = 0; i < npn; i++)
				if (npitems[i] == x)
					break;

			if (i < npn)
			{
				npn = npn - 1;
				for (j = i; j < npn; j++)
				{
					npitems[j] = npitems[j + 1];
					npid[j] = npid[j + 1];
					npprice[j] = npprice[j + 1];
				}
			}
			cout << "\nItem " << x << " successfully deleted.\n";
			break;
		}
	}
	void show_i()
	{
		int i;
		cout.width(25);
		cout << "TYPE OF ITEM";
		cout.width(15);
		cout << "ITEMS";
		cout.width(15);
		cout << "ITEM_ID";
		cout.width(15);
		cout << "PRICE" << endl;

		for (i = 0; i < pn; i++)
		{
			cout.width(25);
			cout << "Perishable item";
			cout.width(15);
			cout << pitems[i];
			cout.width(15);
			cout << pid[i];
			cout.width(15);
			cout << pprice[i] << endl;
		}
		for (i = 0; i < npn; i++)
		{
			cout.width(25);
			cout << "Non-Perishable item";
			cout.width(15);
			cout << npitems[i];
			cout.width(15);
			cout << npid[i];
			cout.width(15);
			cout << npprice[i] << endl;
		}
	}
};
class perishable :virtual public item
{
protected:
	double total_pi = 0, dis_pi = 0;
public:
	void pi_total()
	{
		int i;
		for (i = 0; i < pn; i++)
			total_pi += pprice[i];
	}
	void pi_discount()
	{
		pi_total();
		dis_pi = 0.05 * total_pi;
	}
};
class non_perishable :virtual public item
{
protected:
	double total_npi = 0;
public:
	void npi_total()
	{
		int i;
		for (i = 0; i < npn; i++)
			total_npi += npprice[i];
	}
};
class customer
{
protected:
	char name[30];
	int contact_no;
	int membership_no, m;
public:
	void get_c()
	{
		cout << "\nEnter name: ";
		cin >> name;
		cout << "Enter contact no: ";
		cin >> contact_no;
		cout << endl;
	}
	void membership()
	{
		get_c();
		int choice;
		cout << "\n\nEnter 1 if customer is a member\n";
		cout << "Enter 2 if customer is not a member\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter membership no: ";
			cin >> membership_no;
			m = 1;
			break;
		case 2:
			membership_no = 0;
			m = 0;
			break;
		default:
			cout << "Enter again\n";
		}
	}
	void show_c()
	{
		membership();
		cout << "\n\n\n-------------------------------------------BILL------------------------------------------\n\n";
		cout << "\nCustomer details:\n";
		cout << "Name: " << name << endl;
		cout << "Contact No.: " << contact_no << endl;
		cout << "Membership No.: " << membership_no << endl << endl;

	}

};
class bill : public customer, public perishable, public non_perishable
{
protected:
	double m_discount, total_bill;
public:
	void i_get()
	{
		item::get_i();
	}
	void i_delete()
	{
		item::delete_i();
	}
	void total()
	{
		double dis, tdis;
		pi_discount();
		npi_total();

		dis = total_pi - dis_pi;
		total_bill = dis + total_npi;

		customer::show_c();
		item::show_i();

		if (m == 1)
		{
			cout << "\nExtra 5% discount is given to memeber customer\n";
			tdis = total_bill * 0.05;
			m_discount = total_bill - tdis;
		}
		else
		{
			m_discount = total_bill;
			tdis = 0;
		}
		cout << "\nTotal before discount= " << total_pi + total_npi << endl;
		cout << "\nDiscounted amount= " << dis_pi + tdis << endl;
		cout << "\n\n\nFinal bill:" << m_discount << endl << endl;
	}
};
int main()
{
	bill b;

	int choice;
	cout << "\n\n\t\t\t\t@@@@@-----WELCOME TO SV SUPERMARKET BILLING-----@@@@@\n\n";
	cout << "\ MENU\n";
	cout << " 1: To enter data\n";
	cout << " 2: To delete data\n";
	cout << " 3: To display bill\n";
	cout << " 4: To exit\n";
	do
	{
		cout << "\nEnter your choice\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			b.i_get();
			cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			break;

		case 2:
			cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			b.i_delete();
			cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			break;

		case 3:
			cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			b.total();
			cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			break;

		default:
			cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			cout << "\nEnter again\n";
			cout << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
			break;
		}
		cout << endl;
	} while (choice != 4);

	_getch();
	return 0;
}

