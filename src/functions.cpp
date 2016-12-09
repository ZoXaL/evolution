#include <iostream>
#include <climits>

using namespace std;

int getInt(istream& stream, int min=INT_MIN, int max=INT_MAX) {
	int result = 0;	
	bool correctInput;
	do {
		correctInput = true;
		stream >> result;
		if(stream.ios::fail() || stream.peek() != 10) {
			stream.ios::clear();
			stream.ignore(80, '\n');
			correctInput = false;			
		} else {
			if (result > max || result < min) {
				correctInput = false;
			}
		}
		if (!correctInput) {
			cout << "Incorrect input, repeat please: ";
		}
	} while(!correctInput);		
	stream.ignore(80, '\n');
	return result;
}	

bool checkRange(int check, int min, int max) {
	return (check <= max && check >= min);
}
