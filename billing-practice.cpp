#include<iostream>
#include<fstream>
using namespace std;

class shopping
{
	private:
		// p is product
		int pcode;
		float price;
		float disc;
		string pname;
	
	public: // functions
		void menu();
		void administrator();
		void buyer();
		void add();
		void edit();
		void del();
		void list();
		void receipt();
};

void shopping::menu()
{
	m:
	int choice;
	string email;
	string password;
	
	cout << "\t\t\t _________________________\n";
	cout << "\t\t\t                          \n";
	cout << "\t\t\t   SUPERMARKET MAIN MENU  \n";
	cout << "\t\t\t _________________________\n";
	cout << "\t\t\t                          \n";
	cout << "\t\t\t | 1) Administrator      |\n";
	cout << "\t\t\t | 2) Buyer              |\n";
	cout << "\t\t\t | 3) Exit               |\n";
	cout << "\t\t\t                          \n";
	cout << "\t\t\t Please select: ";
	cin >> choice;
	
	switch(choice)
	{
		case 1:
			cout << "\t\t\t Please LOGIN \n";
			cout << "\t\t\t Enter EMAIL : \n";
			cin >> email;
			cout << "\t\t\t Enter PASSWORD : \n";
			cin >> password;
			
			if(email=="admin@mail.com" && password=="admin123")
			{
				administrator();
			}
			else
			{
				cout << "Invalid email / password";
			}
			break;
			
		case 2:
			buyer();
			break;
			
		case 3:
			exit(0);
			
		default:
			cout << "Please select from the option: ";
	}
	goto m; // go back to main menu
}

void shopping::administrator()
{
	m:
	int choice;
	cout << "\n\n\t\t\t ADMINISTRATOR MENU \n";
	cout << "\t\t\t 1) Add product \n";
	cout << "\t\t\t 2) Edit product \n";
	cout << "\t\t\t 3) Delete product \n";
	cout << "\t\t\t 4) Back to main menu \n";
	
	cout << "\n\t Please enter your choice: ";
	cin >> choice;
	
	switch(choice)
	{
		case 1:
			add();
			break;
			
		case 2:
			edit();
			break;
			
		case 3:
			del();
			break;
			
		case 4:
			menu();
			break;
			
		default:
			cout << "Invalid choice!";
	}
	goto m;
}

void shopping::buyer()
{
	m:
	int choice;
	cout << "\n\n\t\t\t    BUYER    \n";
	cout << "\t\t\t ___________ \n";
	cout << "\n\t\t\t 1) Buy product \n";
	cout << "\n\t\t\t 2) Go back \n";
	cout << "\n\t\t\t  Enter your choice: ";
	cin >> choice;
	
	switch(choice)
	{
		case 1:
			receipt();
			break;
			
		case 2:
			menu();
			break;
			
		default:
			cout << "Invalid choice!";
	}
	goto m;
}

void shopping::add()
{
	m:
	fstream data;
	int c;
	int token = 0;
	float p;
	float d;
	string n;
	
	cout << "\n\n\t\t\t ADD NEW PRODUCT ";
	cout << "\n\n\t Product code: ";
	cin >> pcode;
	cout << "\n\n\t Product name: ";
	cin >> pname;
	cout << "\n\n\t Product price: ";
	cin >> price;
	cout << "\n\n\t Discount: ";
	cin >> disc;
	
	// the data above will be saved into a file. file handling operation to open the file. ios in = open file in reading mode.
	data.open("database.txt", ios::in);
	
	if(!data)
	{
		data.open("database.txt", ios::app|ios::out); // ios out = writing mode.
		data << " " << pcode << " " << pname << " " << price << " " << disc << "\n";
		data.close();
	}
	else
	{
		data >> c >> n >> p >> d; // initializing the index
		
		while(!data.eof()) // end of file. to make sure every content of the file by iterating it.
		{
			if(c == pcode) // each content of the file is checked if the code matches the pcode if there's a duplicacy.
			{
				token++;
			}
			data >> c >> n >> p >> d;
		}
		data.close();

		if(token == 1) // if there's a duplicacy of product, it will take the admin to the main page
		{
			goto m;
		}
		else // if the code is not a duplicate, then we will be able to add a new product
		{
			data.open("database.txt", ios::app|ios::out);
			data << " " << pcode << " " << pname << " " << price << " " << disc << "\n";
			data.close();
		}
	}
	cout << "\n\n\t Insert record successful.";
}

void shopping::edit()
{
	fstream data, data1; // create 2 objects
	// pkey = product code, c = new code, p = price, d = discount, n = name
	int pkey;
	int token = 0;
	int c;
	float p;
	float d;
	string n;
	
	cout << "\n\t\t\t EDIT RECORD ";
	cout << "\n\t\t\t Product code: ";
	cin >> pkey;
	
	data.open("database.txt", ios::in); // to check if the file exist or not
	if(!data)
	{
		cout << "\n\n\t File does not exist";
	}
	else
	{
		// it will open a new data file
		data1.open("database1.txt", ios::app|ios::out);
		data >> pcode >> pname >> price >> disc;
		
		while(!data.eof())
		{
			if(pkey == pcode) // if the product key does match the product code
			{
				cout << "\n\t\t New Product Code: ";
				cin >> c;
				cout << "\n\t\t New Product Name: ";
				cin >> n;
				cout << "\n\t\t Price: ";
				cin >> p;
				cout << "\n\t\t Discount: ";
				cin >> d;
				data1 << " " << c << " " << n << " " << p << " " << d << "\n";
				cout << "\n\n\t\t Record edited successfully.";
				token++;
			}
			else
			{
				data1 << " " << pcode << " " << pname << " " << price << " " << disc << "\n";
			}
			data >> pcode >> pname >> price >> disc;
		}
		data.close();
		data1.close();
		
		// removing the old file with the new one
		
		remove("database.txt");
		rename("database1.txt", "database.txt");
		
		if(token==0)
		{
			cout << "\n\n Record not found.";
		}
	}
	
}

void shopping::del()
{
	fstream data, data1;
	int pkey;
	int token = 0;
	cout << "\n\n\t DELETE PRODUCT ";
	cout << "\n\n\t Product code: ";
	cin >> pkey;
	data.open("database.txt", ios::in);
	
	if(!data)
	{
		cout << "\n\t File does not exist.";
	}
	else
	{
		data1.open("database1.txt", ios::app|ios::out);
		data >> pcode >> pname >> price >> disc;
		
		while(!data.eof())
		{
			if(pcode == pkey)
			{
				cout << "\n\n\t Product deleted successfully.";
				token++;
			}
			else
			{
				data1 << " " << pcode << " " << pname << " " << price << " " << disc << "\n";
			}
			data1 >> pcode >> pname >> price >> disc;
		}
		data.close();
		data1.close();
		remove("database.txt");
		rename("database1.txt", "database.txt");
		
		if(token == 0)
		{
			cout << "\n\n\t Record not found.";
		}
	}
	
}

void shopping::list()
{
	fstream data;
	data.open("database.txt", ios::in);
	cout << "\n\n\t _____________________________________________________________________\n";
	cout << "\t\tProduct No. \t\t Name \t\t Price \n";
	cout << "\n\n\t _____________________________________________________________________\n";
	
	data >> pcode >> pname >> price >> disc;
	
	while(!data.eof())
	{
		cout << "\t\t" << pcode << "\t\t " << pname << "\t\t " << price << "\n";
		data >> pcode >> pname >> price >> disc;
	}
	data.close();
}

void shopping::receipt()
{
	fstream data;
	int arrc[100]; // code array
	int arrq[100]; // quantity array
	char choice;
	int c = 0; //
	float amount = 0;
	float disc = 0;
	float total = 0;
	
	cout << "\n\n\t\t\t\t RECEIPT";
	data.open("database.txt", ios::in);
	
	if(!data)
	{
		cout << "\n\n EMPTY DATABASE";
	}
	else
	{
		data.close();
		
		list();
		cout << "\n\t__________________________________\n";
		cout << "\n\t     Please place your order      \n";
		cout << "\n\t__________________________________\n";
		
		do
		{
			m:
			cout << "\n\n Enter product code : ";
			cin >> arrc[c];
			
			cout << "\n\n Enter product quantity : ";
			cin >> arrq[c];
			
			cout << "\n\t\t" << arrc[c] ;
			cout << "\n\t\t" << arrq[c] ;
			
			for(int i = 0; i < c; i++)
			{
				if(arrc[c]==arrc[i])
				{
					cout << "\n\n Duplicate product code. Please try again.";
					goto m;
				}
			}
			c++;
			cout << "\n\n Do you want to buy another product? Press y for YES. Press n for NO : ";
			cin >> choice;
		}
		while(choice == 'y' ); // if you press either keys it will take you to another menu order OR continue to receipt
		
		cout << "\n\n\t\t______________________ RECEIPT ______________________\n";
		cout << "\n Product No.\t Product Name\t Quantity\t Price\t Amount\t Discounted Amount \n";
		
		cout << "c==>" << c;
		for(int i = 0; i < c; i++)
		{
			data.open("database.txt", ios::in);
			data >> pcode >> pname >> price >> disc;
			
			while(!data.eof())
			{
				if(pcode == arrc[i])
				{
					amount = price * arrq[i];
					disc = amount - (amount * disc / 100);
					total = total + disc;
					cout << "\n\t" << pcode << "\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t" << disc <<"\n";
				}
				data >> pcode >> pname >> price >> disc;
			}
		}
		data.close();
	}
	cout << "\n\n\t\t ____________________________________________________\n";
	cout << "\n\t Total amount: " << total;
}

int main()
{
	shopping s;
	s.menu();
}
