// Shipping calculator
// Prompt user for:
//      - item name
//      - is fragile? + 2.00
//      - order total w/out shipping
//      - destination (USA, Canada, Australia)
// We will use a multi-alternative if statement to determine shipping cost based on Order cost and country
// We will then print out the information to the console and write it to a file.
//

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <list>
#include <algorithm> // use this to use transform



int main()
{
    // shipping variables
    // I may have gone overboard on constants, but shipping prices change frequently
    // it would be annoying to go through and change each one
    string itemName;
    string answer;
    string dest;
    int fWeight;
    float fLength;
    float fWidth;
    float fHeight;
    float fVolume;
    float fDensity;
    float fClass; 
    float OrderTotal;
    float ShippingCost;
    float TotalCost;
    const float FRAGILE = 2.00;
    const float USA1 = 6.00;
    const float USA2 = 9.00;
    const float USA3 = 12.00;
    const float CAN1 = 8.00;
    const float CAN2 = 12.00;
    const float CAN3 = 15.00;
    const float AUS1 = 10.00;
    const float AUS2 = 14.00;
    const float AUS3 = 17.00;


    //string variables
    //if we store the questions and outputs as constants, we can easily subtract string length to line stuff up
    const int WIDTH = (70);
    const string Q1 = "Please enter the item name (no spaces)";
    const string Q2 = "Is the item fragile? (y=yes/n=no)";
    const string Q3 = "Please enter your order total";
    const string Q4 = "Please enter destination (USA, CAN, AUS)";
    const string Q5 = "Please enter the weight of your shipment";
    const string Q6 = "Please enter the length of your shipment";
    const string Q7 = "Please enter the width of your shipment";
    const string Q8 = "Please enter the height of your shipment";
    const string OP1 = "Your item is";
    const string OP2 = "Your shipping cost is";
    const string OP3 = "You are shipping to";
    const string OP4 = "Your total shipping costs are";
    const string OP5 = "Thank you!";
    const string OP6 = "The weight of your shipment is: ";
    const string OP7 = "The dimensions of your shipment are: ";
    const string OP8 = "The freight class of your shipment is: ";



    //file variable
    ofstream outFile;

    //open the file and verify it opens. Program will exit if file did not open
    outFile.open("Order.txt");
    if (outFile.fail())
    {
        return 0;
    }

    cout << right << setw(WIDTH) << setfill('.') << "." << endl;
    cout << "ITCS 2530 - Programming Assignment for week # 3" << endl;
    cout << setfill('.') << setw(WIDTH) << ' ' << endl;

    cout << endl;
    cout << Q1 << setw(WIDTH - Q1.length()) << ":";
    cin >> itemName;
    transform(itemName.begin(), itemName.end(), itemName.begin(), toupper);


    cout << Q2 << setw(WIDTH - Q2.length()) << ":";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), tolower);
    if (answer != "y" && answer != "n")
    {
        cout << "Invalid entry, exiting" << endl;
        system("pause");
        return 0;
    }

    cout << Q3 << setw(WIDTH - Q3.length()) << ":";
    cin >> OrderTotal;


    cout << Q4 << setw(WIDTH - Q4.length()) << ":";
    cin >> dest;
    transform(dest.begin(), dest.end(), dest.begin(), toupper);
    if (dest != "USA" && dest != "CAN" && dest != "AUS")
    {
        cout << "Invalid entry, exiting" << endl;
        system("pause");
        return 0;
    }

    cout << Q5 << setw(WIDTH - Q5.length()) << ":";
    cin >> fWeight;

    cout << Q6 << setw(WIDTH - Q6.length()) << ":";
    cin >> fLength;

    cout << Q7 << setw(WIDTH - Q7.length()) << ":";
    cin >> fWidth;

    cout << Q8 << setw(WIDTH - Q8.length()) << ":";
    cin >> fHeight;


    // here we will calculate the freight density, which will determine the freight class.
    // freight class determines carrier liability and usually price 
    // I will probably upate the pricing in a future version of this program, but for now I just want
    // to add the freight class
    fVolume = (fLength * fWidth * fHeight) / 1728;
    fDensity = fWeight / fVolume;

    if (fDensity < 1)
        fClass = 500;
    else if (fDensity >= 1 && fDensity <= 2)
        fClass = 400;
    else if (fDensity > 2 && fDensity <= 3)
        fClass = 300;
    else if (fDensity > 3 && fDensity <= 4)
        fClass = 250;
    else if (fDensity > 4 && fDensity <= 5)
        fClass = 200;
    else if (fDensity > 5 && fDensity <= 6)
        fClass = 175;
    else if (fDensity > 6 && fDensity <= 7)
        fClass = 150;
    else if (fDensity > 7 && fDensity <= 8)
        fClass = 125;
    else if (fDensity > 8 && fDensity <= 9)
        fClass = 110;
    else if (fDensity > 9 && fDensity <= 10.5)
        fClass = 100;
    else if (fDensity > 10.5 && fDensity <= 12)
        fClass = 92.5;
    else if (fDensity > 12 && fDensity <= 13.5)
        fClass = 85;
    else if (fDensity > 13.5 && fDensity <= 15)
        fClass = 77.5;
    else if (fDensity > 15 && fDensity <= 22.5)
        fClass = 70;
    else if (fDensity > 22.5 && fDensity <= 30)
        fClass = 65;
    else if (fDensity > 30 && fDensity <= 35)
        fClass = 60;
    else if (fDensity > 35 && fDensity <= 50)
        fClass = 55;
    else
        fClass = 50;

    

    // here is our nested multi-alternative if statement to determine shipping costs.
    // our first condition is order total - is it below or = to 50, between  50.01 and 100, above 100.01 and under or = to 150, or is it over 150?
    //      - depending on where our order total falls, we then determine shipping cost based on country
    if (OrderTotal <= 50.00)
    {
        if (dest == "USA")
            ShippingCost = USA1;
        else if (dest == "CAN")
            ShippingCost = CAN1;
        else
            ShippingCost = AUS1;
    }
    else if (OrderTotal > 50.01 && OrderTotal <= 100.00)
    {
        if (dest == "USA")
            ShippingCost = USA2;
        else if (dest == "CAN")
            ShippingCost = CAN2;
        else
            ShippingCost = AUS2;
    }
    else if (OrderTotal > 100.01 && OrderTotal <= 150.00)
    {
        if (dest == "USA")
            ShippingCost = USA3;
        else if (dest == "CAN")
            ShippingCost = CAN3;
        else
            ShippingCost = AUS3;

    }
    else
        ShippingCost = 0.00;

    //this is to add 2 dollars if shipment is fragile
    if (answer == "y")
    {
        ShippingCost = ShippingCost + FRAGILE;
    }

    TotalCost = ShippingCost + OrderTotal;

    cout << endl;
    //here is where we begin the output on the screen
    // and also write to our file
    // to make it line up properly I had to manually add some spaces seen as "1+ WIDTH or 3 + WIDTH"
    // also since the cout and outFile are essentially the same, I like to group them together when possible



    cout << OP1 << setw(WIDTH - OP1.length() ) << itemName << endl;
    outFile << OP1 << setw(WIDTH - OP1.length()) << itemName << endl;

    cout << OP6 << setw(3 + WIDTH - OP6.length() - itemName.length()) << fWeight << endl;
    outFile << OP6 << setw(3 + WIDTH - OP6.length() - itemName.length()) << fWeight << endl;

    cout << OP7 << setw(2 + WIDTH - OP7.length() - itemName.length()) << fLength << "x" << fWidth << "x" << fHeight << endl;
    outFile << OP7 << setw(2 + WIDTH - OP7.length() - itemName.length()) << fLength << "x" << fWidth << "x" << fHeight << endl;

    cout << OP8 << setw(6 + WIDTH - OP8.length() - itemName.length()) << "CLASS "<< fClass << endl;
    outFile << OP8 << setw(6 + WIDTH - OP8.length() - itemName.length()) << "CLASS " << fClass << endl;

    cout << OP2 << setw(1 + WIDTH - OP2.length() - itemName.length()) << "$" << fixed << setprecision(2) << ShippingCost << endl;
    outFile << OP2 << setw(1 + WIDTH - OP2.length() - itemName.length()) << "$" << fixed << setprecision(2) << ShippingCost << endl;

    cout << OP3 << setw(3 + WIDTH - OP3.length() - itemName.length()) << dest << endl;
    outFile << OP3 << setw(3 + WIDTH - OP3.length() - itemName.length()) << dest << endl;

    cout << OP4 << setw(1 + WIDTH - OP4.length() - itemName.length()) << "$" << fixed << setprecision(2) << TotalCost << endl;
    outFile << OP4 << setw(1 + WIDTH - OP4.length() - itemName.length()) << "$" << fixed << setprecision(2) << TotalCost << endl;

    cout << "\n";

    cout << setfill('-') << setw(WIDTH) << OP5 << endl;
    outFile << setfill('-') << setw(WIDTH) << OP5 << endl;


    //close our file
    outFile.close();

    return 0;


}

