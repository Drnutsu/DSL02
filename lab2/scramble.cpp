#include <iostream>
#include <string>
#include "Linklist.h"

using namespace std;
int getNumberCut(string input,double percent){
	double answer = input.length() * (percent/100);
	double intPart;
	double factPart = modf(answer,&intPart); //modf will return int fraction and double fraction. 
	int intPartRaise = intPart;
	if(factPart >= 0.5){
		return ++intPartRaise;
	}else{
		return intPartRaise;
	}
}

int main(){
	Linklist<char> list;
	string line = "1234567890";
	for(int i =0;i < line.length();i++){
		list.insertData(line[i]);
	}

	/* ROTAGE */

	list.moveCursorToStart();
	int percent;
	cout << "fill encryption key: ";
	cin >> percent;
	int rotateNumber = getNumberCut(line,percent);
	cout << "Now, your line is : " << endl;
	list.print();
	cout << "and, rotate it like this : " << endl;
	list.rotate(rotateNumber);
	list.print();

	/* SHUFFLE */

	cout << "and, shuffle it on " ;
	cin >> percent;
	int shuffleNumber = getNumberCut(line,percent);
	cout << "Now, your message is already encryption." << endl;
	list.shuffle(shuffleNumber);
	list.print();
	cout << "-----------------------------------------" << endl;

	/*shuffle back*/
	cout << "Next,if you like to decryption this message" << endl;
	cout << "shuffle it back !!" ;
	int back = 0;
	cin >> back;
	int backNumber = getNumberCut(line,back);
	list.shuffleBack(backNumber);
	list.print();
	cout << "Now you must put rotateback key : ";
	cin >> percent;
	shuffleNumber = getNumberCut(line,percent);
	list.moveCursorToStart();
	int loop = list.getCount() - shuffleNumber;
	cout << loop << endl;
	if(loop > 0){
		for(int i = 1;i < loop;i++){ 
			list.moveCursorForward();
		}
		list.print();
		list.rotateBack(0);
		list.print();
	}else{
		cout << "you key is out of bound !!" << endl;
	}
}