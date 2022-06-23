/**
 *  Add ;name= for MIME file using data from Content-Location line
 *  this is needed as preparation for munpack with correct file names
 *  for very strange Confluence export format
 *
 *  This is input stream to output stream processor without any parameters
 *
 *  COMPILE: g++ addmimename.cxx
 *  USAGE: ./addmimename <file1.doc>file2.doc && munpack file2.doc && yandex-browser export.html
 *
 */
#include <iostream>
#include <iterator>
using namespace std;
#define LINES_AFTER_CONTENT_TYPE 3
#define CONTENT_TYPE "Content-Type"
#define CONTENT_LOCATION "Content-Location"
#define C_DRIVE_LOCATION "C:/"
#define NAME_PART "name="
int main() {
   int headNoName=0;
   bool hasName=false;
   string lines[LINES_AFTER_CONTENT_TYPE];
   string name="";
   for (string line; getline(cin, line);) {
	if (line.find(CONTENT_TYPE)!=string::npos && line.find(NAME_PART)==string::npos) {
		headNoName=LINES_AFTER_CONTENT_TYPE;
		hasName=false;
        }
	if (headNoName==0) {
		cout<<line<<endl;
	}
	if (line.find(CONTENT_LOCATION)!=string::npos && line.find(C_DRIVE_LOCATION)!=string::npos) {
		name=line.substr(line.find(C_DRIVE_LOCATION)+3);
		hasName=true;
	}
	if (headNoName>0) {
		lines[headNoName-1]=line;
	}
	if (headNoName==1) {
	    for (int i=0; i<LINES_AFTER_CONTENT_TYPE; i++) {
	        cout<<lines[LINES_AFTER_CONTENT_TYPE-i-1];
	        if (i==0 && hasName) {
			    cout<<"; name="<<name;
	        }
		    cout<<endl;
	    }
	}
	if (headNoName>0) {
		headNoName=headNoName-1;
	}
   }
   return 0;
}
