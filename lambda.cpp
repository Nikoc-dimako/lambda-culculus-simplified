#include "functions.h"

using namespace std;
int main(int argc,char* argv[]){

	string str="",result="";

	str=argv[1];

	cout<<"input="<<str<<endl<<endl;
	str=cutString(str);
	str=remove_outer_parenthesis(str);
	str=cutString(str);
	result = normalize(str);
	cout<<"result="<<result<<endl;

	return 0;
}
