#include<iostream>

using namespace std;


template<class T> class MyList;
template<class T> MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2);
template<class T> MyList<T> operator + (const MyList<T> &l1, const T &item);
template<class T>  ostream & operator << (ostream &os, const MyList<T> &obj);


template<class T>
class MyList{
	friend MyList<T> operator + <>(const MyList<T> &l1, const MyList<T> &l2); 
    friend MyList<T> operator + <>(const MyList<T> &l1, const T &item); 
	friend ostream & operator<< <>(ostream &os, const MyList<T> &obj);

private:
	T *a;
	int size;//the number of storage
	int len;// the number of elements
	
	void double_space(){
	// double the space while the current storage is insufficient
		size *= 2;
		try{
			T *temp = new T[size];
			if (temp==NULL) throw ('f');
			for (long i=0; i<len; ++i){
				temp[i] = a[i];
			}
			delete []a;
			a = temp;
		}
		catch(char){
			cerr << "Allocation failure" << endl;
			exit(1);
		}
	}
	
public:
	MyList(){
		len = 0;
		size = 100;
		a = new T[size];
	}
	
	MyList(int num, const T &item):size(num),len(num){
	// fill MyList with item for num times
		a = new T[size];
		for (long i=0; i<len; ++i){
			a[i] = item;
		}
	}
		
	MyList(const MyList &l):size(l.size),len(l.len){
	// deep copy the other MyList
		a = new T [size];
		for (long i=0; i<len; ++i){
			a[i] = l[i];
		}
	}
	
    MyList(T* arr, int len_arr):size(len_arr),len(len_arr){
    //construct MyList with the first len_arr elements of array arr
		a = new T [size];
		for (long i=0; i<len; ++i){
			a[i] = arr[i];
		}
	}

	void push(const T &item){
	//push item to the end of MyList
		while (len+1 > size) double_space();
		a[len++] = item;
	}
	
	T pop(){
	//delete and return the last element of MyList
		try{
			if (len==0) throw len;
			return a[--len];
		}
		catch(int){
			cerr << "The list is empty!" << endl; 
		}
	}
	
	void insert(int index, const T &item){
	// insert element to the index position of MyList
		while (len+1 > size) double_space();
		if (index<0){
			index = len + index;
		}
		++len;
		for (long i=index+1; i<len; ++i){
			a[i] = a[i-1];
		}
		a[index] = item;
	}
	
	void clean(){
	//clean MyList
		len = 0;
	}
	
	int get_size() const {
	//Return the number of elements of MyList
		return len;
	}
	
	void erase(int start, int end){
	//delete the elements in MyList from start to end
		start =(len+start)%len; end=(len+end)%len;
		len -= end-start+1;
		for (long i=start; i< len; ++i){
			a[i]= a[i+(end-start+1)];
		}
	}
	
	T get_item(int index) const {
	//return the elements in index position	
		try{
			if (index >= len) throw index;
			index =(len+index)%len;
			return a[index];
		}
		catch(int){
			cerr << "Index required is out of range!" << endl; 
		}
	}
	
	MyList<T> get_item(int start, int end) const{
	//return a new MyList with elements from start to end of this MyList
		try{
			if (start >= len || end >= len) throw len;
			start =(len+start)%len; end=(len+end)%len;
			if (start>end){
				MyList<T> temp;
				return temp;
			}else{
				T arr[end-start+1];
				for (long i=start; i<=end; ++i){
					arr[i-start] = a[i];
				}
				MyList<T> temp(arr, end-start+1);
				return temp;
			}
		} 
		catch(int){
			cerr << "Index required is out of range!" << endl; 
			exit(1);
		}
	}
	
	int count(const T &item) const {
	//return the number of elements in MyList which is equal to item
		int ans = 0;
		for (long i=0; i<len; ++i){
			if (a[i]==item) ++ans;
		}
		return ans;
	}
	
	void remove(const T &item){
	// remove the first element in MyList which is equal to item
		for (long i=0; i<len; ++i){
			if (a[i]==item){
				--len;
				for (long j=i; j<len; ++j){
					a[j] = a[j+1];
				}
				return;
			}
		}
	}

	
	MyList<T> &operator = (const MyList<T> &l){
	//assignment operation
		if (&l==this) return *this;
		size = l.get_size();
		len = l.get_size();
		delete [] a;
		a = new T[size];
		for (long i=0; i<len; ++i){
			a[i] = l[i];
		}
		return *this;
	}
	
	MyList &operator += (const T &item){
	//push item to the end of MyList
		push(item);
	}
	
	MyList &operator += (const MyList &l){
	//Add the MyList l to the end of this MyList
		for (long i=0; i<l.get_size(); ++i){
			push(l[i]);
		}
		return *this;
	}
	
	T &operator [](int index) const {
    //return the elements in index position	
		try{
			if (index >= len) throw index;
			index =(len+index)%len;
			return a[index];
		}
		catch(int){
			cerr << "Index required is out of range!" << endl; 
			exit(1);
		}
	}	

	void sort(int l, int r, bool less=true){
	// using quick sort to sort the elements of MyList
	// less=true means ascending order, less=false means decending order
		int i, j;
		T mid, t;
		try{
			if (l<0 || r>=len) throw 0;
			i = l; j = r;
		}
		catch(int){
			cerr << "Index required is out of range!" << endl;
			exit(1);
		}
		mid = a[(l+r)/2];
		if (less){
			do{
				while (a[i]<mid) ++i;
				while (a[j]>mid) --j;
				if (i<=j){
					t = a[i]; a[i]=a[j]; a[j] = t;
					++i; --j;
				}
			}while (i<=j);
		}else{
			do{
				while (a[i]>mid) ++i;
				while (a[j]<mid) --j;
				if (i<=j){
					t = a[i]; a[i]=a[j]; a[j] = t;
					++i; --j;
				}
			}while (i<=j);
		}
		if (l<j) sort(l,j,less);
		if (i<r) sort(i,r,less);
	}
	
	void reverse(){
	//reverse the elements in MyList
		T *temp = new T[size];
		for (long i=0; i<len; ++i){
			temp[i] = a[len-1-i];
		}
		delete []a;
		a = temp;
	}

	~MyList(){delete [] a;}
};



template<class T> 
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2){
// merge two MyLists
	MyList<T> temp(l1);
	temp += l2;
	return temp;
}

template<class T> 
MyList<T> operator + (const MyList<T> &l1, const T &item){
// return a new MyList which is equal to l1 pushed by item
	MyList<T> temp(l1);
	temp.push(item);
	return temp;
}

template<class T>  
ostream & operator << (ostream &os, const MyList<T> &obj){
// printing MyList when type T can be cout directly
	os << "[";
	if (obj.get_size()==0){
		os << "]"; 
		return os; 
	}
	for (long i=0; i<obj.get_size()-1; ++i){
		os << obj[i] << ", ";
	}
	os << obj[obj.get_size()-1] << "]";
	return os;
}



int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
	
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	
	a.sort(0,4); // a = [0, 1, 2, 4, 15]
	
	a.reverse(); // a = [15, 4, 2, 1, 0]
	
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3);// b = [] 
	b = a.get_item(3, -1); // b = [1, 0, 12] 

	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	cout << a << endl;
	a.erase(2, 5); // a = [15, 4, 1, 0, 12]
	//NOTICE: Element 1 is missed in the origin file! 
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12]
	
	b.insert(3, 116); // b = [15, 4, 1, 116, 0, 12, 15, 4, 1, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout << c << endl; 
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}

