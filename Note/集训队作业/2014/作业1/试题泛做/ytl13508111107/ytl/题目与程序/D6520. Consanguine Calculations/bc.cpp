#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<math.h>
#include<set>
#include<iterator>
#include<map>
#include<sstream>
 
 
 
using namespace std;
 
char input[5];
string p1,p2,ch;
 
string all[] = {"AA", "AO", "BB", "BO", "AB", "OO"};
map<string,string> enc;
 
 
string getChild(string pp1, string pp2) {
	//preparing parent1 data
	string p1[2];
	int sz1 = 0;
	string rh1 = pp1.substr(pp1.size()-1,1);
	pp1 = pp1.substr(0,pp1.size()-1);
	if (pp1 == "A") {
		p1[sz1++] = "AA";
		p1[sz1++] = "AO";
	}
	else if (pp1 == "B") {
		p1[sz1++] = "BB";
		p1[sz1++] = "BO";
	}
	else if (pp1 == "O") {
		p1[sz1++] = "OO";
	}
	else if (pp1 == "AB") {
		p1[sz1++] = "AB";
	}
	rh1 += "-";
 
 
	//preparing parent2 data
	string p2[2];
	int sz2 = 0;
	string rh2 = pp2.substr(pp2.size()-1, 1);
	pp2 = pp2.substr(0,pp2.size()-1);
	if (pp2 == "A") {
		p2[sz2++] = "AA";
		p2[sz2++] = "AO";
	}
	else if (pp2 == "B") {
		p2[sz2++] = "BB";
		p2[sz2++] = "BO";
	}
	else if (pp2 == "O") {
		p2[sz2++] = "OO";
	}
	else if (pp2 == "AB") {
		p2[sz2++] = "AB";
	}
	rh2 += "-";
 
 
 
	//generate all possible child alleles
	set<string> s;
 
	for(int i = 0; i < sz1; i++) {
		for (int j = 0; j < sz2; j++) {
			for (int ii = 0; ii < 2; ii++) {
				for(int jj = 0 ; jj < 2; jj++) {
					for(int ri = 0; ri < 2; ri++) {
						for(int rj = 0; rj < 2; rj++) {
							stringstream ss;
							ss << ((char)p1[i][ii]) << ((char)p2[j][jj]);
							string tmp = ss.str();
							tmp = enc[tmp];
							if (rh1[ri] == '+' || rh2[rj] == '+') tmp += '+';
							else tmp += '-';
							s.insert(tmp);
						}
					}
				}
			}
		}
	}
 
	string result = "";
	bool first = true;
	int counter = 0;
	for(set<string>::iterator itr = s.begin(); itr != s.end(); itr++) {
		if (!first) result += ", ";
		first = false;
		result += *itr;
		counter++;
	}
	if (counter > 1) {
		result = "{" + result + "}";
	}
	return result;
}
 
 
string getParent(string pp1, string ch) {
	//preparing parent1 data
	string p1[2];
	int sz1 = 0;
	string rh1 = pp1.substr(pp1.size()-1,1);
	pp1 = pp1.substr(0,pp1.size()-1);
	if (pp1 == "A") {
		p1[sz1++] = "AA";
		p1[sz1++] = "AO";
	}
	else if (pp1 == "B") {
		p1[sz1++] = "BB";
		p1[sz1++] = "BO";
	}
	else if (pp1 == "O") {
		p1[sz1++] = "OO";
	}
	else if (pp1 == "AB") {
		p1[sz1++] = "AB";
	}
	rh1 += "-";
 
 
	//preparing parent2 data
	int sz2 = 6;
	string rh2 = "+-";
 
 
	//generate all possible child alleles
	set<string> s;
 
	for(int i = 0; i < sz1; i++) {
		for (int j = 0; j < sz2; j++) {
			for (int ii = 0; ii < 2; ii++) {
				for(int jj = 0 ; jj < 2; jj++) {
					for(int ri = 0; ri < 2; ri++) {
						for(int rj = 0; rj < 2; rj++) {
							stringstream ss;
							ss << ((char)p1[i][ii]) << ((char)all[j][jj]);
							string tmp = ss.str();
							tmp = enc[tmp];
							if (rh1[ri] == '+' || rh2[rj] == '+') tmp += '+';
							else tmp += '-';
							if (tmp == ch) {
								s.insert(enc[all[j]]+'+');
								if (!(rh1 == "--" && ch[ch.size()-1] == '+')) {
									s.insert(enc[all[j]]+'-');
								}
							}
						}
					}
				}
			}
		}
	}
 
	string result = "";
	bool first = true;
	int counter = 0;
	for(set<string>::iterator itr = s.begin(); itr != s.end(); itr++) {
		if (!first) result += ", ";
		first = false;
		result += *itr;
		counter++;
	}
	if (counter == 0) {
		result = "IMPOSSIBLE";
	}
	else if (counter > 1) {
		result = "{" + result + "}";
	}
	return result;
}
 
 
int main() {
	freopen("calculate.in","r",stdin);
	freopen("bc.out","w",stdout);
	enc["AA"] = "A";
	enc["AO"] = "A";
	enc["OA"] = "A";
	enc["BB"] = "B";
	enc["BO"] = "B";
	enc["OB"] = "B";
	enc["OO"] = "O";
	enc["AB"] = "AB";
	enc["BA"] = "AB";
	int tc = 1;
	while (true) {
		scanf("%s", input); p1 = input;
		scanf("%s", input); p2 = input;
		scanf("%s", input); ch = input;
		if (p1 == "E" && p2 == "N" && ch == "D") break;
		if (p1 == "?") {
			printf("Case %d: %s %s %s\n", tc++, getParent(p2, ch).c_str(), p2.c_str(), ch.c_str());
		}
		else if (p2 == "?") {
			printf("Case %d: %s %s %s\n", tc++, p1.c_str(), getParent(p1, ch).c_str(), ch.c_str());
		}
		else if (ch == "?") {
			printf("Case %d: %s %s %s\n", tc++, p1.c_str(), p2.c_str(), getChild(p1, p2).c_str());
		}
	}
	return 0;
}
 
