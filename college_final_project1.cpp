/*			||  OOPS MICRO-PROJECT ||
		Project Title -	 Shopping Management with Billing System 
		
     Project By :- 	
				
	1. Ravindra Kadam     9022404626	rbkadam2320@gmail.com
	
	 Guided By :-			
				Mrs.Lalita Korde Mam 
				[COMPUTER ENGINEERING DEPARTMENT]
			 Lecturer at Government Polytechnic Pune 
*/
/************************************************************************************
 including header files
**************************************************************************************/
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
using namespace std;
/************************************************************************************
 goto() function is declared for loading animation
**************************************************************************************/
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/************************************************************************************
 here class customer is declared in which add to cart operations are included
**************************************************************************************/

class customer //class concept
{
private: //private access specifier
    int order_id[40], order_quanti[40], x;
    static int c; //static data members
    float amt, damt;
    static float total, cgst, sgst, save, totalsave; //static data members
    char ch;
    char proName[20];
    int proId, custId;
    float price;
    int quanti, dis;
    char name[100];
    string city, country, state, pincode, phone_no, email;

public: //public access specifier
    /************************************************************************************
 declaration of member fucntion of class customer
**************************************************************************************/
    void custFinal(); //member function declaration
    void addTocart();
    void viewBill();
    void subBill();
    void custInfo();
    void paymentMode();
    void displayCustInfo();
    void finalBill();
};
//intialize static data members outside the class
int customer::c = 0;
float customer::total = 0;
float customer::cgst = 0;
float customer::sgst = 0;
float customer::save = 0;
float customer::totalsave = 0;
/************************************************************************************
 here class head is declared in which login register operations are included
**************************************************************************************/
class head
{
    char cho; //it is by defalult private varibale

public:                    //public access specifiers
    friend class customer; //friend class concept
    string reguser, regpass, email;
    //password function declared for hiding the data which user entering and prints in the form of '*'
    void password(char *ar, int max)
    {
        int x = 0;
        while (1)
        {
            cho = getch();
            if (cho == 13)
            {
                ar[x] = '\0';
                break;
            }
            if (cho == 8 && x != 0)
            {
                cout << "\b \b";
                if (x < max && x > 0)
                    x--;
            }
            else if (x < max && cho != 8)
            {
                cout << "*";
                ar[x] = cho;
                x++;
            }
        }
    }
    void final();
    void contactUs();
    void userLogin(customer); //object as member function argument
    void userRegister();
    void forgotPassword();
    void captacha();
    void userInfo();
};
/************************************************************************************
 member function defination is declaring at outside the class
**************************************************************************************/
void head::userRegister()
{
    //this function is used for user registration...and its data is stored in userLoginDatabase.txt file
    char ch, regpass[8], repass[8], retype[8];
    int i;
    string email;
label:
    system("cls"); //it is used for clear screen
    cout << "\n\n\t\t\tRegistration page";
    cout << "\n\n\t\t\t| Enter The Email Id :";
    cin >> email;
    cout << "\n\t\t\t| Enter The Username :";
    cin >> reguser;
    cout << "\n\t\t\t| Enter The Password :";
    cin >> regpass;
    cout << "\n\t\t\t| Re-Type Password : ";
    cin >> retype;
    if (strcmp(regpass, retype) == 0) //predefined string method
    {
        goto l1; //checking passowrd and goto label l1
    }
    else
    {
        cout << "\n\n\t\t\t\tEnter valid password";
        cin.get();
        cin.get();
        goto label; //goto statement
    }
l1:
    ofstream regUser("UserLoginDatabase.txt", ios::app); //read data from user and store in file
    regUser << email << "  " << reguser << "   " << regpass << "\n";
    regUser.close(); //file close
    cout << "\n\n\t\t\t____[Registration Sucessfully]____\n";
    cout << "\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get(); //
    cin.get();
    system("cls");
}
/************************************************************************************
 in userInfo() function user regsitered data is retruve from database and display it
**************************************************************************************/
void head::userInfo()
{
    system("cls");
    ifstream UserLoginDatabase("UserLoginDatabase.txt");
    if (!UserLoginDatabase) //file does not exist
    {
        cout << "\n\n\t\t\t____[File Openning Error!]____";
    }
    else
    {
        cout << "\n\n\t\t\t____Users List Who Has Done With Registration____";
        cout << "\n\t____________________________________________________________________________________";
        cout << "\n\t\tEmail-Id  \t\tUserName\t\t Password ";
        cout << "\n\t____________________________________________________________________________________";
        UserLoginDatabase >> email >> reguser >> regpass;
        while (!UserLoginDatabase.eof()) //retrive data form file till last record
        {
            cout << "\n\t\t"
                 << email << "\t\t" << reguser << "\t\t" << regpass;
            cout << "\n\t____________________________________________________________________________________";
            UserLoginDatabase >> email >> reguser >> regpass;
        }
        UserLoginDatabase.close();
    }
    cout << "\n\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
    cin.get();
}
/************************************************************************************
 userlogin() function is declared for user login..if registered username ans password is same
 with login username and password then user logged in..shopping 
**************************************************************************************/
void head::userLogin(customer cust) //object as passing an argument
{
    int count, i, n, n1, userans;
    char ch, ans, regpass[20];
    string reguser, u, p, email;
    system("cls");
    cout << "\n\n\t\t\tUser Login Page" << endl;
    cout << "\n\n\t\t\t| Enter Registered Username :";
    cin >> u;
    cout << "\n\t\t\t| Enter Registered Password :";
    cin >> p;
    ifstream input("UserLoginDatabase.txt", ios::in);
    while (!input.eof())
    {
        input >> email >> reguser >> regpass;
        if (reguser == u && regpass == p) //checking username and pasword form database
        {
            count = 1;
            system("cls");
        }
    }
    input.close();
    if (count == 1)
    {
        captacha();       //here self class member function is calling
        cust.custFinal(); //calling customer class member function();
    }
    else
    {
        system("cls");
        cout << "\n\n\t\t\t____[Invalid Username or password]____";
        cout << "\n\n\t\t\t<Press Enter Key To Continue>";
        cin.get();
        cin.get();
    }
}
/************************************************************************************
 captacha() function is generation captacha for login
**************************************************************************************/
void head::captacha()
{
    int count, i, n, n1, userans;
    char ch, ans;
    gotoxy(30, 10);
    cout << "\n\n\t\t\tGenerating Captacha Please Wait...";
    for (int i = 1; i <= 5; i++)
    {
        Sleep(500);
        cout << ".";
    }
    cout << "\n\n\t\t\tAre You a Robot?[Y/N] : ";
    cin >> ch;
    if (ch == 'n' || ch == 'N')
    {
        cout << "\n\n\t\t\tPlease Enter Captcha .";
        for (i = 0; i < 1; i++)
        {
            n = rand() % 30; //random number genrator
            n1 = rand() % 20;
            ans = n + n1;
            cout << "\n\n\t\t\t" << n << " "
                 << "+" << n1 << " "
                 << "= :";
        }
        cin >> userans;
        cout << "\n\n\t------------------------------------------------------------------------------------";
        if (ans == userans)
        {
            system("cls");
            cout << "\n\n\t\tHello Mr/Mrs " << reguser << "\n\n\t\tYou are logged suucessfuly.\n\n\n\t\tWe're glad that you're here.\n\n\t\tThanks for logging In.\n\n\t\t<SHOPPING WITH US & ENJOY FULL>";
            cout << "\n\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
        }
        else
        {
            system("cls");
            cout << "\n\n\t\t\t____[Invalid Captacha]____";
            captacha();//recusrsion conecpt...function calling itself
        }
    }
}
/************************************************************************************
 forgot password function return if any user forgot his password or username then this function help him to login
**************************************************************************************/
void head::forgotPassword()
{
    int ch;
    system("cls");
    cout << "\n\n\t\t\tForgotten ? We're here for help\n";
    cout << "\n\t\t\t1.Search your id by username" << endl;
    cout << "\n\t\t\t2.Search your id by password" << endl;
    cout << "\n\t\t\t3.Main menu" << endl;
    cout << "\n\t\t\tEnter your choice [1-3]:";
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        int count = 0;
        string searchuser, su, sp, email;
        cout << "\n\n\t\t\tEnter your remembered username :";
        cin >> searchuser;
        ifstream input("UserLoginDatabase.txt", ios::in);

        while (!input.eof())
        {
            input >> email >> su >> sp;
            if (searchuser == su)
            {
                count = 1;
            }
        }
        input.close();
        if (count == 1)
        {
            system("cls");
            cout << "\n\n\t\t\tHurray, account found\n";
            cout << "\n\n\t\t\tYour Password is " << sp;
            cout << "\n\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
            system("cls");
        }
        else
        {
            system("cls");
            cout << "\n\n\t\t\tSorry, Your userID is not found in our database\n";
            cout << "\n\n\t\t\tPlease kindly contact your system administrator for more details \n";
            cout << "\n\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
        }
        break;
    }
    case 2:
    {
        int count = 0;
        string searchpass, su2, sp2, email;
        cout << "\n\n\t\t\tEnter the remembered password :";
        cin >> searchpass;
        ifstream input("UserLoginDatabase.txt", ios::in);
        while (!input.eof())
        {
            input >> email >> su2 >> sp2;
            if (searchpass == sp2)
            {
                count = 1;
            }
        }
        input.close();
        if (count == 1)
        {
            system("cls");
            cout << "\n\n\t\t\tYour password is found in the database \n";
            cout << "\n\t\t\tYour Username is : " << su2;
            cout << "\n\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
        }
        else
        {
            system("cls");
            cout << "\n\n\t\t\tSorry, We cannot found your password in our database \n";
            cout << "\n\t\t\tkindly contact your administrator for more information\n";
            cout << "\n\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
        }
        break;
    }
    case 3:
    {
        break;
    }
    default:
        cout << "\n\n\t\t\t[Sorry, You entered wrong choice. Kindly try again]" << endl;
        forgotPassword(); //Recursive Function Concept..itself calling
    }
}
/************************************************************************************
 contactUs function is declared in which simple some information is printed
**************************************************************************************/
void head::contactUs()
{
    system("cls");
    cout << "\n\n\n\t\t\t* Welcome To EverGreen Shopping Mall *";
    cout << "\n\n\t\t\t| Contact Us - Ravindra Kadam";
    cout << "\n\n\t\t\t| Email Id - ravindrakadam***@gmail.com";
    cout << "\n\n\t\t\t| Mo.No - +91902240****";
    cout << "\n\n\t\t\t--------------------------------------------------------------------";
    cout << "\n\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
    cin.get();
    system("cls");
}
/************************************************************************************
 class admin product is decalred for admin operations
**************************************************************************************/
class AdminProduct
{
protected: //protected access specifiers
    string proName;
    int proId;
    float price;
    int quanti, dis;
    int i, n;

public:                     //public access specifiers
    virtual void getData(); //here virtual member function is declared
    virtual void putData(); //here virtual member function is declared
    void searchProduct();
    void updateProduct();
    void cancelProduct();
    //function overloading menas same function name with different parametrs
    void getValue(int id) //function overoading
    {
        proId=id;
    }
    void getValue(float pri)//function overloading
    {
    	price=pri;
	}
};
AdminProduct adpro1; //creating adminProduct class object here
/************************************************************************************
getData method just scan values form admin and store it into admmin database
**************************************************************************************/
void AdminProduct::getData()
{
    cout << "\n\n\t\t\tEnter Product ID :";
    cin >> proId;
    cout << "\n\t\t\tEnter Product Name : ";
    cin >> proName;
    cout << "\n\t\t\tEnter Product Price :";
    cin >> price;
    cout << "\n\t\t\tEnter Product Quantity : ";
    cin >> quanti;
    cout << "\n\t\t\tEnter Discount On Product : ";
    cin >> dis;
    ofstream productData("productData.txt", ios::app);

    productData << proId << " " << proName << " " << price << " " << quanti << " " << dis << "\n";

    productData.close();
}
/************************************************************************************
putdata() method retrive data from database and display it
**************************************************************************************/
void AdminProduct::putData()
{
    ifstream productData("productData.txt"); //retive data from productdata file
    if (!productData)                        //if file does not exist then if block will execute
    {
        cout << "\n\n\t\t\t____[File Openning Error!]____";
    }
    else
    {
        cout << "\n\t\t\tProID  \t\tProName\t\t Price \t\tQuanti\t\tDiscount";
        cout << "\n\t____________________________________________________________________________________________";
        productData >> proId >> proName >> price >> quanti >> dis;
        while (!productData.eof())
        {
            cout << "\n\t\t\t"
                 << proId << "\t\t" << proName << "\t\t" << price << "\t\t" << quanti << "\t\t" << dis;
            cout << "\n\t______________________________________________________________________________________________";
            productData >> proId >> proName >> price >> quanti >> dis;
        }
        productData.close();
    }
}
/************************************************************************************
 updateProduct() method upating the record and updated record store into database
**************************************************************************************/
void AdminProduct::updateProduct()
{
    int count = 0, quan;
    char pro_n[20];
    float pri;
    int proIdd, disc;
    ofstream admindata1("book1.txt", ios::app);
    ifstream productData("productData.txt");
    if (!productData)
    {
        cout << "\nFile Openning Error!";
    }
    else
    {
        cout << "\n\n\t\t\tEnter Product ID To Update Specific Item : ";
        cin >> proId;
        productData >> proIdd >> proName >> price >> quanti >> dis;
        while (!productData.eof() && count == 0)
        {
            if (proId == proIdd)
            {
                cout << "\n\n\t\t\tUpdate Record";
                cout << "\n\n\t\t\tEnter New Product Name    : ";
                cin >> pro_n;
                cout << "\n\t\t\tEnter New Product Price     : ";
                cin >> pri;
                cout << "\n\t\t\tEnter New Product Quantity  :";
                cin >> quan;
                cout << "\n\t\t\tEnter New Discount On Product: ";
                cin >> disc;
                cout << "\n\n\t\t\tRecord Updated Successfully.";
                admindata1 << " " << proId << " " << pro_n << " " << pri << " " << quan << " " << disc << "\n";
                count++;
            }
            else
            {
                admindata1 << " " << proIdd << " " << proName << " " << price << " " << quanti << " " << dis << "\n";
                productData >> proIdd >> proName >> price >> quanti >> dis;
            }
        }
        if (count == 0)
        {
            cout << "\n\n\t\t\tProduct Id is not found";
        }
    }
    productData.close();
    admindata1.close();
    remove("productData.txt");
    rename("book1.txt", "productData.txt"); //renameing file book1 to productData
}
/************************************************************************************
 cancelProduct() method is used to delete the record which admin inputs product id from database
**************************************************************************************/
void AdminProduct::cancelProduct()
{
    int count = 0;
    int proIdd;
    ofstream admindata1("book2.txt", ios::app);
    ifstream productData("productData.txt");
    if (!productData)
    {
        cout << "\n\n\t\t\tFile Openning Error!";
    }
    else
    {
        cout << "\n\n\t\t\tEnter Product ID To Delete Specific Item : ";
        cin >> proId;
        productData >> proIdd >> proName >> price >> quanti >> dis;
        while (!productData.eof() && count == 0)
        {
            if (proId == proIdd)
            {
                cout << "\n\n\t\t\tDelete record";
                cout << "\n\n\t\t\tOne Record Successfully deleted.";
                count++;
            }
            else
            {
                admindata1 << " " << proIdd << " " << proName << " " << price << " " << quanti << " " << dis << "\n";
                productData >> proIdd >> proName >> price >> quanti >> dis;
            }
        }
        if (count == 0)
        {
            cout << "\n\n\t\t\tProduct Id is not found";
        }
    }
    productData.close();
    admindata1.close();
    remove("productData.txt");
    rename("book2.txt", "productData.txt");
}
/************************************************************************************
 searchProduct() methos searches the product in database and retive specific data
**************************************************************************************/
void AdminProduct::searchProduct()
{
    int count;
    int proIdd;
    ifstream productData("productData.txt");
    if (!productData)
    {
        cout << "\n\n\t\t\tFile Openning Error!";
    }
    else
    {
        cout << "\n\n\t\t\tEnter Product ID To Search Specific Item : ";
        cin >> proIdd;
        productData >> proId >> proName >> price >> quanti >> dis;
        while (!productData.eof())
        {
            if (proId == proIdd)
            {
                cout << "\n\n\t\t\tSearch Successfully.....";
                cout << "\n\n\t\t\tProduct Description";
                cout << "\n\t\t---------------------------------------------------------------------------------";
                cout << "\n\n\t\t\t| Product Id        : " << proId;
                cout << "\n\n\t\t\t| Product Name      : " << proName;
                cout << "\n\n\t\t\t| Product Price     : " << price;
                cout << "\n\n\t\t\t| Product Quanatity : " << quanti;
                cout << "\n\n\t\t\t| Product Discount  : " << dis;
                count++;
                break;
            }
            productData >> proId >> proName >> price >> quanti >> dis;
        }
        if (count == 0)
        {
            cout << "\n\n\t\t\tProduct Id is not found";
        }
        productData.close();
    }
}
/************************************************************************************
book class is declared and it is inherited by adminProduct class
**************************************************************************************/
class book : public AdminProduct //here public is called visibility mode
{

private:
    string authorname;
    string publications;

public:
    void getData()
    {
        AdminProduct::getData(); //calling base class method in derived class
        cout << "\n\t\t\tEnter Book Author       : ";
        cin >> authorname;
        cout << "\n\t\t\tEnter Book Publications : ";
        cin >> publications;
        cout << "\n\t\t\t------------------------------------------";
        ofstream productData("productData.txt", ios::app);
        productData.close();
    }
    void putData()
    {
        AdminProduct::putData(); //calling base class method by usnig classname and scoper resolution operator
    }
};
/************************************************************************************
electronics class is declared and it is inherited by adminProduct class
**************************************************************************************/
class electronics : public AdminProduct
{
private:
public:
    void getData()
    {
        AdminProduct::getData();
        ofstream productData("productData.txt", ios::app);
        productData.close();
    }
    void putData()
    {
        AdminProduct::putData();
    }
};
/************************************************************************************
mobile class is declared and it is inherited by adminProduct class
**************************************************************************************/
class mobiles : public AdminProduct
{
private:
    char brand[20];
    int ram;

public:
    void getData()
    {
        AdminProduct::getData(); //calling same name base class method
        cout << "\n\t\t\tEnter Mobile Brand : ";
        cin >> brand;
        cout << "\n\t\t\tEnter Ram          :";
        cin >> ram;
        cout << "\n\t\t\t------------------------------------------";
        ofstream productData("productData.txt", ios::app);
        productData.close();
    }
    void putData()
    {
        AdminProduct::putData();
    }
};
/************************************************************************************
beauty class is declared and it is inherited by adminProduct class
**************************************************************************************/
class beauty : public AdminProduct
{
private:
    char type[20];
    char brand[20];

public:
    void getData()
    {
        AdminProduct::getData();
        cout << "\n\t\t\tEnter Face Wash Type  : ";
        cin >> type;
        cout << "\n\t\t\tEnter Face Wash Brand : ";
        cin >> brand;
        cout << "\n\t\t\t------------------------------------------";
        ofstream productData("productData.txt", ios::app);
        productData.close();
    }
    void putData()
    {
        AdminProduct::putData();
    }
};
/************************************************************************************
food class is declared and it is inherited by adminProduct class
**************************************************************************************/
class food : public AdminProduct
{
private:
    int quanti;
    char flavor[20];

public:
    void getData()
    {
        AdminProduct::getData();
        cout << "\n\t\t\tEnter Product Quantity[Weight] : ";
        cin >> quanti;
        cout << "\n\t\t\tEnter Product flavor           : ";
        cin >> flavor;
        cout << "\n\t\t\t------------------------------------------";
        ofstream productData("productData.txt", ios::app);
        productData.close();
    }
    void putData()
    {
        AdminProduct::putData();
    }
};
/************************************************************************************
fashion class is declared and it is inherited by adminProduct class
**************************************************************************************/
class fashion : public AdminProduct
{
private:
    char fabric[20];
    int size;

public:
    void getData()
    {
        AdminProduct::getData();
        cout << "\n\t\t\tEnter Product Fabric : ";
        cin >> fabric;
        cout << "\n\t\t\tEnter Product Size   : ";
        cin >> size;
        cout << "\n\t\t\t------------------------------------------";
        ofstream productData("productData.txt", ios::app);
        productData.close();
    }
    void putData()
    {
        AdminProduct::putData();
    }
};
/************************************************************************************
home class is declared and it is inherited by adminProduct class
**************************************************************************************/
class home : public AdminProduct
{
private:
    char color[20];
    char material[20];

public:
    void getData()
    {
        AdminProduct::getData();
        cout << "\n\t\t\tEnter Product Color    : ";
        cin >> color;
        cout << "\n\t\t\tEnter Product Material : ";
        cin >> material;
        cout << "\n\t\t\t------------------------------------------";
        ofstream productData("productData.txt", ios::app);
        productData.close();
    }
    void putData()
    {
        AdminProduct::putData();
    }
};
/************************************************************************************
productOperation class is declared in which only menu driven code for product
**************************************************************************************/
class productOperations
{
protected:
    int choice;

public:
    void productInfo();
};
/***********************************************************************************
 *productinfo method is meber funciton of productoperation and declaring at outside the class
**************************************************************************************/
void productOperations::productInfo() //calling using scope resolution operator
{
    electronics e1, arr2[20]; //creating object of electronics
    AdminProduct adpro1;      //creating object of base class adminproduct
    AdminProduct *adpro;	//pointer to object
    adpro=&adpro1;			//take a rference
    customer cust;            //creating object of customer class
    head h1;                  //creating object of head class
    home hm1;                 //creating obejet of home class
    book b1, arr1[200]; //creating object of book class
	adpro=&b1;      //taking reference from base class
    mobiles m1;               //creating object of mobiles clas
    beauty beu1;              //creating object of beauty class
    fashion f1;               //creating object of fashion class
    food fo1;                 //creating object of food class
    do
    {
        system("cls");
        cout << "\n\n\t\t\t__________ ADMIN OPERATIONS ___________";
        cout << "\n\n\t\t\t\t|1. View Users";
        cout << "\n\n\t\t\t\t|2. View Customers";
        cout << "\n\n\t\t\t\t|3. Store Section";
        cout << "\n\n\t\t\t\t|4. Logout";
        cout << "\n\n\t\t\t------------------------------------------------------";
        cout << "\n\n\t\t\tEnter Your Choice[1-4] :";
        cin >> choice;
        switch (choice)
        {
        case 1:
            h1.userInfo(); //calling userInfo function of head class
            break;
        case 2:
            cust.displayCustInfo(); //calling displaycustinfo method of customer class
            break;
        case 3:
            do
            {
                system("cls");
                cout << "\n\n\t\t\t _____________ ADMIN MENU _________________";
                cout << "\n\n\t\t\t\t|1. Add Product In Store Room";
                cout << "\n\n\t\t\t\t|2. Display Product";
                cout << "\n\n\t\t\t\t|3. Update Product";
                cout << "\n\n\t\t\t\t|4. Search Product";
                cout << "\n\n\t\t\t\t|5. Delete Product";
                cout << "\n\n\t\t\t\t|6. Go Back";
                cout << "\n\t\t\t------------------------------------------------------------";
                cout << "\n\n\t\t\tEnter Your Choice[1-6] :";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    do
                    {
                        system("cls");
                        cout << "\n\t\t\t_____________ PRODUCT CATEGORY _______________";
                        cout << "\n\n\t\t\t\t1. Books";
                        cout << "\n\n\t\t\t\t2. Electronics";
                        cout << "\n\n\t\t\t\t3. Mobiles";
                        cout << "\n\n\t\t\t\t4. Beauty";
                        cout << "\n\n\t\t\t\t5. Food and more";
                        cout << "\n\n\t\t\t\t6. Fashion";
                        cout << "\n\n\t\t\t\t7. Home";
                        cout << "\n\n\t\t\t\t8. Toys";
                        cout << "\n\n\t\t\t\t9. Go Admin Menu";
                        cout << "\n\n\t\t\t---------------------------------------------------";
                        cout << "\n\t\t\tEnter Your Choice [1-9] : ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            system("cls");
                            cout << "\n\t\t\t--------------- Book Store ---------------------";
                            adpro->getData();//this pointer
                            cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                            cin.get();
                            cin.get();
                            system("cls");
                            break;
                        case 2:
                            do
                            {
                                system("cls");
                                cout << "\n\n\t\t\t__________ ELECTRONICS ____________ ";
                                cout << "\n\n\t\t\t\t1. Laptop Or Desktops";
                                cout << "\n\n\t\t\t\t2. Headphones";
                                cout << "\n\n\t\t\t\t3. Computer Accessories";
                                cout << "\n\n\t\t\t\t4. Go Product Department";
                                cout << "\n\n\t\t\tEnter Your Choice[1-4] : ";
                                cin >> choice;
                                switch (choice)
                                {
                                case 1:
                        			
                                    e1.getData();
                                    cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                                    cin.get();
                                    cin.get();
                                    break;
                                case 2:
                                    e1.getData();
                                    cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                                    cin.get();
                                    cin.get();
                                    break;
                                case 3:
                                    e1.getData();
                                    cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                                    cin.get();
                                    cin.get();
                                    break;
                                case 4:
                                    system("cls");
                                    break;
                                default:
                                    cout << "\nError!!! Plz check again...";
                                }
                            } while (choice != 4);
                            break;
                        case 3:
                            system("cls");
                            m1.getData();
                            cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                            cin.get();
                            cin.get();
                            break;
                        case 4:
                            system("cls");
                            beu1.getData();
                            cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                            cin.get();
                            cin.get();
                            break;
                        case 5:
                            system("cls");
                            fo1.getData();
                            cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                            cin.get();
                            cin.get();
                            break;
                        case 6:
                            system("cls");
                            f1.getData();
                            cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                            cin.get();
                            cin.get();
                            break;
                        case 7:
                            system("cls");
                            hm1.getData();
                            cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                            cin.get();
                            cin.get();
                            break;
                        case 8:
                            system("cls");
                            cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                            cin.get();
                            cin.get();
                            break;
                        case 9:
                            system("cls");
                            break;
                        default:
                            cout << "\nERROR !!! Plz Check again...";
                        }
                    } while (choice != 9);

                    break;
                case 2:
                    system("cls");
                    adpro1.putData(); //calling putdata of adminproduct class
                    cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                    cin.get();
                    cin.get();
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    adpro1.updateProduct(); //calling update product of adminprodcut clas
                    cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                    cin.get();
                    cin.get();
                    system("cls");
                    break;
                case 4:
                    system("cls");
                    adpro1.searchProduct(); //calling searchproduct of adminroduct class
                    cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                    cin.get();
                    cin.get();
                    system("cls");
                    break;
                case 5:
                    system("cls");
                    adpro1.cancelProduct();
                    cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
                    cin.get();
                    cin.get();
                    system("cls");
                    break;
                case 6:
                    system("cls");
                    break;
                default:
                    cout << "\nERROR !!!! Plz Check Again";
                }
            } while (choice != 6);
            break;
        case 4:
            system("cls");
            break;
        }
    } while (choice != 4);
}
/************************************************************************************
create class admin and its inherited by productOperations..here single type inheritance is occured
**************************************************************************************/
class Admin : public productOperations
{
private:
    char aduser[20], adpass[20];
    friend class AdminProduct; //friend class concept

public:
    Admin() //default constrcutor admin class
    {
    }
    Admin(char aduser[], char adpass[]) //parametric constructor
    {
        int count;
        //this keyword use for pointing current object/value
        strcpy(this->aduser, aduser);                                                      //predefined string function
        strcpy(this->adpass, adpass);                                                      //predefined string function
        if (strcmp(this->aduser, "ravindra") == 0 && strcmp(this->adpass, "admin123") == 0) //checking admin username and passowrd
        {
            count = 1;
            system("cls");
        }
        if (count == 1)
        {
            gotoxy(30, 10);
            cout << "\n\n\t\t\tLoading Please Wait...";
            for (int i = 1; i <= 8; i++)
            {
                Sleep(600);
                cout << ".";
            }
            system("cls");
            cout << "\n\n\t\t\t____[LOGIN SUCCESFULL]____";
            cout << "\n\n\t\t\tWelcome To Adminstrative Department !!!";
            cout << "\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
            productOperations::productInfo(); //calling productinfo method of base class
        }
        else
        {
            system("cls");
            cout << "\n\n\t\t\t____[Invalid Username or password]____";
            cout << "\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
        }
    }
    ~Admin() //destructor
    {
    }
};
/************************************************************************************
add to cart method is used to add product to cart
**************************************************************************************/
void customer::addTocart()
{
    cout << "\n\n\t\t[ So Please Enter The Product ID and Quantity ]";
    do
    {
        cout << "\n\n\t\t\tEnter The Product Id : ";
        cin >> order_id[c];
        cout << "\n\t\t\tEnter The Product Quantity : ";
        cin >> order_quanti[c];
        c++;
        cout << "\n\n\t\t\t<Do You Want to Order another Product[y/Y] ?>";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\n\t\t\t______Thank You For Ordering Product_____";
    cout << "\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
    cin.get();
}
/************************************************************************************
custInfo() method is taking customer data and save into database
**************************************************************************************/
void customer::custInfo()
{
    int flag = 0;

    ofstream payment("customerInfo.txt", ios::app);
    cout << "\n\n\t\t\t\t || W E L C O M E  T O  E V E R G R E E N  S H O P P I N G  M A L L ||";
    cout << "\n-----------------------------------------------------------------------------------------------------------";

    cout << "\n\t\t\tEnter Customer Name   : ";
    cin.getline(name, 100);//here getline function is used 
    cout << "\n\n\t\t\tEnter CUstomer Id   : ";
    cin >> custId;
    cout << "\n\t\t\tEnter Email-Id : ";
    cin >> email;
    cout << "\n\t\t\tEnter City    : ";
    cin >> city;
label: //declare label
    cout << "\n\n\t\t\tEnter Pincode   : ";
    cin >> pincode;
    try //excption handling
    {
        //code for checking pincode ...valadation of pincode
        for (int i = 0; i < pincode.length(); i++)
        {
            if (pincode[i] - 48 > 0 && pincode[i] - 48 <= 9)
            {
                flag = 1;
                continue;
            }
            else
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1 && pincode.length() == 6)
        {
        }
        else if (flag == 0 || pincode.length() != 6)
        {
            throw 1; //throw kwyword
        }
    }
    catch (int n) //catach keyword
    {
        cout << "\n\n\t\t\t\t\tPlease Enter Valid Pincode";
        getch();
        goto label; //goto statememt
    }

label1: //declarations of label
    cout << "\n\n\t\t\tEnter Phone Number    : ";
    cin >> phone_no;
    try //try catch block
    {
        //code for valadating mobile no
        for (int i = 0; i < phone_no.length(); i++)
        {
            if (phone_no[i] - 48 >= 0 && phone_no[i] - 48 <= 9)
            {
                flag = 1;
                continue;
            }
            else
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1 && phone_no.length() == 10)
        {
        }
        else if (flag == 0 || phone_no.length() != 10)
        {
            throw 1; //throw keyword
        }
    }
    catch (int n) //catach block
    {
        cout << "\n\n\t\t\t\t\tPlease Enter Valid Phone Number";
        getch();
        goto label1; //goto statement
    }

    cout << "\n\n\t\t\tEnter State       : ";
    cin >> state;
    cout << "\n\t\t\tEnter Country       : ";
    cin >> country;
    cout << "\n\t---------------------------------------------------------------------------------------------------";
    cout << "\n\n\t\t\tRecord save successfully.";
    cout << "\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
    cin.get();
    payment << custId << "\t" << name << "\t" << email << "\t" << city << "\t" << pincode << "\t" << phone_no << "\t" << state << "\t" << country << "\n\n";
    payment.close();
}
/************************************************************************************
dsiplaycustinfo method displaying just customer information
**************************************************************************************/
void customer::displayCustInfo()
{
    system("cls");
    ifstream customerInfo("customerInfo.txt");
    if (!customerInfo)
    {
        cout << "\n\n\t\t\t____[File Openning Error!]____";
    }
    else
    {
        cout << "\n\n\t\t\t\t\t______CUSTOMERS DETAILS_______";
        customerInfo >> custId >> name >> email >> city >> pincode >> phone_no >> state >> country;
        while (!customerInfo.eof()) //data retrive from database
        {
            cout << "\n\t\t\tCustomer Id   : " << custId;
            cout << "\n\t\t\tCustomer Name : " << name;
            cout << "\n\t\t\tEmail-Id      : " << email;
            cout << "\n\t\t\tCity          : " << city;
            cout<<"\n\t\t\tPinCode         : "<<pincode;
            cout << "\n\t\t\tMobile Number : " << phone_no;
            cout << "\n\t\t\tState         : " << state;
            cout << "\n\t\t\tCountry       : " << country;
            cout << "\n______________________________________________________________________________________________________________________________";
            customerInfo >> custId >> name >> email >> city >> pincode >> phone_no >> state >> country;
        }
        customerInfo.close();
    }
    cout << "\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
    cin.get();
}
/************************************************************************************
paymentmode() method is only for selecting payment mod
**************************************************************************************/
void customer::paymentMode()
{
    char ch;
    int choice;
    do
    {
        system("cls");
        cout << "\n\n\n\t\t\t\t ||W E L C O M E  T O  E V E R G R E E N  S H O P P I N G  M A L L ||";
        cout << "\n\t------------------------------------------------------------------------------";
        cout << "\n\n\t\t\t<Select Payment Mode>";
        cout << "\n\n\t\t\t1. Cash On Delivery.";
        cout << "\n\n\t\t\t2. Credit Card.";
        cout << "\n\n\t\t\t3. Debit Card.";
        cout << "\n\n\t\t\t4. UPI Pay.";
        cout << "\n\t------------------------------------------------------------------------------";
        cout << "\n\t\t\tEnter Your Choice : ";
        cin >> choice;
        cout << "\n\n\t\t**************************************************************************";
        switch (choice)
        {
        case 1:
            cout << "\n\n\t\t\tYou Have Selected Cash on Delivery.";
            break;
        case 2:
            cout << "\n\n\t\t\tYou Have Selected Payment from Credit Card";
            break;
        case 3:
            cout << "\n\n\t\t\tYou Have Selected Payment from Debit Card";
            break;
        case 4:
            cout << "\n\n\t\t\tYou Have Selected UPI Payement Mode.";
            break;
        default:
            cout << "\n\n\t\t[Invalid...]";
        }
        cout << "\n\n\n\t\t<Are You sure with your Option [y/n]>:";
        cin >> ch;
    } while (ch == 'n' || ch == 'N');
    cout << "\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
    cin.get();
}
/************************************************************************************
displaying sub bill of product
**************************************************************************************/
void customer::subBill()
{
    float subtotal = 0;
    cout << "\n\n\t\t**************************************  Bill Status ***************************************\n";
    cout << "\n\t\t\t\tProdID.\tPrName\tQuanti\tDisc%\tPrice\tAmount";
    cout << "\n\t\t______________________________________________________________________________________________________________";
    for (int x = 0; x <= c; x++)
    {
        ofstream billStatus("billStatus.txt", ios::app); //store data in database
        ifstream admindata("productData.txt");
        admindata >> proId >> proName >> price >> quanti >> dis;
        while (!admindata.eof())
        {
            if (proId == order_id[x])
            {
                amt = price * order_quanti[x];
                subtotal = subtotal + amt;
                cout << "\n\t\t\t\t"
                     << order_id[x] << "\t" << proName << "\t" << order_quanti[x] << "\t" << dis << "\t" << price << "\t" << amt;
                cout << "\n\t\t_________________________________________________________________________________________________________";
            }
            admindata >> proId >> proName >> price >> quanti >> dis;
        }
        billStatus << order_id[x] << "\t" << proName << "\t" << order_quanti[x] << "\t" << dis << "\t" << price << "\t " << amt << "\n\n";
        billStatus.close();
        admindata.close();
    }
    cout << "\n\n\t\t\t\tSUB TOTAL[Without Tax] = " << subtotal;
    cout << "\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
}
/************************************************************************************
displaying final bill of user carts with cgsts and sgst
**************************************************************************************/
void customer::viewBill()
{
    //system("cls");
    cout << "\n\n\t\t***************************************** FINAL BILL ********************************************\n";
    cout << "\n\t\t\tPrID.\tPrName\tQuanti\tDisc%\tPrice\tAmount\tCGST\tSGST\tAfterDiscountAmount\tSaveAmt ";
    cout << "\n\t\t________________________________________________________________________________________________________________";
    for (int x = 0; x <= c; x++)
    {
        ofstream userdata("addToCart.txt", ios::app);
        ifstream admindata("productData.txt");
        admindata >> proId >> proName >> price >> quanti >> dis;
        while (!admindata.eof())
        {
            if (proId == order_id[x])
            {
                amt = price * order_quanti[x]; //calculating bill
                damt = amt - (amt * dis / 100);
                save = amt - damt;
                cgst = damt * 0.06;
                sgst = damt * 0.06;
                totalsave = totalsave + save;
                total = total + damt + cgst + sgst;
                cout << "\n\t\t\t"
                     << order_id[x] << "\t" << proName << "\t" << order_quanti[x] << "\t" << dis << "\t" << price << "\t" << amt << "\t" << cgst << "\t" << sgst << "\t\t" << damt << "\t\t" << save;
                cout << "\n\t\t___________________________________________________________________________________________________________________";
            }
            admindata >> proId >> proName >> price >> quanti >> dis;
        }
        userdata << order_id[x] << "\t" << proName << "\t" << order_quanti[x] << "\t" << dis << "\t" << price << "\t " << amt << "\t " << damt << "\t " << total << "\t " << cgst << "\t " << sgst << "\t" << save << "\n\n";
        userdata.close();
        admindata.close();
    }
    cout << "\n\n\t\t\t\tGRAND TOTAL[With Tax] : " << total << " Rs/-"; //displaying grand total
    cout << "\n\n\t\t\t\tYou Will Save Rupees On This Order : " << totalsave << " Rs/-";
    cout << "\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
}
/************************************************************************************
displaying final bill with customers inforamtions which cust have purchase products
**************************************************************************************/
void customer::finalBill()
{
    int count, custIdd;
    system("cls");
    ifstream customerInfo("customerInfo.txt");
    if (!customerInfo)
    {
        cout << "\n\n\t\t\t____[File Openning Error!]____";
    }
    else
    {
        cout << "\n\n\t\t\tEnter Customer ID To Generate Bill : ";
        cin >> custIdd;
        cout << "\n\n\t\t\t<Press Enter Key To Generate Bill>";
        cin.get();
        cin.get();
        gotoxy(30, 10);
        cout << "\n\n\t\t\tGenerating Bill Please Wait...";
        for (int i = 1; i <= 8; i++)
        {
            Sleep(600);
            cout << ".";
        }
        system("cls");
        customerInfo >> custId >> name >> email >> city >> pincode >> phone_no >> state >> country;
        while (!customerInfo.eof()) //retrive data from custmer database
        {
            if (custId == custIdd)
            {
                cout << "\n\n\t\t\t\t ||W E L C O M E  T O  E V E R G R E E N  S H O P P I N G  M A L L ||";
                cout << "\n\n\n\t\t\t\t\t_____Customer Description_____";
                cout << "\n\t\t_______________________________________________________________________________________________________________________";
                cout << "\n\n\t\t|Customer Id        : " << custId  <<"\t\t\t|Customer Name        : " << name;
                cout << "\n\n\t\t|Email-Id           : " << email   <<"\t\t\t|City                 : " << city;
                cout << "\n\n\t\t|Pincode            : " << pincode <<"\t\t\t|Phone No             : " << phone_no;
                count++;
                break;
            }
            customerInfo >> custId >> name >> email >> city >> pincode >> phone_no >> state >> country;
        }
        customerInfo.close();
        if (count == 0)
        {
            cout << "\n\n\t\t\tCustomer Id is not found";
        }
    }
    viewBill(); //calling viewbill method of same class
}


/************************************************************************************
custFinal() method is declared for customer final operations
**************************************************************************************/
void customer::custFinal()
{
    AdminProduct adpro1; //creating object of adminproduct class
    char ch;
    system("cls");
    cout << "\n\n\t\t\t\t ||W E L C O M E  T O  E V E R G R E E N  S H O P P I N G  M A L L ||";
    cout << "\n\n\t\t\t\t\t\tPRODUCT DETAILS";
    cout << "\n_____________________________________________________________________________________________________________________________";
    adpro1.putData(); //calling putdata method of adminproduct class
    cout << "\n_____________________________________________________________________________________________________________________________";
    cout << "\n\n\t\t\tAdd To Cart Product....[Y/N]: ";
    cin >> ch;
    if (ch == 'Y' || ch == 'y')
    {

        addTocart(); //nested function...function within member function
        system("cls");
        cout << "\n\n\t\t\t\t ||W E L C O M E  T O  E V E R G R E E N  S H O P P I N G  M A L L ||";
       	subBill();//calling subbill method of customer class
        cout << "\n";
        cout << "\n\n\t\t\tAre You Sure To Place Your Order ? [y/Y]: ";
        cin >> ch;
        if (ch == 'y' || ch == 'Y')
        {
            cout << "\n\n\t**********************************************************************************";
            cout << "\n\n\t\t\t____[Thank You For Placing Order]_____.";
            cout << "\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
            system("cls");
            custInfo();    //calling customer info method
            paymentMode(); //calling payment mode method
            finalBill();   //calling final bill method
            system("cls");
            cout << "\n\n\t\t\tThank You For Sopping With Us.";
            cout << "\n\n\t\t\tT H A N K  Y O U ____ V I S I T  A G A I N";
            cout << "\n\n\t\t\t<Press Enter Key To LOGOUT>";
            cin.get();
        }
        else
        {
            cout << "\n\n\tIt's Okay......";
            cout << "\n\n\t\t\t<Press Enter Key To Continue>";
            cin.get();
            cin.get();
        }
    }
    else
    {
        system("cls");
        cout << "\n\n\t\tThank You For Visit..";
        cout << "\n\n\t\t! VISIT AGAIN !";
        cout << "\n\n\t\t\t<Press Enter Key To LOGOUT>";
        cin.get();
        cin.get();
        system("cls");
    }
}
/************************************************************************************
main function declartions
**************************************************************************************/
int main()
{
    head h1; //creating object of head class
    int choice;
    customer cust; //creating obejct of customer class
    char aduser[20], adpass[20];
    system("cls");
    system("color 30"); //givig color to console
                        /************************************************************************************
loading animation
**************************************************************************************/
    cout << "\n\n\n\t\t\tTo Install Software Press Enter Key .";
    getch();
    system("cls");
    gotoxy(30, 10);
    cout << "\n\t\tPlease Wait Installing...";
    for (int i = 1; i <= 10; i++)
    {
        Sleep(500);
        cout << ".";
    }
    system("cls");
    cout << "\n\n\n\t\t\t\t ||W E L C O M E  T O  E V E R G R E E N  S H O P P I N G  M A L L ||";
    cout << "\n\t--------------------------------------------------------------------------------------------------------------";
    cout << "\n\n\t\t\t\t\t    || Government Polytechnic Pune ||";
    cout << "\n\n\t\t\t\t\tProject Title - Shopping Management with Billing System.";
    cout << "\n\n\n\t\t| Project By :-";
    cout << "\n\n\t\t\t| 1. Ravindra Kadam     9022404626		rbkadam2320@gmail.com \t   |";
    cout << "\n\n\n\t\t| Guided By :-";
    cout << "\n\n\t\t\t|Mrs.Lalita Korde Mam";
    cout << "\n\n\n\n\t\t\t<Press Enter Key To Continue>";
    cin.get();
    system("cls");
    do //do-while loop
    {
        try
        { //...Exception Handling

            system("cls");
            cout << "\n\n\n\n\t\t\t\t || W E L C O M E  T O  E V E R G R E E N  S H O P P I N G  M A L L ||";
            cout << "\n\n\t\t\t\t--------------------------------------------------------------";
            cout << "\n\t\t\t\t\t\t _____$ HOME PAGE MENU $_____";
            cout << "\n\n\t\t\t\t\t\t1. ADMINSTRATION LOGIN" << endl;
            cout << "\n\t\t\t\t\t\t2. USER LOGIN" << endl;
            cout << "\n\t\t\t\t\t\t3. SIGNUP/REGISTER HERE" << endl;
            cout << "\n\t\t\t\t\t\t4. FORGOT PASSWORD OR USERNAME" << endl;
            cout << "\n\t\t\t\t\t\t5. CONTACT US" << endl;
            cout << "\n\t\t\t\t\t\t6. EXIT" << endl;
            cout << "\n\n\t\t\t\t--------------------------------------------------------------";
            cout << "\n\n\t\t\t\t\t\tENTER YOUR CHOICE [1-6] : ";
            cin >> choice;
            cout << endl;
            switch (choice)
            {
            case 1:
                system("cls");
                cout << "\n\n\n\t\t\t| Enter Administrative Username : ";
                cin >> aduser;
                cout << "\n\t\t\t| Enter Administrative Password : ";
                h1.password(adpass, 8); //calling password function
                Admin(aduser, adpass);  //calling constructor of class admin
                break;
            case 2:
                h1.userLogin(cust); //calling userlogin method and passing object as argument
                break;
            case 3:
                h1.userRegister(); //calling userregister method of head class
                break;
            case 4:
                h1.forgotPassword(); //calling forgotpassword method of head class
                break;
            case 5:
                h1.contactUs(); //calling contactus method of head class
                break;
            case 6:
                break;
            default:
                throw 1; //throw integer value
            }
        }
        catch (int n) //catch block
        {
            cout << "\n\n\t\t\t\t\tInvalid Choice..Please Enter Valid Choice.";
        }
    } while (choice != 6);
    return 0; //returning 0
} //end of main
/* T H A N K  Y O U  */
