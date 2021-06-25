// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
Implement a helper function for the game Hangman.


In this game one player thinks of a secret word and the other player attempts to guess it.
In each turn of the game the guessing player may guess any letter of the alphabet.
Each time they do so, the player who knows the secret word reveals all occurrences of the guessed letter.


You are given the secret word and the collection of letters that have already been guessed: the strings secretWord and lettersGuessed.


Return a copy of secretWord in which the letters that have been already guessed are visible and all other letters are replaced by underscores ('_').


DEFINITION
Class:HangmanHelper
Method:show
Parameters:string, string
Returns:string
Method signature:string show(string secretWord, string lettersGuessed)


CONSTRAINTS
-secretWord will contain between 1 and 50 characters, inclusive.
-Each character in secretWord will be an uppercase English letter ('A'-'Z').
-lettersGuessed will contain between 0 and 26 characters, inclusive.
-Each character in lettersGuessed will be an uppercase English letter ('A'-'Z').
-All characters in lettersGuessed will be distinct.


EXAMPLES

0)
"SECRET"
""

Returns: "______"

The beginning of the game. There haven't been any letters guessed yet, so no letters of the secret word are visible.

1)
"SECRET"
"CAE"

Returns: "_EC_E_"

The guess 'A' hasn't revealed any letters but we do have two 'E's and a 'C'.

2)
"REVEALED"
"QWERTYUIOPASDFGHJKLZXCVBNM"

Returns: "REVEALED"

This time the player has already guessed all possible letters.

3)
"ALONGEREXAMPLE"
"SOMETHING"

Returns: "__ONGE_E__M__E"



// END CUT HERE
#line 70 "HangmanHelper.cpp"
#include <string>
#include <vector>
class HangmanHelper {
	public:
	string show(string secretWord, string lettersGuessed) {
		
	}
};
