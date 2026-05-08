#include <iostream>
#include <fstream>
using namespace std;
//task four
class Product{
	public:
	
		string name;
		double price;
		int stock;
		
		Product(){
			name = " ";
			price = 0.00;
			stock = 0;
		}
		Product(string n, double p, int s): name(n), price(p), stock(s){}
		
		void addProduct(Product &p){
			ofstream out("Product.txt", ios::app);
			out << p.name<<" "<<p.price<<" "<<p.stock<<endl;
			out.close();
			cout<<"Item successfully added"<<endl;
		}
		
		void updateInventory(Product &p){
			Product temp[100];
			int count = 0;
			string pro;
			
			ifstream in("Product.txt");
			while(in>> temp[count].name >> temp[count].price >> temp[count].stock){
				count++;
			}
			in.close();
			
			cout<<"enter the product you want to search: "<<endl;
			cin>>pro;
			bool found = false;
			
			for(int i =0; i<count; i++){
				if(pro==temp[i].name){
					cout<<"Enter the changed value of price: "<<endl;
					cin>>temp[i].price;
					cout<<"Enter the changed value of the stock: "<<endl;
					cin>>temp[i].stock;
					found = true;
					break;
				}
			}
			if(found == false){
				cout<<"entry not found"<<endl;
			}
		}
};

int main(){
	Product p1("Wheat", 42.09, 2);
	p1.addProduct(p1);
	
	return 0;
}
