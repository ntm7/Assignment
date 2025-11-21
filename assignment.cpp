#include<iostream>
using namespace std;

class Ticket
{
protected:
    string ticketID,source,destination;
    float distance;

public:
    void setTicketInfo()
    {
        cin>>ticketID>>source>>destination>>distance;
    }
    void displayTicketInfo()
    {
        cout<<ticketID<<" "<<source<<" "<<destination<<" "<<distance<<endl;
    }
    float calculateFare()
    {
       return distance*1.0;
    }
};

class TrainTicket:private Ticket
{
public:
    string coachType;

    void input()
    {
        setTicketInfo();
        cin>>coachType;

    }
    float calculateFare()
    {
      float Base_fare=distance*1.0;

       if(coachType=="AC")
       {
           return Base_fare=Base_fare+200;
       }
       else if(coachType=="Sleeper")
       {
           return Base_fare=Base_fare+100;
       }
       else if(coachType=="general")
       {
           return Base_fare=Base_fare+0;
       }

    }
    void displayTrainTicket()
    {
      displayTicketInfo();
      cout<<"total fare: "<<calculateFare()<<endl;
    }
};

class FlightTicket: protected Ticket
{
public:
    string seatClass;
    float luggageWeight;
    void input2()
    {
        setTicketInfo();
        cin>>seatClass>>luggageWeight;
    }

    float calculateFare()
{
    float Base_fare = distance * 25.0;

    if(seatClass == "Business")
    {
        Base_fare=Base_fare + 20000;
    }

    if(luggageWeight > 20)
    {
        float extra = luggageWeight - 20;
        Base_fare=Base_fare +(extra * 5000);
    }

    return Base_fare;
}

    void displayFlightTicket()
    {
      displayTicketInfo();
      cout<<"total fare: "<<calculateFare()<<endl;
    }

};

int main()
{
    TrainTicket t;
    t.input();
    t.calculateFare();
    t.displayTrainTicket();

    FlightTicket f;
    f.input2();
    f.calculateFare();
    f.displayFlightTicket();
}

