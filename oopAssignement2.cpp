#include <iostream>
using namespace std;

class HVehicle { //abstract class
   public:
   	
    // Every vehicle must be able to display itself
    virtual void displayDetails() const = 0;
 
    // Every vehicle  can  calculate its depreciated value
    virtual double depreciation(int currentYear) const = 0;
 
    // Every vehicle must provide a short type label e.g. "Car", "Bike"
    virtual std::string getVehicleType() const = 0;
    
    //every vehicle can be checked if it meets the criteria of the user
    virtual bool isSuitable(int year, double limitPrice) const = 0;
 
};
class HUser {  //abstract class
  public:
    // Every user must be able to log in
    virtual bool LogIn(string email, string password) = 0;

    // Every user must be able to log out
    virtual void logOut() = 0;

    // Every user must expose their role label
    virtual string getRole() const = 0;

    // Every user must display their profile
    virtual void displayDetails() const = 0;

};
class HPayable { //abstract class
  public:
    // Must attempt to process the payment; return true on success
    virtual bool processPayment() = 0;
 
 
    // Must support refunds
    virtual void refund() = 0;
 
    // Must report current payment status
    virtual string getStatus() const = 0;
 
    // Must display full payment details
    virtual void displayDetails() const = 0;
 
     
};
class HReportable { //abstract class
public:
    // Must generate and print a full summary report
    virtual void generateReport() = 0;
 

    // Must return total count of items it tracks
    virtual int getTotalCount() const = 0;
 
};
class Vehicle : public HVehicle {
	protected:
		const int vehicleID;
		string company;
		string model;
		int manufactureYear;
		double price;
		int mileage;
		
		public:
			
		
			
			int getYear() const {
				return manufactureYear;
			}
		
			double getPrice() const {
				return price;
			}
			int getID() const {
				return vehicleID;
			}
			
			Vehicle():vehicleID(0){
				//default
			}
			Vehicle(int vID , string c, string m, int year, double p, int mile):vehicleID(vID), 
			company(c), model(m), manufactureYear(year), price(p), mileage(mile){}  //parametrized
			
			Vehicle& operator=(const Vehicle& v) {  //we use operator overloading since we have a constant member
				if(this != &v) {                              //and later we have aggregation/compsotion relations
					this->~Vehicle();
					new (this) Vehicle(v);
				}
				return *this;
            }
            
			void priceUpdate(double Price){
				price = Price;
			}
			void alterYear(int Year){
				manufactureYear = Year;
			}
			
			bool match(string C, string M, int Y, double MaxP, double MinP, int MaxM, int MinM){
				if((C==company) && (M==model) && (Y==manufactureYear) 
				&& price>MinP && price<MaxP && mileage>MinM && mileage<MaxM){
					return true;
				}
				else{
					return false;
				}
			}
			
			bool operator >(Vehicle &v){
				return this->price > v.price;   //operator overloading returns true if v1 is greater 
			}
			
			bool operator ==(const Vehicle &v) const {  //operator overloading returns true if both vehicle ID's match
				return vehicleID == v.vehicleID;      //const since the vehicle id is constant
				//works similarily as the member function bool match
			}
			
			void displayDetails()const override {  // using abstract class
				cout<<"Vehicle ID: "<<vehicleID<<endl;
				cout<<"Comapny: "<<company<<endl;
				cout<<"Model: "<<model<<endl;
				cout<<"Manufacture date: "<<manufactureYear<<endl;
				cout<<"Price: "<<price<<endl;
				cout<<"Mileage: "<<mileage<<endl;
			}
			
			bool isSuitable(int year, double limitPrice) const override {
				if(manufactureYear == year && limitPrice == price){       
					return true;
				}
			}
			
			double depreciation(int currentYear) const override { 
				int age = currentYear - manufactureYear;
				if(age <= 0){
					return price;
				}
				else{
					double dep = price * (1.0-0.10*age);
					if(dep <= 0){
						return 0;
					}else{
						return dep;
					}
				}
			}
			
			string getVehicleType() const override {
				return "Vehicle";
			}
			
			friend void comparePrice(const Vehicle &v1, const Vehicle &v2);
			
};
void comparePrice(const Vehicle &v1, const Vehicle &v2){ //friend Function
    //compares vehicles by mileage
	cout<<"Mileage compariosion of vehicles"<<endl;
	cout<<"Vehcile number 1 "<<endl;
	v1.displayDetails();
	cout<<"Vehicle number 2 "<<endl;
	v2.displayDetails();
	if(v1.mileage > v2.mileage){
		cout<<"Vehicle one has driven more miles than vehicle two"<<endl;
	}else if(v2.mileage > v1.mileage){
		cout<<"Vehicle two has driven more miles than vehicle one"<<endl;
	}
	if(v1.mileage==0){
		cout<<"Vehicle number one is brand new"<<endl;
	}
	if(v2.mileage==0){
		cout<<"Vehicle number two is brand new"<<endl;
	}
}
class Car : public Vehicle{
	private:
		string fuelType;
		double engineCapacity;
		string color;
		string bodyType;
		bool hasSunroof;
		bool hasNavigation;
		
	public:
		Car(int vID , string c, string m, int year, double p, int mile, string fuel, double capacity, string col, 
		string type, bool sunroof, bool nav): Vehicle(vID,c,m,year,p,mile), fuelType(fuel), engineCapacity(capacity), color(col),
		bodyType(type), hasSunroof(sunroof), hasNavigation(nav){}
		
		void displayDetails() const override {  //override from class vehicle
			Vehicle::displayDetails();
			cout<<"Fuel Type: "<<fuelType<<endl;
			cout<<"Engine Capacity: "<<engineCapacity<<endl;
			cout<<"Color of the car: "<<color<<endl;
			cout<<"Type of body: "<<bodyType<<endl;
			if(hasSunroof){
				cout<<"Car has a sunroof"<<endl;
			}
			else{
				cout<<"Car does not have a sunroof"<<endl;
			}
			if(hasNavigation){
				cout<<"Car has navigation features"<<endl;
			}
			else{
				cout<<"Car does not have navigation features"<<endl;
			}
		}
		
		string getVehicleType() const override {
			return "Car";
		}
		
		bool SuitableForFamilty() const {
			if(bodyType == "sedan" || bodyType == "SUV"){
				return true;
			}
			else{
				return false;
			}
		}
		
		void ChangeColor(string Col){
			color = Col;
		}
		
		bool isPremium() const {
			if((hasSunroof && hasNavigation)==1){
				return true;
			}
			else{
				return false;
			}
		}
};
class ElectricCar: public Car{
	private:
		double BatteryCapacity;
		int ChargingTime;
		double BatteryHealth;
		bool isCharged;
		
	public:
		ElectricCar(int vID, string c, string m, int year, double p, int mile,
                string col, string type, bool sunroof, bool nav,
                double batCap, int chargeTime,
                double batHealth, bool charged):
				Car(vID, c, m, year, p, mile, "Electric", 0.0, col, type, sunroof, nav),
                BatteryCapacity(batCap), ChargingTime(chargeTime),
                BatteryHealth(batHealth), isCharged(charged) {}
                
                
              
				
                
                bool isFullyCharged() const {
                	return isCharged;
				}
				bool FastCharging(){
					if(ChargingTime < 45){  //45 mins
						return true;
					}else{
						return false;
					}	
				}
				void chargeBattery(){
					if(isCharged=true && BatteryHealth==100.0){
						cout<<"Battery is charged and in good health"<<endl;
					}
				}
				
				void displayDetails(){
					cout<<"-----Electric Car------"<<endl;
					cout<<"The total battery capacity of the electric car is: "<<BatteryCapacity<<endl;
					cout<<"The time required for charging is: "<<ChargingTime<<endl;
					cout<<"The battery health of this car is: "<<BatteryHealth<<endl;
					if(isCharged=true){
						cout<<"The car as of now is charged"<<endl;
					}else{
						cout<<"The car as of now is not charged"<<endl;
					}
				}
				
				double depreciation(int CurrentYear)const override{
					int age = CurrentYear - getYear();
					if(age<=0){
						return getPrice();
					}
					double dep = getPrice() * (1.0-0.10*age);
					if(dep <=0 ){
						return 0;
					}else{
						return dep;
					}
				}
				
				
                   
};
class Bike: public Vehicle{
	private:
		int EngineCapacity;
		string bikeType;
		int horsePower;
		int topSpeed;
		double weight;
		bool isModified;
		
	public:
		Bike(int vID, string c, string m, int year, double p, int mile,
		 int engCap, string type, int power, int maxSpeed, double w, bool modified):Vehicle(vID,c,m,year,p,mile), EngineCapacity(engCap), bikeType(type),
		 horsePower(power), topSpeed(maxSpeed), weight(w), isModified(modified){}
		 
		 
		 
		 void displayDetails() const override {
		 	cout<<"-----Bike-----"<<endl;
		 	cout<<"The engine capacity of this bike is: "<<EngineCapacity<<endl;
		 	cout<<"The type of this bike is: "<<bikeType<<endl;
		 	cout<<"Horse power: "<<horsePower<<endl;
		 	cout<<"Max speed: "<<topSpeed<<endl;
		 	cout<<"Weight: "<<weight<<endl;
		 	if(isModified==true){
		 		cout<<"The bike has been modified previously"<<endl;
			 }
		 }
		 string getVehicleType() const override {
		 	return "Bike";
		 }
		
		 bool isSports(){
		 	if(bikeType=="sports"){
		 		return true;
			 }
			 else{
			 	return false;
			 }
		 }
		 
		 bool isHighPerformance(){
		 	if(horsePower>200 && weight>150 && weight <200){
		 		return true;
			 }
			 else{
			 	return false;
			 }
		 }
		 
		 bool isBeginnerFriendly(){
		 	if(EngineCapacity <=150){
		 		return true;
			 }
			 else{
			 	return false;
			 }
		 }
		 
		bool Modified(){
			if(isModified){
				return true;
			}
			else{
				return false;
			}
		}
		
};
class SportsBike: public Bike{
	private:
		bool TurboEnabled;
		bool raceMode;
		double capacity;
		double trackRecord;
		bool additionalKit;
	public:
		SportsBike(int vID, string c, string m, int year, double p, int mile,
        int engCap, int power, int maxSpeed, double w, bool modified,
        bool turbo, bool race, double cap, double track, bool kit):
        Bike(vID, c, m, year, p, mile, engCap, "sports",
        power, maxSpeed, w, modified),
        TurboEnabled(turbo), raceMode(race), capacity(cap),
        trackRecord(track), additionalKit(kit) {}
        
        
        void activateTurbo(){
        	TurboEnabled = true;
        	cout<<"Turbo has been activated"<<endl;
		}
		void SwitchRaceMode(){
			if(raceMode==true){
				raceMode=false;
			}else if(raceMode==false){
				raceMode = true;
			}
		}
		
		void checkCapacity(){
			if(capacity<45 && capacity > 20){
				cout<<"Capacity is low"<<endl;
			}else if(capacity<=20){
				cout<<"Urgent"<<endl;
			}else if(capacity >= 45){
				cout<<"Good condition"<<endl;
			}
		}
		
		string getVehicleType() const override {
			return "Sports bike";
		}
               
               
               
};
class Users: public HUser{
	
	protected:
		const int UserID;
		string name;
		string email;
		string phoneNo;
		string passkey;
		string role;  // buyer/seller
		
	public:
		
		
		Users(): UserID(0), name(""), email(""), phoneNo(""), passkey(""), role(""){}
		
		Users(int ID, string n, string e, string phone, string pass, string r): UserID(ID), name(n), email(e),
		phoneNo(phone), passkey(pass), role(r){}
		
		Users(const Users& u):UserID(u.UserID), name(u.name), email(u.email) , phoneNo(u.phoneNo), 
		passkey(u.passkey), role(u.role){}
		
		
		
		bool operator ==(const Users &u) const{ //operator overloading
			return UserID == u.UserID;
		}

		friend void  CheckDuplicate(const Users &u1, const Users &u2);
		
		bool LogIn(string email, string password) override{
			if(this->email == email && password==passkey){
				cout<<"Log in was successfull"<<endl;
				return true;
			}else{
				cout<<"Incorrect credentials"<<endl;
				return false;
			}
		}
		
		string getRole() const override{
			return role;
		}
		
		void changePassword(string password){
			passkey = password;
			cout<<"Password was successfuly changed"<<endl;
		}
		string getName(){
			return name;
		}
		void logOut() override {
			cout<<"You are logged out"<<endl;
		}
		
		void displayDetails() const override{
			cout<<"User ID: "<<UserID<<endl;
			cout<<"Name: "<<name<<endl;
			cout<<"Email: "<<email<<endl;
			cout<<"Phone number: "<<phoneNo<<endl;
			cout<<"Role in the car market place (Buyer/Seller)"<<role<<endl;
		}
};
void CheckDuplicate(const Users &u1, const Users &u2){ //friend function
		if(u1== u2){    //using operator overloading in a function to check duplicate id's
			cout<<"Error detected, two users can not share same ID"<<endl;
		}
}
class Seller: public Users{
	private:
		int inventoryIDs[20];
		int totalInventory;
		double earning;
		double sellerRating;
		bool verified;
	public:
		Seller(): Users(), totalInventory(0), earning(0), sellerRating(0), verified(false){}  //default
		
		Seller(int ID, string n, string e, string num, string pass): Users(ID,n,e,num,pass,"Seller"), totalInventory(0), 
		earning(0), sellerRating(0), verified(false){}  //parametrized
		
		Seller(const Seller& s): Users(s), totalInventory(s.totalInventory), earning(s.earning), sellerRating(s.sellerRating), 
		verified(s.verified){
			for(int i =0; i<totalInventory; i++){
				inventoryIDs[i] = s.inventoryIDs[i]; //copy constructor
			}
		}
		
		string getSellername(){
			return name;
		}
		
		Seller& operator +=(const Seller &s){ //using operator overloading to add earnings
			earning += s.earning;
			return *this;   //returns reference to the object of Seller
		}
		
		void addInventory(int inventoryID){
			if(totalInventory<20){
				inventoryIDs[totalInventory++] = inventoryID;  //works as post increment
				cout<<"Inventory updated"<<endl;
			}
		}
		void deleteInventory(int inventoryID){
			for(int i=0; i<totalInventory; i++){
				if(inventoryIDs[i]==inventoryID){
					for(int j=i;j<totalInventory-1;j++){
						inventoryIDs[j] = inventoryIDs[j+1];
					}
					totalInventory--;
					cout<<"Inventory deleted"<<endl;
					break;
				}
			}
		}
		
		void addEarning(double amount){
			earning += amount;  //once order confirmed amount can be added
		}
		
		void displayDetails() const override {
			cout<<"Total inventory: "<<totalInventory<<endl;
			cout<<"Earning as of now: "<<earning<<endl;
			cout<<"Ratings of the seller: "<<sellerRating<<endl;
			cout<<"Is the seller verified? "<<verified<<endl;
		}
		
		friend void MergeEarnings(const Seller &s1, const Seller &s2);
};
void MergeEarnings(const Seller &s1, const Seller &s2){ //friend function
	cout<<"Combined earnings of two sellers is: "<<endl;
	cout<<s1.name<<" amount earned: "<<s1.earning<<endl;
	cout<<s2.name<<" amount earned: "<<s2.earning<<endl;
	cout<<"Total: "<<(s1.earning + s2.earning)<<endl;
}
class Buyer: public Users{
	private:
		int favInventory[30];
		int savedCount;
		double budget;
		string prefferedCompany;
		string prefferedType;  
	public:
		Buyer():Users(), savedCount(0), budget(0), prefferedCompany(""), prefferedType(""){}
		
		Buyer(int id, string n, string e, string num, string pass, double b, string comp, string type):Users(id,n,e,num,pass,"Buyer"), savedCount(0),
		budget(b), prefferedCompany(comp), prefferedType(type){}
		
		Buyer(const Buyer& b): Users(b), savedCount(b.savedCount), budget(b.budget), prefferedCompany(b.prefferedCompany),
		prefferedType(b.prefferedType){
			
			for(int i =0;i< savedCount;i++){
				favInventory[i] = b.favInventory[i];
			}
		}
		string getBuyername(){
			return name;
		}
		void SaveFav(int inventoryID){
			if(savedCount<30){
				favInventory[savedCount++] = inventoryID;
				cout<<"Inventory ID saved to favourites"<<endl;
			}
		}
		
		
		void removeFav(int inventoryID){
			for(int i=0; i<savedCount; i++){
				if(favInventory[i] == inventoryID){
					for(int j=i; j<savedCount-1; j++){
						favInventory[j] = favInventory[j+1];	
					}
					savedCount--;
					cout<<"Removed from favourites"<<endl;
					break;
				}
			}
		} 
		
		void viewFavourite() const {
			cout<<"View saved/Favourite list of vehicles";
			for(int i=0;i<savedCount;i++){
				cout<<favInventory[i] <<endl;
			}
		}
		friend void compareBudget(const Buyer& buyer, const Vehicle& vehicle);
		void sendMessage(Seller* seller, string message);
};
void compareBudget(const Buyer &buyer, const Vehicle &vehicle){
	cout<<"------Comparing budget-----"<<endl;
	cout<<"Buyer: "<<buyer.name << endl;
	cout<<"Budget: "<< buyer.budget<<endl;
	cout<<"Vehicle price: "<<vehicle.getPrice()<<endl;
	
	if(buyer.budget > vehicle.getPrice()){
		cout<<"Buyer can afford this vehicle"<<endl;
	}else{
		cout<<"Buyer can not afford this vehicle"<<endl;
	}
}
void Buyer::sendMessage(Seller* seller, string message) {
    cout << "Message sent to Seller: " << message << endl;
}
class PremiumBuyer: public Buyer{
	private:
		string memberShipStatus;
		int loyaltyPoints;
		double discountRate;
		string premiumSince;
		int count;
		
	public:
		PremiumBuyer(int id, string n, string e, string num, string pass,
        double b, string comp, string type,
        string status, int pts, double disc, string since, int c):
        Buyer(id, n, e, num, pass, b, comp, type),
        memberShipStatus(status), loyaltyPoints(pts), discountRate(disc),
        premiumSince(since), count(c) {}
        
        void upgradeTier(){
        	if(memberShipStatus == "Silver"){
        		memberShipStatus = "Gold";
			}else if(memberShipStatus == "Gold"){
				memberShipStatus = "Plarinum";
			}else if(memberShipStatus == "Platinum"){
				cout<<"You already have Platinum status"<<endl;
			}
		}
		
		void redeemPoints(int points){
			if(points<= loyaltyPoints){
				loyaltyPoints -= points;
				cout<<"Points have been redeemed. Remaining points are: "<<loyaltyPoints<<endl;
			}else{
				cout<<"You do not have enough points"<<endl;
			}
		}
		
		double getDiscount(double orignal){
			double saving =  orignal*(discountRate/100);
			return orignal - saving;
		}
		
		void displayDetails()const override {
			Buyer::displayDetails();
			cout<<"Member Ship status: "<<memberShipStatus<<endl;
			cout<<"Loyalty points: "<<loyaltyPoints<<endl;
			cout<<"Discount rate based on membership status: "<<discountRate<<endl;
			cout<<"Have been a premium buyer since: "<<premiumSince<<endl;
			cout<<"Total number of vehicles purchased: "<<count<<endl;
		}
		
		string getRole()const override {
			return "Premium Buyer";
		}
		
        
};
class Inventory{
	private:
		const int Inventoryid;
		Vehicle *vehicle; 
		Seller *seller;  //aggregation
		string status;   //available/sold
		string city;
		int views;
		
	public:
		Inventory(): Inventoryid(0),seller(NULL), status("Available"), city(""), views(0){
			vehicle = NULL;
		}
		
		Inventory(int id, const Vehicle &v, Seller* s,string stat, string location): Inventoryid(id), seller(s),
		status(stat), city(location), views(0){
			vehicle = new Vehicle(v);
		}
		
		Inventory& operator=(const Inventory& i) {
			if(this != &i){
				delete vehicle;
				this->~Inventory();
				new (this) Inventory(i);
			}
			return *this;
	   }
  
		Inventory(const Inventory& i): Inventoryid(i.Inventoryid)
		, seller(i.seller), status(i.status), city(i.city), views(i.views){
			vehicle = new Vehicle(*i.vehicle);
		}
		
		int getInventoryID() const {
			return Inventoryid;
		}
		 
		Vehicle& getVehicle() { return *vehicle; }
        const Vehicle& getVehicle() const { return *vehicle; }
        
		void publish() {
			status = "Available";
			cout<<"Inventory is available"<<endl;
		}
		
		void markAsSold(){
			status = "Sold";
			cout<<"Inventory is now sold"<<endl;
		} 
		void  incrementViews(){
			views++;
		}
		
		void changeLocation(string location){
			city = location;
			
		}
		
		~Inventory(){
			delete vehicle;
		}
 		
};
class Admin: public Users ,public HReportable{
	private:
		int approvedInventory;
		int removedInventory;
		int adminLevel;
		string department;
		bool premiumAuthority;
		
	public:
		Admin(): Users(), approvedInventory(0), removedInventory(0), adminLevel(1), department("Inventory"), premiumAuthority(false){}
		
		Admin(int ID, string n, string e, string num, string pass, int level, string d="Inventory", bool authority= false): Users(ID,n,e,num,pass,"Admin"),
		approvedInventory(0), removedInventory(0), adminLevel(level), department(d), premiumAuthority(authority){}
		
		void removeInventory(Inventory &i){
			i.markAsSold();
			removedInventory++;
			cout<<"Inventory successfully removed";
		}
		
		void approveInventory(Inventory &i){
			i.publish();
			approvedInventory++;
			cout<<"Inventory approved successfully";
		}
		
		void generateReport()  override{
			cout<<"Admin report"<<endl;
			cout<<"Department: "<<department<<endl;
			cout<<"Level of authority: "<<adminLevel<<endl;
			cout<<"Does admin have premium authority? "<<premiumAuthority<<endl;
			cout<<"Number of vehicles approved: "<<approvedInventory<<endl;
			cout<<"Number of vehicles removed: "<<removedInventory<<endl;
		}
		
		void displayDetails() const override {
			Users::displayDetails();
			cout<<"Department: "<<department<<endl;
			cout<<"Level of authority: "<<adminLevel<<endl;
			cout<<"Does admin have premium authority? "<<premiumAuthority<<endl;
			cout<<"Number of vehicles approved: "<<approvedInventory<<endl;
			cout<<"Number of vehicles removed: "<<removedInventory<<endl;
		}
		
		int getTotalCount(){
			return approvedInventory + removedInventory;
		}
		int getAdminLevel() const {
			return adminLevel;
		}
		string getDepartment() const {
			return department;
		}
		
	
};
class Payment : public HPayable{
	protected:
		const int paymentID;
		double amount;
		string status;
		string paymentDate;
		string transactionRef;
	public:
		
		 Payment():paymentID(0), amount(0), status("Pending"),
         paymentDate(""), transactionRef("") {}
 
         Payment(int id, double amt, string date, string ref):paymentID(id), amount(amt), 
		 status("Pending"),paymentDate(date), transactionRef(ref) {}
 
         Payment(const Payment& p):paymentID(p.paymentID), amount(p.amount), status(p.status),
         paymentDate(p.paymentDate), transactionRef(p.transactionRef) {}
         
         bool operator== (const Payment& p) const {
         	return transactionRef == p.transactionRef;
		 } //two payments are equal if the transaction reference is same for both
		 
		 friend void printPaymentSummary(const Payment &p1, const Payment &p2);
		 
		 bool processPayment() override {
		 	status = "Completed";
		 	cout<<"Payment: "<<amount<<" processed"<<endl;
		 	return true;
		 }
		 
		 void refund(){
		 	status = "Refunded";
		 	cout<<"Payment "<< paymentID<<" refunded"<<endl;
		 }
		 
		 void displayDetails() const override {
		 	cout<<"Payment Id: "<<paymentID<<endl;
		 	cout<<"AMount: "<<amount<<endl;
		 	cout<<"Status: "<<status<<endl;
		 	cout<<"Date of payment: "<<paymentDate<<endl;
		 	cout<<"Transaction reference: "<<transactionRef<<endl;
		 }
		 
		 string getStatus()const override {
		 	return status;
		 }
		 
		 double getAmount(){
		 	return amount;
		 }
		 int getPaymentID() const {
		 	return paymentID;
		 }
		 string getTransactionRef(){
		 	return transactionRef;
		 }	
};
void printPaymentSummary(const Payment &p1, const Payment &p2){ //friend function
	cout<<"---Payment Summary---"<<endl;
	cout<<"Payment 1: "<<endl;
	p1.displayDetails();
	cout<<"Payment 2: "<<endl;
	p2.displayDetails();
	cout<<"Total: "<< (p1.amount+p2.amount)<<endl;
}
class CashPayment: public Payment{
	private:
		double cashReceived;
		double changeReturned;
		string verifiedBy;
		string receiptNumber;
		
	public:
		CashPayment(int id, double amt, string date, string ref, double received, 
		string verifier,string receipt, string denom): Payment(id, amt, date, ref),
        cashReceived(received), verifiedBy(verifier),
        receiptNumber(receipt){
        changeReturned = cashReceived - amount;
        }
        
        
        
        double calculateChange(){
        	return cashReceived - amount;
		}
		
		bool processPayment() override{
			changeReturned = calculateChange();
			status = "completed";
			cout<<"Cash payment successful"<<endl;
			return true;
		} //simply confirms payment
        
        void refund() override{
        	status = "Refunded";
        	cout<<"Cash returned"<<endl;
		}
		
		void issueReceipt(){
			cout<<"Reciept: "<<receiptNumber<< "Verified by: "<<verifiedBy<<endl;
		}
		
};
class OnlinePayment: public Payment{
	private:
		string bankName;
		string accountNumber;
		string gateway;
		bool isEncrypted;
		string otp;
	public:
		OnlinePayment(int id, double amt, string date, string ref,string bank, 
		string accNum, bool encrypted,string gw, string otpCode) : Payment(id, amt, date, ref),
        bankName(bank), accountNumber(accNum), isEncrypted(encrypted),
        gateway(gw), otp(otpCode) {}
        
        bool verifyGateway(){
        	bool verified = (gateway=="Stripe" || gateway =="PayFast" || gateway== "JazzCash");
        	cout<<"Gateway used: "<<gateway<<endl;
			if(verified==false){
			   cout<<"UnKown"<<endl; 
			} 
		}
		void encryptTransaction(){
			isEncrypted = true;
			cout<<"Transaction is encrypted"<<endl;
		}
		
		void refund() override {
			status = "Refunded";
			cout<<"Onliner payment refunded"<<endl;
		}
		
		bool processPayment(){
			encryptTransaction();
			status = "Completed";
			cout<<"Online payment via "<<gateway<< "completed successfully"<<endl;
			return true;
		}
		
		void displayDetails() const override {
			Payment::displayDetails();
			cout<<"Name of the bank: "<<bankName<<endl;
			cout<<"Account number: "<<accountNumber<<endl;
			cout<<"Is the transaction encrypted ? "<<endl;
			if(isEncrypted==true){
				cout<<"Yes"<<endl;
			}else{
				cout<<"No"<<endl;
			}
			cout<<"Gateway: "<<gateway<<endl;
			
		}
		
};
class Order{
	private:
		const int orderID;
	    Inventory vehicle;
	    Buyer *buyer;
	    Seller *seller;
	    double amount;
	    string status;
	    string orderDate;
	    string deliveryDate;
	    
	public:
		Order(): orderID(0){}  //default constructor is needed for const members
		Order(int id, const Inventory& inv, Buyer *b, Seller *s, double amt, string orderD, string deliveryD): orderID(id),
		vehicle(inv), buyer(b), seller(s), amount(amt), status("Pending"), orderDate(orderD), deliveryDate(deliveryD){}
		 
		Order(const Order& o):orderID(o.orderID), vehicle(o.vehicle), buyer(o.buyer), seller(o.seller),//copy constructor
		amount(o.amount), status(o.status), orderDate(o.orderDate), deliveryDate(o.deliveryDate){} //so all addresses are coppied adaquetly
		
		Order& operator=(const Order& o) {
			if(this != &o){
				this->~Order();
				new (this) Order(o);
			}
			return *this;
	   }
	
		void confirmOrder(){
			status = "Confirmed";
			if(seller) seller->addEarning(amount);
			cout<<"Order confirmed"<<endl; 
		}
		void delivered(){
			status = "Delivered";
			vehicle.markAsSold();
			cout<<"Order delivered"<<endl;
		}
		
		void displayOrder() const {
			cout<<"Order ID: "<<orderID<<endl;
			cout<<"Buyer: ";
			if(buyer != NULL){
				cout<<buyer->getBuyername()<<endl;
			}
			else{
				cout<<"UnKnown"<<endl;
			}
			if(seller != NULL){
				cout<<seller->getSellername()<<endl;
			}
			else{
				cout<<"UnKown"<<endl;
			}
			cout << "Amount: " << amount << endl;
			cout<<"Status: "<< status<<endl;
			cout<<"Order date: "<<orderDate<<endl;
			cout<<"Delivery date"<<deliveryDate<<endl;			
		}
		
		string getStatus() const { return status; }
        int getOrderID() const { return orderID; }
};
class StoreFront: public HReportable{
	private:
		Inventory inventories[100];
		Order orders[100];
		int totalInventories;
		int totalOrders;
		string storeName;
		
		
	public:
		StoreFront(): totalInventories(0), totalOrders(0), storeName("AutoHub"){}
		
		
		void addInventory(const Inventory &i){
			if(totalInventories<100){
				inventories[totalInventories++] = i;
				cout<<"Inventory added to store front"<<endl;
			}
		}
		void deleteInventory(int inventoryID){
			bool found = false;
			for(int i=0; i <totalInventories; i++){
				if(inventories[i].getInventoryID() == inventoryID){
					for(int j=i; j < totalInventories-1;j++){
						inventories[j]= inventories[j+1];
					}
					totalInventories--;
					cout<<"Inventory deleted"<<endl;
					found = true;
					break;
				}
			}
			if(!found){
				cout<<"Inventory not found"<<endl;
			}
		}
		
		//Search by either categories from the class vehicle 
		//for example search by year
		
		void searchByYear(int year) const {
			bool found = false;
			for(int i=0;i<totalInventories;i++){
				if(inventories[i].getVehicle().getYear()==year){
					found = true;
				}
			}
			if (found){
				cout<<"Vehicle found"<<endl;
			}
			else{
				cout<<"Vehicle was not found"<<endl;
			}
		}
		
		void addOrder(const Order &o){
			if(totalOrders<100){
				orders[totalOrders++] = o;
				cout<<"Order "<<o.getOrderID()<<" added"<<endl;
			}
		}
		void displayAllOrders() const {
            for(int i=0; i<totalOrders; i++) {
               orders[i].displayOrder();
            }
       }
       //HReportable abstract class
       void generateReport(){
       	cout<<"---Store front Report---"<<endl;
       	cout<<storeName<<endl;
       	cout<<"Total inventories at this moment: "<<totalInventories<<endl;
       	cout<<"Total number of orders: "<<totalOrders;
	   }
	   
	
};		


int main(){
	
}

int main(){
	
	
	
	return 0;
}

