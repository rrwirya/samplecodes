#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"

using namespace std;

class Passenger{
	public:
		int assignedrow;
		char assignedseat;
};

class Row{
	public:
		void RowNum(int num){					
			number = num;
		}

		void rowcondition(string row_state){
			cond = row_state;
		}
		
		void insertppl(Passenger a){
			person = a;
		}

		void deleteppl(){
			Passenger temp;
			person = temp;
		}
		
		int getrow(){
			return number;
		}
		
		string getstatus(){
			return cond;
		}
		
		Passenger getpassenger(){
			return person;
		}
		
		// previously seated passengers
		StackAr <char> ACseats = StackAr<char>(3);
		StackAr <char> DFseats = StackAr<char>(3);
		// passengers in aisle -> for moving passengers into aisle when someone wants to get inside 
		StackAr <char> aisle = StackAr<char>(2);
		
	private:
		string cond;
		int number;
		Passenger person;
};

template<typename T>
void printpassengers(Queue<T> passqueue){
	while(!passqueue.isEmpty()){
		T peeps = passqueue.dequeue();
		cout << peeps.assignedrow << peeps.assignedseat << endl;
	}
}

void emptystack(StackAr<char> stack){
	if(stack.isEmpty()){
		cout << "STACK IS EMPTY" << endl;
	}
	else{
		cout << "STACK IS NOT EMPTY" << endl;
	}
}

void rowloss(Queue<Row> queuerow){
	int i = 0;
	while(!queuerow.isEmpty()){
		queuerow.dequeue();
		i++;
	}
	if(i==48){
		cout << "All rows accounted for" << endl;
	}
	else{
		cout<<"Rows missing"<<endl;
	}
}

Queue<Row> shufflerow(Queue <Row> classrow){
	Row toprow = classrow.getFront();
	while(toprow.getrow()!=48){
		classrow.enqueue(classrow.dequeue());
		toprow = classrow.getFront();
	}
	return classrow;
}

void printrows(Queue<Row> someq){
	someq = shufflerow(someq);
	for(int i=0;i<=47;i++){
		Row somerow = someq.dequeue();
		cout << "Row " << somerow.getrow() << " has condition: " << somerow.getstatus() << endl;
	}
}

Queue<Row> reshufflecertainrow(Queue<Row> source, int wantednumber){
	Row refrow = source.getFront();
	while(refrow.getrow()!=wantednumber){
		source.enqueue(source.dequeue());
		refrow = source.getFront();
	}
	return source;
}

Queue<Row> movepassengers2(Queue<Row> source, int wantednumber){

	Row refrow = source.getFront();
	int toprownum = refrow.getrow();
	
	source = reshufflecertainrow(source,wantednumber+1);
	
	Row toprow = source.dequeue();
	Row nextrow = source.dequeue();

	if((toprow.getstatus()=="EMPTY")&&(nextrow.getstatus()=="WAITING")){
		toprow.insertppl(nextrow.getpassenger());
		// cout << toprow.getpassenger().assignedrow << toprow.getpassenger().assignedseat << " moved forward" << endl;
		toprow.rowcondition("WAITING");
		nextrow.rowcondition("EMPTY");
	}
	source.enqueue(toprow);
	source.enqueue(nextrow);
	
	Row comparator = source.getFront();
	
	while(comparator.getrow()!=toprownum){
		source.enqueue(source.dequeue());
		comparator = source.getFront();
	}
	
	return source;
}

// returns queue with 1st row in top
// works
Queue<Row> getfirstrow(Queue<Row>rq){
	Row toprow = rq.getFront();
	//cout << "Row " << toprow.getrow() << " status is: " << toprow.getstatus() << endl;
	while(toprow.getrow()!=1){
		
		rq.enqueue(rq.dequeue());
		toprow = rq.getFront();
		//cout << "Row " << toprow.getrow() << " status is: " << toprow.getstatus() << endl;
	}
	//cout << "firstrowstatus in getfirstrow = " << toprow.getstatus() << endl;
	return rq;
}

int lastiteration(Queue<Row> qr){
	int counter=0;
	for(int X=0; X<=47; X++){
		Row rowtobechecked = qr.dequeue();
		if(rowtobechecked.getstatus()=="EMPTY"){
			counter++;
		}
		qr.enqueue(rowtobechecked);
	}
	if(counter==48){
		return 1;
	}
	else{
		return 0;
	}
}

void boarding(Queue<Passenger> passengerlist){
	//Queue <Passenger> passengerlist = Queue<Passenger>(288);
	Queue <Row> rowqueue = Queue<Row>(48);
	
	int end = 0;
	
	for(int i=0; i<=47; i++){
		Row a;
		a.RowNum(48-i);
		a.rowcondition("EMPTY");
		if(i==47){
			a.insertppl(passengerlist.dequeue());
			//cout << "First Passenger: " << a.getpassenger().assignedrow << a.getpassenger().assignedseat << " at Row: " << a.getrow() << endl;
			/*if(a.getpassenger().assignedrow==1){
				a.rowcondition("WAITING");
			}*/
			a.rowcondition("WAITING");
		}
		rowqueue.enqueue(a);
	}
	int time = 5;
	Row currentrow;
	while(end!=1){
		for(int x=0; x<=47; x++){
			currentrow = rowqueue.dequeue();
			if((currentrow.getrow()==currentrow.getpassenger().assignedrow)&&(currentrow.getstatus()!="EMPTY")){
				if(currentrow.getstatus()=="AC_IN"){
					currentrow.ACseats.push(currentrow.aisle.topAndPop());
					if(!currentrow.aisle.isEmpty()){
						currentrow.rowcondition("AC_IN");
					}
					else{
						currentrow.rowcondition("EMPTY");
						if(currentrow.getrow()==1){
							currentrow.insertppl(passengerlist.dequeue());
							currentrow.rowcondition("WAITING");
						}
					}
				}
				else if(currentrow.getstatus()=="DF_IN"){
					currentrow.DFseats.push(currentrow.aisle.topAndPop());
					if(!currentrow.aisle.isEmpty()){
						currentrow.rowcondition("DF_IN");
					}
					else{
						currentrow.rowcondition("EMPTY");
						if(currentrow.getrow()==1){
							currentrow.insertppl(passengerlist.dequeue());
							currentrow.rowcondition("WAITING");
						}
					}
				}
				else if(currentrow.getstatus()=="AC_EMPTY"){
					currentrow.ACseats.push(currentrow.getpassenger().assignedseat);
					
					// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
					
					if(!currentrow.aisle.isEmpty()){
						currentrow.rowcondition("AC_IN");
					}
					else{
						currentrow.rowcondition("EMPTY");
					}
				}
				else if(currentrow.getstatus()=="DF_EMPTY"){
					currentrow.DFseats.push(currentrow.getpassenger().assignedseat);
					
					// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;	
					
					if(!currentrow.aisle.isEmpty()){
						currentrow.rowcondition("DF_IN");
					}
					else{
						currentrow.rowcondition("EMPTY");
					}
				}
				else if(currentrow.getstatus()=="AC_OUT"){
					currentrow.aisle.push(currentrow.ACseats.topAndPop());
					
					// cout << currentrow.getrow() << currentrow.aisle.top() << " now waiting in aisle" << endl;
					
					currentrow.rowcondition("AC_EMPTY");
				}
				else if(currentrow.getstatus()=="DF_OUT"){
					currentrow.aisle.push(currentrow.DFseats.topAndPop());
					
					// cout << currentrow.getrow() << currentrow.aisle.top() << " now waiting in aisle" << endl;
					
					currentrow.rowcondition("DF_EMPTY");
				}
				else if(currentrow.getstatus()=="STORING_LUGGAGE2"){
					if((currentrow.getpassenger().assignedseat=='A')||(currentrow.getpassenger().assignedseat=='B')||(currentrow.getpassenger().assignedseat=='C')){
						if(currentrow.ACseats.isEmpty()){
							currentrow.ACseats.push(currentrow.getpassenger().assignedseat);
							
							// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
							
							currentrow.rowcondition("EMPTY");
							if(currentrow.getrow()==1){
								currentrow.insertppl(passengerlist.dequeue());
								
								// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " entered plane" << endl;
								
								currentrow.rowcondition("WAITING");
							}
						}
						else{
							if(int(currentrow.ACseats.top())>int(currentrow.getpassenger().assignedseat)){
								currentrow.aisle.push(currentrow.ACseats.topAndPop());
								if(!currentrow.ACseats.isEmpty()){
									if(int(currentrow.ACseats.top())>int(currentrow.getpassenger().assignedseat)){
										currentrow.rowcondition("AC_OUT");
									}
									else{
										currentrow.rowcondition("AC_EMPTY");
									}
								}
								else{
									currentrow.rowcondition("AC_EMPTY");
								}
							}
							else{
								currentrow.ACseats.push(currentrow.getpassenger().assignedseat);
								
								// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
								
								currentrow.rowcondition("EMPTY");
								if(currentrow.getrow()==1){
									currentrow.insertppl(passengerlist.dequeue());
									
									// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " entered plane" << endl;
									
									currentrow.rowcondition("WAITING");
								}
							}
						}
					}
					else if((currentrow.getpassenger().assignedseat=='D')||(currentrow.getpassenger().assignedseat=='E')||(currentrow.getpassenger().assignedseat=='F')){
						if(currentrow.DFseats.isEmpty()){
							currentrow.DFseats.push(currentrow.getpassenger().assignedseat);
							
							// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
							
							currentrow.rowcondition("EMPTY");
							if(currentrow.getrow()==1){
								currentrow.insertppl(passengerlist.dequeue());
								
								// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " entered plane" << endl;
								
								currentrow.rowcondition("WAITING");
							}
						}
						else{
							if(int(currentrow.DFseats.top())<int(currentrow.getpassenger().assignedseat)){
								currentrow.aisle.push(currentrow.DFseats.topAndPop());
								if(!currentrow.DFseats.isEmpty()){
									if(int(currentrow.DFseats.top())<int(currentrow.getpassenger().assignedseat)){
										currentrow.rowcondition("DF_OUT");
									}
									else{
										currentrow.rowcondition("DF_EMPTY");
									}
								}
								else{
									currentrow.rowcondition("DF_EMPTY");
								}
							}
							else{
								currentrow.DFseats.push(currentrow.getpassenger().assignedseat);
								
								// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " has seated" << endl;
								
								currentrow.rowcondition("EMPTY");
								if(currentrow.getrow()==1){
									currentrow.insertppl(passengerlist.dequeue());
									
									// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " entered plane" << endl;
									
									currentrow.rowcondition("WAITING");
								}
							}
						}
					}
				}
				else if(currentrow.getstatus()=="STORING_LUGGAGE1"){
					currentrow.rowcondition("STORING_LUGGAGE2");
					
					// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " storing luggage (2)" << endl;
					
				}
				else{
					currentrow.rowcondition("STORING_LUGGAGE1");
					
					// cout << currentrow.getpassenger().assignedrow << currentrow.getpassenger().assignedseat << " storing luggage (1)" << endl;
					
				}
				
				rowqueue.enqueue(currentrow);
			}
			else{
				rowqueue.enqueue(currentrow);
				if(x!=0){
					rowqueue = movepassengers2(rowqueue,currentrow.getrow());
				}
				if(x==47){
					Row checkfirstrow = getfirstrow(rowqueue).getFront();
					if((checkfirstrow.getstatus()=="EMPTY")&&(!passengerlist.isEmpty())){
						rowqueue = getfirstrow(rowqueue);
						Row firstrow = rowqueue.dequeue();
						
						// cout << passengerlist.getFront().assignedrow << passengerlist.getFront().assignedseat << " entered plane" << endl;
						
						firstrow.insertppl(passengerlist.dequeue());
						firstrow.rowcondition("WAITING");
						rowqueue.enqueue(firstrow);
						rowqueue = shufflerow(rowqueue);
					}
					break;
				}
			}	
		}
		//cout << endl << endl;
		//printrows(rowqueue);
		time = time + 5;
		//cout << endl << endl;
		//cout << "time frame = " << time << endl << endl;
		end = lastiteration(rowqueue);
		/*if(time==180){
			end = 1;
		}*/
	
	}
	cout << time << endl;
}

int main(int argc, char** argv){
	
	Queue <Passenger> PassengerList1 = Queue<Passenger>(288);
	Queue <Passenger> PassengerList2 = Queue<Passenger>(288);
	Queue <Passenger> PassengerList3 = Queue<Passenger>(288);
	int rownum; char letters;

	ifstream txtfile(argv[1]);
	int i = 0;
	while(txtfile >> rownum >> letters){
		Passenger person;
		person.assignedrow = rownum;
		person.assignedseat= letters;
		PassengerList1.enqueue(person);
		i++;
		if(i==288){
			break;
		}
	}
	
	i = 0;
	while(txtfile >> rownum >> letters){
		Passenger person;
		person.assignedrow = rownum;
		person.assignedseat= letters;
		PassengerList2.enqueue(person);
		i++;
		if(i==288){
			break;
		}
	}
	i = 0;
	while(txtfile >> rownum >> letters){
		Passenger person;
		person.assignedrow = rownum;
		person.assignedseat= letters;
		PassengerList3.enqueue(person);
		i++;
		if(i==288){
			break;
		}
	}
	
	cout << "Back to front: ";
	boarding(PassengerList1);
	cout << "Random: ";
	boarding(PassengerList2);
	cout << "Outside in: ";
	boarding(PassengerList3);
	return 0;
}
