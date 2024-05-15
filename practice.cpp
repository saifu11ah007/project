#include <iostream>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

int flightSerial[15] = { 101, 102, 103, 122, 123, 124, 131, 132, 133, 241, 242, 243, 501, 502, 503 };
int price[16] = { 12000, 10000, 15000, 11000, 14000, 10000, 12000, 13500, 9000, 12500, 14000, 12000, 16000, 16500, 13500 };
int selectFlight;
int perPersonPrice;

const int max_members=20;
string  gender;

string passenger_name[max_members], passenger_gender[max_members], passenger_CNIC[max_members];
int ticket_fare[max_members];
string passenger_destinationCity, passenger_departureCity;
int passenger_age[max_members];
int passenger_ticketSerialNo, passenger_seat;
string global_destination[max_members], global_departure[max_members];
int global_destiny;
int global_members;
int  global_serial;
string gendermale , genderfemale, actualdate;

string Gendercheck();
void calculatePrice();
void Gender();
int serialnum[max_members]={};

void setPerPersonPrice(int price);
void personalinfo();
int getperPersonPrice();
int getSelectFlight();
void showWaitingList();
void confirmPayment();
void modifyTicket();

void viewInfo();
void Exit();
void booking();
int showMenu();
void lahore();
void karachi();
void islamabad();
void quetta();
void peshawar();
void setPerPersonPrice(int price);
bool isValidDate(int d, int m, int y);
time_t t = time(NULL);
tm timeStruct;
// localtime_r(&t, &timeStruct);

const int MAX_VALID_YR = 2024;
const int MIN_VALID_YR = 2024;

const int MIN_VALID_MNTH = 4;
const int MAX_VALID_MNTH = 5 + 1;

bool isLeap(int year)
{
	// Return true if year
	// is a multiple of 4 and
	// not multiple of 100.
	// OR year is multiple of 400.
	return (((year % 4 == 0) &&
		(year % 100 != 0)) ||
		(year % 400 == 0));
}

bool isValidDate(int d, int m, int y)
{
	// If year, month and day
	// are not in given range
	if (y > MAX_VALID_YR ||
		y < MIN_VALID_YR)
		return false;
	if (m < MIN_VALID_MNTH || m > MAX_VALID_MNTH)
		return false;
	if (d < 1 || d > 31)
		return false;

	// Handle February month
	// with leap year
	if (m == 2)
	{
		if (isLeap(y))
			return (d <= 29);
		else
			return (d <= 28);
	}

	// Months of April, June,
	// Sept and Nov must have
	// number of days less than
	// or equal to 30.
	if (m == 4 || m == 6 ||
		m == 9 || m == 11)
		return (d <= 30);

	return true;
}

void booking() {
    bool cont = false;
    do {
        system("CLS");
        int departureCity, destinationCity;
        string date = "", cnic = "";
        cout << "Press Number as shown below to choose your departure city: " << endl;
        cout << "1-\tKarachi" << endl;
        cout << "2-\tPeshawar " << endl;
        cout << "3-\tIslamabad " << endl;
        cout << "4-\tQuetta" << endl;
        cout << "5-\tLahore " << endl;
        cout << "Enter your departure city from above mentioned cities: ";
        cin >> departureCity;
        cout << "---\t---\n";
        cout << "Enter your Destination city from above mentioned cities: ";
        cin >> destinationCity;

        // Handling city selection
        switch (departureCity) {
            case 1:
                passenger_departureCity = "Karachi";
                break;
            case 2:
                passenger_departureCity = "Peshawar";
                break;
            case 3:
                passenger_departureCity = "Islamabad";
                break;
            case 4:
                passenger_departureCity = "Quetta";
                break;
            case 5:
                passenger_departureCity = "Lahore";
                break;
            default:
                cout << "Invalid departure city. Please try again." << endl;
                cout << "Enter your departure city from above mentioned cities: ";
                cin >> departureCity;
                break;
        }

        switch (destinationCity) {
            case 1:
                passenger_destinationCity = "Karachi";
                break;
            case 2:
                passenger_destinationCity = "Peshawar";
                break;
            case 3:
                passenger_destinationCity = "Islamabad";
                break;
            case 4:
                passenger_destinationCity = "Quetta";
                break;
            case 5:
                passenger_destinationCity = "Lahore";
                break;
            default:
                cout << "Invalid destination city. Please try again." << endl;
                cout << "\nEnter your Destination city from above mentioned cities: ";
                cin >> destinationCity;
                break;
        }

        // Check if departure and destination cities are the same
        if (destinationCity == departureCity) {
            cout << "Departure city and destination city cannot be the same. Please choose again." << endl;
            cout << "\nEnter your departure city from above mentioned cities: ";
            cin >> departureCity;
            cout << "---\t---\n";
            cout << "\nEnter your Destination city from above mentioned cities: ";
            cin >> destinationCity;
        }
        
          global_destiny=destinationCity;
        
        personalinfo();
        cout << "Enter 1 to continue, any other key to exit: ";
        string s;
        cin >> s;
        if(s.size() == 1 && s[0] == '1') {
            cont = true;
        } else {
            cont = false;
        }
    } while(cont);
}

void personalinfo(){
  bool cont=false;
  do{
    int d = 0, m = 0, y = 0;
    string date = "" ;
    string cnic[max_members];
    bool validDate = false;
    do {
      cout << "Enter Date (dd mm yyyy): ";
      cin >> d;
      cout << "Enter Month (dd mm yyyy): ";
      cin >> m;
      cout << "Enter Year (dd mm yyyy): ";
      cin >>y;

      validDate = isValidDate(d, m, y);
      if (!validDate) {
          cout << "Invalid date. Please enter again." << endl;
        }
    } while (!validDate);
    stringstream formattedDate;
    formattedDate << setw(2) << setfill('0') << d << " / " << setw(2) << setfill('0') << m << " / " << y;

    string formattedDateString = formattedDate.str();
    actualdate = formattedDateString;

    int members;
    cout << "\nFor how many people do you want to book tickets: ";
    cin >> members;
    if (members <= 0 || members > 20) {
        cout << "Invalid number of passengers. Please enter a value between 1 and 20." << endl;
        continue; // Restart loop
    }
    global_members = members;
    for (int i=0; i<global_members; i++){
            global_departure[i]=passenger_departureCity;
            global_destination[i]=passenger_destinationCity;
          }
    for (int i = 0; i < global_members; i++) {

      string name[max_members];
      string MorF;
      int age[max_members]; 
      int ticketSerialNo = 0;
      serialnum[i] = (rand() % 1000) + 1;
      cout << "Serial number for passenger " << i + 1 << ": " << serialnum[i] << endl;

      // Passenger details input
      cout << "Enter passenger name: ";
      cin >> name[i];

      cout << "Enter your age: ";
      cin >> age[i];

      MorF=Gendercheck();

      // CNIC validation
      cout << "Enter CNIC (without dashes): ";
      cin >> cnic[i];

      if (cnic[i].length() != 13) {
          cout << "Enter correct CNIC number (without dashes): ";
          cin >> cnic[i];
      }

      cnic[i] = cnic[i].insert(5, "-");
      cnic[i] = cnic[i].insert(13, "-");
      cout<<endl<<"-------------------\n";
      
      int seatnum= (rand() % 20) + 1;
      
      passenger_name[i] = name[i];
      
      passenger_age[i] = age[i];
      passenger_seat =seatnum;
      // passenger_date = date;
      passenger_gender[i] = MorF;
      passenger_CNIC[i] = cnic[i];
      passenger_ticketSerialNo = i;
      

    }

    switch (global_destiny) {
      case 1: karachi();break;
      case 2:peshawar(); break;
      case 3: islamabad(); break;
      case 4:  quetta(); break;
      case 5: lahore(); break;
      default:
          cout << "Wrong destinationCity\n";
          break;
    }
    cout << "Enter 1 to continue, any other key to exit: ";
            string s;
            cin >> s;
            if(s.size() == 1 && s[0] == '1') {
                cont = true;
            } else {
                cont = false;
            }
        } while(cont);
}
void mainmenu() {
    //opens a display menu 
    bool cont=false;
    do{
        int option;
        system("CLS");
        cout << endl;
        cout << "\n----------------------------------" << endl;
        cout << "  Pakistan International Airline ";
        cout << "\n";
        cout << "----------------------------------";

        cout << "\n 11 Flights Avaialable to Cities";
        cout << "\n 1 Booking";
        cout << "\n 2 Price";
        cout << "\n 3 View Ticket details";
        cout << "\n 4 Modify Ticket details";
        cout << "\n 5 Payment confirmation ";
        cout << "\n 6 Cancel your booking";
        cout << "\n 7 Show waiting List";
        cout << "\n 0 Exit \n";
        cout << "\nEnter your Choice:  ";
        cin >> option;

			switch (option)
			{
			case 11:
				cout << endl;
				cout << " Karachi";
				cout << "\n Peshawar ";
				cout << "\n Islamabad ";
				cout << "\n Quetta";
				cout << "\n Lahore " << endl;

				break;
			case 1:
				cout << "\tBook PIA Flight Tickets"<< endl;
        booking();
				break;
			case 2:
				cout << endl;
				calculatePrice();
				break;
			case 3:
				cout << endl;
				viewInfo();
				break;
			case 4:
				cout << endl;
				modifyTicket();
				break;
			case 5:
				cout << endl;
				confirmPayment();
				break;
			case 6:
				cout << endl;
				// DeletingPassengerInfo();
				break;
			case 7:
				cout << endl;
				// showWaitingList();
			}
      cout << "Enter 1 to continue, any other key to exit: ";
              string s;
              cin >> s;
              if(s.size() == 1 && s[0] == '1') {
                  cont = true;
              } else {
                  cont = false;
              }
          } while(cont);
}
void welcomeScreen() {
    system("CLS");
    cout << "\t---\tAyan Airport International    ---\t" << endl;
    getch();
}

int main() {
  srand(time(NULL));
    welcomeScreen();
    mainmenu();

    return 0;
}
void exitScreen(){
    system("CLS");
    cout<<"Thankyou for using our platform"<<endl;
    exit(0);
}

void Exit(){
    exitScreen();
}
void lahore()
  {
    system("CLS");
    cout << "\n\n Flights available for Lahore:";
    cout << "\n  " << flightSerial[0] << "-Flight (time: 5:00pm) " << price[0] << "/- per person";
    cout << "\n  " << flightSerial[1] << "-Flight (time: 12:00am) " << price[1] << "/- per person";
    cout << "\n  " << flightSerial[2] << "-Flight (time: 8:00pm) " << price[2] << "/- per person";

    cout << "\nChoose your flight: ";
    cin >> selectFlight;

    for (int i = 0; i < 3; i++)
    {
      if (selectFlight == flightSerial[i])
      {
        setPerPersonPrice(price[i]);
        break;
      }
    }
  }

void karachi()
{
  system("CLS");
  cout << "\n You have chosen Karachi.";
  cout << "\n Flights available for Karachi:";
  cout << "\n  " << flightSerial[3] << "-Flight (time: 3:00pm) " << price[3] << "/- per person";
  cout << "\n  " << flightSerial[4] << "-Flight (time: 7:00pm) " << price[4] << "/- per person";
  cout << "\n  " << flightSerial[5] << "-Flight (time: 2:00am) " << price[5] << "/- per person";

  cout << "\n\nChoose your flight: ";
  cin >> selectFlight;

  for (int i = 3; i <= 5; i++)
  {
    if (selectFlight == flightSerial[i])
    {
      setPerPersonPrice(price[i]);
      break;
    }
  }
}

void islamabad()
{
  system("CLS");
  cout << "\n You have chosen Islamabad.";
  cout << "\n Flights available for Islamabad:";
  cout << "\n  " << flightSerial[6] << "-Flight (time: 4:00pm) " << price[6] << "/- per person";
  cout << "\n  " << flightSerial[7] << "-Flight (time: 9:00pm) " << price[7] << "/- per person";
  cout << "\n  " << flightSerial[8] << "-Flight (time: 2:00am) " << price[8] << "/- per person";

  cout << "\n\nChoose your flight: ";
  cin >> selectFlight;

  for (int i = 6; i <= 8; i++)
  {
    if (selectFlight == flightSerial[i])
    {
      setPerPersonPrice(price[i]);
      break;
    }
  }
}


void peshawar()
{
  system("CLS");
  cout << "\n You have chosen Peshawar.";
  cout << "\n Flights available for Peshawar:";
  cout << "\n  " << flightSerial[9] << "-Flight (time: 5:00pm) " << price[9] << "/- per person";
  cout << "\n  " << flightSerial[10] << "-Flight (time: 6:00pm) " << price[10] << "/- per person";
  cout << "\n  " << flightSerial[11] << "-Flight (time: 1:00am) " << price[11] << "/- per person";

  cout << "\n\nChoose your flight: ";
  cin >> selectFlight;

  for (int i = 9; i <= 11; i++)
  {
    if (selectFlight == flightSerial[i])
    {
      setPerPersonPrice(price[i]);
      break;
    }
  }
}


void quetta()
{
  system("CLS");
  cout << "\n Flights available for Quetta:";
  cout << "\n  " << flightSerial[12] << "-Flight (time: 4:00am) " << price[12] << "/- per person";
  cout << "\n  " << flightSerial[13] << "-Flight (time: 3:00pm) " << price[13] << "/- per person";
  cout << "\n  " << flightSerial[14] << "-Flight (time: 6:00am) " << price[14] << "/- per person";

  cout << "\n\nChoose your flight: ";
  cin >> selectFlight;

  for (int i = 12; i <= 14; i++)
  {
    if (selectFlight == flightSerial[i])
    {
      setPerPersonPrice(price[i]);
      break;
    }
  }
}


void setPerPersonPrice(int price)
{
  perPersonPrice = price;
}


int getperPersonPrice()
{
  return perPersonPrice;
}


int getSelectFlight()
{
  return selectFlight;
}

void showWaitingList()
{
  system("CLS");
  int serial;
  cout<<"Please enter your serial num: ";
  cin>>serial;
    while (serial == global_serial)
    {
      cout << "_____________________________________________________________________ " << endl << endl;
      cout << "| Serial No.:     \t" << "S-" << global_serial << " \t\t\t|" << endl;
      cout << "| Passenger Name: \t" << passenger_name << " \t\t\t|" << endl;
      cout << "| Age:            \t" << passenger_age << " \t\t\t|" << endl;
      cout << "| CNIC:           \t" << passenger_CNIC << " \t|" << endl;
      cout << "| Booking Date:   \t" << "Under Progress" << " \t\t|" << endl;
      cout << "| From:           \t" << passenger_destinationCity << " \t\t|" << endl;
      cout << "| To:             \t" << passenger_departureCity << " \t\t|" << endl;
      cout << "_____________________________________________________________________ " << endl << endl;
      break;

    }
}
void viewInfo() {

  bool cont = false;

  do {
      int bookCode;
      bool found = false;

      cout << "Enter ticket code: ";
      cin >> bookCode;

      for (int i = 0; i < global_members; i++) {
        if (serialnum[i] == bookCode) {
          cout << "_____________________________________________________________________ " << endl << endl;
          cout << "| Serial No.:     \t" << "S-" << bookCode << " \t\t\t|" << endl;
          cout << "| Boarding No.:     \t" << "D-" << bookCode << " \t\t\t|" << endl;
          cout << "| Passenger Name: \t" << passenger_name[i] << " \t\t\t|" << endl;
          cout << "| Age:            \t" << passenger_age[i] << " \t\t\t|" << endl;
          cout << "| CNIC:           \t" << passenger_CNIC[i] << " \t|" << endl;
          cout << "| Gender:           \t" << passenger_gender[i] << " \t\t\t\t|" << endl;
          cout << "| Booking Date:   \t" << actualdate << " \t\t|" << endl;
          cout << "| From:           \t" << global_departure[i] << " \t\t\t\t|" << endl;
          cout << "| To:             \t" << global_destination[i] << " \t\t\t\t|" << endl;
          cout << "| Flight No.:     \tPA-" << getSelectFlight() << " \t\t|" << endl;
          cout << "| Fare:           \t" << getperPersonPrice() << " \t\t\t|" << endl;
          cout << "_____________________________________________________________________ " << endl;
          cout << endl;
          found = true;
          break; // Exit the loop since we found the value
        }
      }

      if (!found) {
          cout << "Booking not found" << endl;
      }

      cout << "Enter 1 to continue, any other key to exit: ";
      string s;
      cin >> s;
      if (s.size() == 1 && s[0] == '1') {
          cont = true;
      } else {
          cont = false;
      }
   } while (cont);
}

void Gender(){
    char choice;
    cout<<"Choose Gender (M/F): ";
    cin>>choice;
    if ( choice == 'M' || choice == 'm'){
      gender= "Male";
    }
    else if(choice == 'F' ||choice == 'f'){
        gender= "Female";
    }
    else{
        cout<<"Invalid!! plz try again"<<endl;
        Gender();    //recursive function to retake input again
    }

}
string Gendercheck(){
  Gender(); 
  return gender;

}
void calculatePrice(){
    bool cont=false;
    int fare, totalFare ,discount, discountFare;
    do{
      
      int sum=0;
      bool found = false;
      fare = getperPersonPrice();
      totalFare = sum;

      int bookCode;

      cout << "Enter your booking code: ";
      cin >> bookCode;

      for (int i = 0; i < global_members; i++) {
        if (serialnum[i] == bookCode) {
          if (passenger_age[i]  > 0 && passenger_age[i] <= 6)
          {
            discount = getperPersonPrice() * 0.5; // 50% discount
            discountFare = getperPersonPrice() - discount;
            totalFare = discountFare;
            sum += discountFare; // Total fare
          }
          else if (passenger_age[i] > 6 && passenger_age[i]  <= 12)
          {
            discount = getperPersonPrice() * 0.3; // 30% discount
            discountFare = getperPersonPrice() - discount;
            totalFare = discountFare;
            sum += discountFare; // Total fare
          }
          else if (passenger_age[i]  >= 60)
          {
            discount = getperPersonPrice() * 0.2; // 20% discount
            discountFare = getperPersonPrice() - discount;
            totalFare = discountFare;
            sum += discountFare; // Total fare
          }
          else
          {
            fare = getperPersonPrice();
            totalFare = fare;
            sum += fare;
          }

          found = true;
        }
      }
      if (found = false)
      {
        cout << "Enter correct booking code" << endl;
      }
      else
      {
        totalFare = sum;
        cout << "Your Total Fare is: " << totalFare;
      }
      cout << "Enter 1 to continue, any other key to exit: ";
      string s;
      cin >> s;
      if (s.size() == 1 && s[0] == '1') {
          cont = true;
      } else {
          cont = false;
      }
   } while (cont);

	}

void modifyTicket()
{
  bool cont=false;
  do{
    int bookingcode;
  int serial;
  bool found = false;

  cout << "Enter your booking code: ";
  cin >> bookingcode;

  // cout << "\nEnter serial number to edit: S-";
  // cin >> serial;

  for (int i = 0; i < global_members; i++) {
    if (serialnum[i] == bookingcode) {
      int option;
      cout<<"What do you want to Change?: "<<endl;
      cout<<"Press 1- To Update name."<<endl;
      cout<<"Press 2- To Update age."<<endl;

      cout<<"Press 3- To Update gender."<<endl;
      cin>>option;
      switch (option)
      {
      case 1:
        cout << "Enter passenger name: ";
        cin >> passenger_name[i];
        break;
      case 2:
        cout << "Enter passenger age: ";
        cin >> passenger_age[i];
        break;
      case 3:
        cout << "Enter gender: ";
        cin >> passenger_gender[i];
        break;
      
      default:
        break;
      }
;
      found = true;
      cout << endl;
      break;
    }
  }
  if (!found)
  {
    cout << "Record not Found" << endl;
  }
  cout << "Enter 1 to continue, any other key to exit: ";
      string s;
      cin >> s;
      if (s.size() == 1 && s[0] == '1') {
          cont = true;
      } else {
          cont = false;
      }
   } while (cont);
}

void confirmPayment(){
		bool cont=false;
    do{
      int bookingcode, userInput;
      string cnic;
      bool found = false;

      cout << "Enter your booking code: ";
      cin >> bookingcode;

      cout << "\nEnter CNIC number of booking of 1st person(with dashes): ";
      cin >> cnic;

      for (int i = 0; i < global_members; i++) {
        if (serialnum[i] == bookingcode && cnic== passenger_CNIC[i]) {
          found = true;
          break;
        }
        if (found){
          cout << "\nYour Total Fare is: " << ticket_fare[i] << endl;
          cout << "\nPay fare amount to confirm ticket: ";
          cin >> userInput;
          if (userInput == ticket_fare[i]){
            cout << "\nYour booking is confirmed, enjoy your trip!!!";
          }
          else{
            cout << "\nPlease pay the required amount" << endl;
            cout << "\nPay fare amount to confirm ticket: ";
            cin >> userInput;
            if (userInput == ticket_fare[i]){
              cout << "\nYour booking is confirmed, enjoy your trip!!!";
            }
            else{
              cout << "\nYour Booking is cancelled, book again." << endl;
            }
          }
        }
        else{
          cout << "\nBookings not found, book your ticket first" << endl;
        }
        
	    }
      cout << "Enter 1 to continue, any other key to exit: ";
      string s;
      cin >> s;
      if (s.size() == 1 && s[0] == '1') {
          cont = true;
      } else {
          cont = false;
      }
   } while (cont);
}