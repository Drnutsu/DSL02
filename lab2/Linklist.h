#ifndef _Linklist_h
#define _Linklist_h

template <typename type>
class Linklist {
private:
	struct Cell{
		type data;
		Cell *link;
	}; 

	Cell *start;
	Cell *cursor;
	Cell *end;
	int itemcount;

public:
	Linklist<type>();
	Linklist<type>(Linklist<type> &);
	~Linklist<type>();
	void insertData(type);
	void deleteData();
	bool moveCursorForward();
	bool moveCursorBackward();
	void moveCursorToStart();
	void moveCursorToEnd();
	void rotate(int);
	void shuffle(int);
	void shuffleBack(int);
	void rotateBack(int);
	type getCursorData();
	void print();
	int getCount();
	Linklist<type> copyList(Linklist<type>);
};


template <typename type>
Linklist<type>::Linklist(){
	start = cursor = new Cell;
	start->link = nullptr;
	itemcount = 0;
}

template <typename type>
Linklist<type>::~Linklist(){
	try{
		Cell *cp = start;
		while(cp != nullptr){
			Cell *next = cp->link;
			delete cp;
			cp = next;
		}
	}catch(int e){
		cerr << e;
	}
}

template <typename type>
void Linklist<type>::insertData(type data){
	Cell *cp = new Cell;
	cp->data = data;
	cp->link = cursor->link;
	cursor->link = cp;
	cursor = cp;
	end = cursor;
	cout << "[]<<[" << cursor->data << "]" << endl;
	itemcount++;
}

template <typename type>
void Linklist<type>::deleteData(){
	Cell *next;
	Cell *cp = start;
	while(cp->link != cursor){
		cp = cp->link;
	}
	next = cursor->link;
	delete cursor;
	cp->link = next;
	cursor = cp;
}

template <typename type>
bool Linklist<type>::moveCursorForward(){
	if(cursor->link != nullptr){
		cursor = cursor->link;
		return true;
	}else{
		return false;
		cout << "The cursor is at the end of the list !" << endl;
	}
}

template <typename type>
bool Linklist<type>::moveCursorBackward(){
	if(cursor != start->link){
		Cell *cp = start->link;
		while(cp->link != cursor){
			cp = cp->link;
		}
		cursor = cp;
		return true;
	}else{
		cout << "The cursor has already at first data !" << endl;
		return false;

	}
}

template <typename type>
void Linklist<type>::moveCursorToStart(){
	cursor = start->link;
}

template <typename type>
void Linklist<type>::moveCursorToEnd(){
	while(cursor->link != nullptr){
		cursor  = cursor->link;
	}
}

template <typename type>
void Linklist<type>::print(){
	Cell *cp = start->link;
	while(cp != nullptr){
		cout << "[" << cp->data << "]";
		cp = cp->link;
	}
	cout << endl;
	Cell *c = start->link;
	cout << " ";
	while(c != cursor){
		cout << "   ";
		c = c->link;
	}
	cout << "^";
	cout << endl;
	cout << cursor->data << endl;
}

template <typename type>
type Linklist<type>::getCursorData(){
	return cursor->data;
}


template <typename type>
Linklist<type>::Linklist(Linklist<type> &input){
	this->cursor = this->start = new Cell;
	start->link = nullptr;
	input.moveCursorToStart();
	do{
		type data = input.getCursorData();
		this->insertData(data);
	}while(input.moveCursorForward());
}

template <typename type>
void Linklist<type>::rotate(int input){
	moveCursorToStart();
	for(int i = 1;i < input;i++){ // i = 0 is dummy cell.
		moveCursorForward();
	}
	Cell *beginJoint  = start->link;
	start->link = cursor->link;
	cursor->link = nullptr;
	end->link = beginJoint;
}

template <typename type>
void Linklist<type>::shuffle(int input){
	moveCursorToStart();
	for(int i = 1;i < input;i++){ 
		moveCursorForward();
	}
	Cell *left;
	Cell *right;
	if(input >= (itemcount/2)){ //To avoid case shuffle case is less than half of item count,It's can cause error(We respect loop by only right)
		left = start->link;
		right = cursor->link;
	}else if(input < (itemcount/2)){
		left = cursor->link;
		right = start->link;
		start->link = cursor->link; //change start point for change right or left.
		cursor->link = nullptr;
	}
	while(right != nullptr){
		Cell *oldLeftLink = left->link; // Collect old left link.
		left->link = right; //joining left to right.
		Cell *oldRightLink = right->link; // Collect old right link.
		right->link = oldLeftLink; // joining right to next Left.
		left = oldLeftLink;//forward left to next left, oldLeftLink collected the old left link before changed.
		right = oldRightLink; //same as left.
	}
	if(input >= (itemcount/2)){
		cursor->link = nullptr;
	}
}
template <typename type>
void Linklist<type>::shuffleBack(int input){
	/*Cell *left = start->link;
	Cell *rightjoint;
	Cell *right;
	right = rightjoint = start->link->link;
	// The even case and odd case is difference in the last left side item,so we should divide by case.
	//EVEN CASE 
	if(itemcount % 2 == 0){ 
	while(left->link != nullptr && right->link != nullptr){
	left->link = right->link; // joining to next left.
	left = left->link; // move to next left
	if(left->link->link == nullptr)break;
	right->link = left->link; // joinging to next right.
	right = right->link; // move to next right.
	}
	right->link = nullptr; //clear the last item link,avoid from infinity loop.
	left->link->link = rightjoint; //joining left row and right row.
	}else {
	// ODD CASE same as even but out form loop previous even for one loop.
	while(left->link != nullptr && right->link != nullptr){
	left->link = right->link; 
	left = left->link; 
	if(left->link == nullptr)break;
	right->link = left->link; 
	right = right->link; 
	}
	right->link = nullptr;
	left->link = rightjoint;
	}
	end = right;*/
	moveCursorToEnd();
	end = cursor; //make end to be real last item.
	Cell *old;
	moveCursorToStart();
	if(input >= (itemcount/2)){
		int loop = itemcount - input;
		for(int i = 0;i < loop;i++){
			old = cursor;
			cursor = cursor->link;
			old->link = cursor->link;
			end->link = cursor;
			cursor->link = nullptr;
			end = cursor;
			cursor = old->link;
		}
	}else if(input < (itemcount/2)){
		moveCursorToStart();
		Cell *startJoint = cursor; //this value collected the first item form old linklist before shulffle back.
		for(int i = 1;i < input * 2;i++)moveCursorForward(); //move cursor to the last item that should shuffle.

		for(int i = 0;i < input;i++){  //move cursor to change link back.
			old = cursor;
			moveCursorBackward(); 
			cursor->link = old->link;
			old->link = startJoint;
			startJoint = old;
			moveCursorBackward();
		}
		start->link = startJoint;
	}
}

template <typename type>
void Linklist<type>::rotateBack(int input){
	cout << "end :" << end->data << endl;
	if(input >= (itemcount/2))moveCursorForward();//in case item morethan itemcount/2 the cursor is wrong point.
	Cell *old = cursor->link;
	cursor->link = nullptr;
	end->link = start->link;
	start->link = old;
}

template <typename type>
int Linklist<type>::getCount() {
	return itemcount;
}

#endif

