// PhoneBook_Redux.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

class PhoneBook
{
public:
	string ContactName;
	list<string> ContactNumber;
};

class PhoneBookFunctions
{
public:
	string PhoneNo;
	list<PhoneBook> PhoneBooks;
	PhoneBook ObjPhoneBook;
	string GetName();
	string GetNo();
	void AddPhoneBooks();
	void DisplayPhoneBooks();
	void SearchPhoneBook();
	void AddNewPhoneBook(PhoneBook&);
	int DisplaySpecificPhoneBooks(string);
	char MergePhoneBooks(string);
	bool CheckExistingPhoneBook(string);
	void FillPhoneBook();
	int SearchByName(string);
};

bool SortMethod(PhoneBook a, PhoneBook b);
int j{ 0 };

string PhoneBookFunctions::GetName()
{
	string FName, LName, Name;
	cout << "\nEnter First Name: ";
	cin >> FName;
	cin.ignore();
	cout << "\nEnter Last Name: ";
	getline(cin, LName, '\n');
	Name = (FName + " " + LName);
	transform(Name.begin(), Name.end(), Name.begin(), toupper);
	return Name;
}

string PhoneBookFunctions::GetNo()
{
	string PhoneNo;
	cout << "\nEnter Phone No.: ";
	regex r("^(([0]|(\\+1-)|(\\+1))\\ d{10})|\\d{10}$");
	cin >> PhoneNo;
	while (!regex_match(PhoneNo, r))
	{
		cout << "\n\n\t\tPlease Enter a valid no.";
		cout << "\n\n\t\tEnter Phone No.: ";
		cin >> PhoneNo;
	}
	if (PhoneNo.at(0) == '+' && PhoneNo.length() > 10)
	{
		if (PhoneNo.at(3) == '-')
		{

		}
		else
		{
			PhoneNo.replace(0, 3, "+1-");
		}
	}
	if (PhoneNo.at(0) == '0')
	{
		PhoneNo.replace(0, 1, "+1-");
	}
	if (PhoneNo.at(0) != '0' && PhoneNo.at(0) != '+')
	{
		PhoneNo = "+1-" + PhoneNo;
	}
	return PhoneNo;
}

bool SortMethod(PhoneBook a, PhoneBook b)
{
	if (a.ContactName == b.ContactName)
	{
		return a.ContactNumber < b.ContactNumber;
	}
	else
	{
		return a.ContactName < b.ContactName;
	}
}
void PhoneBookFunctions::AddPhoneBooks()
{
	cout << "\nAdd contact";
	char ch{ 'a' };
	int i;
	{
		PhoneBook AddPhoneBook;
		ObjPhoneBook.ContactName = GetName();
		if (CheckExistingPhoneBook(ObjPhoneBook.ContactName))
		{
			cout << "\nPhoneBook Name Already Exists.\n\n\t\tDo you want to add a new PhoneBook number to the existing PhoneBook?";
			cout << "\ny = Yes add more numbers.\n\n\t\tn = No. Add as a new PhoneBook.\n\n\t\tEnter your choice: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				if (DisplaySpecificPhoneBooks(ObjPhoneBook.ContactName) > 1)
				{
					cout << "\nEnter the current contact No of the PhoneBook: ";
					PhoneNo = GetNo();
					for (PhoneBook& ExistingPhoneBook : PhoneBooks)
					{
						if (ExistingPhoneBook.ContactName == ObjPhoneBook.ContactName)
						{
							for (string No : ExistingPhoneBook.ContactNumber)
							{
								if (No == PhoneNo)
								{
									cout << "\n\n\t\tEnter the new contact number:";
									PhoneNo = GetNo();
									ch = MergePhoneBooks(PhoneNo);
									while (ch != 'n' && ch != 'N')
									{
										if (ch == 'y' || ch == 'Y')
										{
											ExistingPhoneBook.ContactNumber.push_back(PhoneNo);
											cout << "\nDo you want to add more number to the contact " << ObjPhoneBook.ContactName << "?";
											cout << "\ny = Yes & n = No\nSelect your choice: ";
											cin >> ch;
											if (ch == 'y' || ch == 'Y')
											{
												PhoneNo = GetNo();
											}
										}
									}
									ch = 'c';
									break;
								}
							}
						}
						if (ch == 'c')
						{
							break;
						}
					}
				}
				else
				{
					for (PhoneBook& ExistingPhoneBook : PhoneBooks)
					{
						if (ExistingPhoneBook.ContactName == ObjPhoneBook.ContactName)
						{
							cout << "\n\n\t\tEnter the new Contact Number:";
							PhoneNo = GetNo();
							ch = MergePhoneBooks(PhoneNo);
							while (ch != 'n' && ch != 'N')
							{
								if (ch == 'y' || ch == 'Y')
								{
									ExistingPhoneBook.ContactNumber.push_back(PhoneNo);
									cout << "\nDo you want to add more number to the contact " << ObjPhoneBook.ContactName << "?";
									cout << "\ny = Yes & n = No\nSelect your choice:  ";
									cin >> ch;
									if (ch == 'y' || ch == 'Y')
									{
										PhoneNo = GetNo();
									}
								}
							}
							ch = 'x';
							break;
						}
					}
				}
			}
			if (ch == 'n' || ch == 'N')
			{
				AddNewPhoneBook(AddPhoneBook);
				j++;
			}
		}
		else
		{
			AddNewPhoneBook(AddPhoneBook);
			j++;
		}
	}
	cout << "\n" << j << " Contact added.\n";
	j = 0;
}

void PhoneBookFunctions::DisplayPhoneBooks()
{
	cout << "\nContact List";
	if (PhoneBooks.empty())
	{
		cout << "\nList of Contacts in Phonebook";
	}
	else
	{
		cout << "\nList of " << PhoneBooks.size() << " PhoneBooks are: \n";
		for (PhoneBook& DisplayPhoneBooks : PhoneBooks)
		{
			cout << "\nContact Name: " << DisplayPhoneBooks.ContactName;
			cout << "\nContact Number: ";
			DisplayPhoneBooks.ContactNumber.sort();
			DisplayPhoneBooks.ContactNumber.unique();
			for (string N : DisplayPhoneBooks.ContactNumber)
			{
				cout << N << " ";
			}
			cout << "\n";
		}
	}
}

void PhoneBookFunctions::SearchPhoneBook()
{
	char ch{ 'a' };
	while (ch != '3')
	{
		cout << "\nSearch PhoneBook";
		cout << "\nChoose an option:\n1. Search PhoneBook By Name\n2. Search PhoneBook By Number\n3. Main Menu\n Enter your choice: ";
		(cin >> ch).get();

		switch (ch)
		{
		case '1':
			system("cls");
			cout << "\nEnter the the name of contact you want to search: ";
			getline(cin, ObjPhoneBook.ContactName);
			transform(ObjPhoneBook.ContactName.begin(), ObjPhoneBook.ContactName.end(), ObjPhoneBook.ContactName.begin(), toupper);
			if (DisplaySpecificPhoneBooks(ObjPhoneBook.ContactName) == 0)
			{
				if (system("cls") || SearchByName(ObjPhoneBook.ContactName) > 0)
				{

					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "\n0 Number of Contacts with " << ObjPhoneBook.ContactName << " availbale in current Phone Book.";
				}
			}
			else if (DisplaySpecificPhoneBooks(ObjPhoneBook.ContactName) != 0)
			{
				system("cls");
				DisplaySpecificPhoneBooks(ObjPhoneBook.ContactName);
			}

			break;

		case '2':
			system("cls");
			cout << "\nEnter the conctact phone number you want to search ";
			PhoneNo = GetNo();
			if (DisplaySpecificPhoneBooks(PhoneNo) == 0)
			{
				system("cls");
				cout << "\nNumber of contacts with " << PhoneNo << " availbale.";
			}
			else if (DisplaySpecificPhoneBooks(ObjPhoneBook.ContactName) != 0)
			{
				system("cls");
				DisplaySpecificPhoneBooks(PhoneNo);
			}
			break;

		case '3':
			break;


		default:
			cout << "\nPlease select a correct option.\n";
			break;
		}
	}
}

void PhoneBookFunctions::AddNewPhoneBook(PhoneBook& NewPhoneBook)
{
	char ch = 'a';
	NewPhoneBook.ContactName = ObjPhoneBook.ContactName;
	PhoneNo = GetNo();
	NewPhoneBook.ContactNumber.push_back(PhoneNo);
	ch = MergePhoneBooks(PhoneNo);
	if (ch == 'n')
	{
		j--;
	}
	else if (ch == 'y')
	{
		while (ch != 'n' && ch != 'N')
		{
			cout << "\nDo you want to add more contact numbers to " << NewPhoneBook.ContactName << "?";
			cout << "\ny = Yes & n = No\nSelect your choice: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				NewPhoneBook.ContactNumber.push_back(GetNo());
			}
			if (ch == 'n' || ch == 'N')
			{
				PhoneBooks.push_back(NewPhoneBook);
			}
		}
	}
}

int PhoneBookFunctions::DisplaySpecificPhoneBooks(string Detail)
{
	int i = 0;
	cout << "\nDisplay Contacts that mached the search creiteria";
	if (Detail.at(0) == '+')
	{
		cout << "\nThe Contact Details are: \n";
		for (PhoneBook DisplayPhoneBook : PhoneBooks)
		{
			for (string DisplayNo : DisplayPhoneBook.ContactNumber)
			{
				if (DisplayNo == Detail)
				{
					cout << "\nContact Name: " << DisplayPhoneBook.ContactName << "\n";
					for (string DisplayNo : DisplayPhoneBook.ContactNumber)
					{
						cout << "\nContact numbers: ";
						cout << DisplayNo << " ";
					}
					i++;

				}
			}
		}
	}
	else
	{
		cout << "\n\n\t\tThe PhoneBook Details are: \n";
		for (PhoneBook DisplayPhoneBook : PhoneBooks)
		{
			if (DisplayPhoneBook.ContactName == Detail)
			{
				cout << "\n\n\t\tPhoneBook Name: " << DisplayPhoneBook.ContactName << "\n";
				for (string DisplayNo : DisplayPhoneBook.ContactNumber)
				{
					cout << "\n\t\tPhoneBook No(s): ";
					cout << DisplayNo << " ";
				}
				i++;
				cout << "\n\n";
			}
		}
	}
	return i;
}

char PhoneBookFunctions::MergePhoneBooks(string PhoneNo)
{
	char ch;
	for (PhoneBook& MergePhoneBook : PhoneBooks)
	{
		for (string& MergeNo : MergePhoneBook.ContactNumber)
		{
			if (MergeNo == PhoneNo)
			{
				DisplaySpecificPhoneBooks(PhoneNo);
				cout << "\Contact with same Information already exist.";
				cout << "\nDo you want to join the contact with existing contact?";
				cout << "\ny = Yes & n = No\n\n\t\tEnter your choice: ";
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					return 'n';
				}
				else if (ch == 'n' || ch == 'N')
				{
					return 'y';
				}
			}
		}
	}
	return ch = 'y';
}

bool PhoneBookFunctions::CheckExistingPhoneBook(string Name)
{
	for (PhoneBook CheckPhoneBook : PhoneBooks)
	{
		if (CheckPhoneBook.ContactName == Name)
		{
			return true;
		}
	}
	return false;
}

int PhoneBookFunctions::SearchByName(string Detail)
{
	cout << "\nSearch Contact";
	int Counter = 0;
	for (PhoneBook SearchPhoneBook : PhoneBooks)
	{
		if (!SearchPhoneBook.ContactName.find(Detail))
		{
			cout << "\n\n\t\Contact Name: " << SearchPhoneBook.ContactName << "\n";
			for (string DisplayNo : SearchPhoneBook.ContactNumber)
			{
				cout << "\n\t\Contact No(s): ";
				cout << DisplayNo << " ";
			}
			cout << "\n\n";
			Counter++;
		}
	}
	return Counter;
}

string GetRandomString()
{
	string s1, s2, s;
	for (int i = 1; i <= 10; i++)
	{
		while (s1.length() != 5)
		{
			char c = ((rand() % 26) + 65);
			s1 += c;
		}
		while (s2.length() != 2)
		{
			char c = ((rand() % 26) + 65);
			s2 += c;
		}
		s = s1 + " " + s2;
	}
	return s;
}

void PhoneBookFunctions::FillPhoneBook()
{
	for (int i = 1; i <= 5; i++)
	{
		PhoneBook Temp;
		Temp.ContactName = GetRandomString();
		transform(Temp.ContactName.begin(), Temp.ContactName.end(), Temp.ContactName.begin(), toupper);
		do
		{
			PhoneNo += ((rand() % 4) + 49);
			if (PhoneNo.length() == 10)
			{
				Temp.ContactNumber.push_back(PhoneNo);
				PhoneNo.clear();
			}
			if (Temp.ContactNumber.size() > 2)
			{
				break;
			}
		} while (Temp.ContactNumber.size() != ((rand() % 10) + 52));
		PhoneBooks.push_back(Temp);
	}
}

int main()
{
	PhoneBookFunctions ObjPhoneBookFunctions;
	char choice{ '0' };
	while (choice != '6')
	{

		cout << "\n\n\t\Menu";
		cout << "\n Choose an option:\n 1. Add contact\n 2. Display all saved Contacts\n 3. Search for a contact\n 4. Exit\n Select an Option: ";
		(cin >> choice).get();
		switch (choice)
		{
		case '1':
			system("cls");
			ObjPhoneBookFunctions.AddPhoneBooks();
			cout << "\n";
			system("pause");
			system("cls");
			break;

		case '2':
			system("cls");
			ObjPhoneBookFunctions.PhoneBooks.sort(SortMethod);
			ObjPhoneBookFunctions.DisplayPhoneBooks();
			cout << "\n";
			system("pause");
			system("cls");
			break;

		case '3':
			system("cls");
			ObjPhoneBookFunctions.SearchPhoneBook();
			system("cls");
			break;

		case '4':
			break;

		default:
			system("cls");
			cout << "\n\tPlease select a correct option.\n";
			break;
		}
	}
	return 0;
}

