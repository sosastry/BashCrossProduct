#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <regex>
using namespace std;

/* Creates a stack comprised of each element in the input string.
 * Returns an empty stack if there are invalid characters in the string */
stack<string> createInputStack(string input) {
    stack<string> inputStack;
    string temp;
    string curr;

    for (int i=0; i<input.length(); i++) {
        curr = input.substr(i,1);

        if (!regex_match(curr, regex("[a-zA-Z{},]"))) { // Invalid characters
            return stack<string>();
        } else if (regex_match(curr, regex("[a-zA-Z]"))) {  // alphanumeric character
            temp += curr; // pass consecutive letters to stack (e.g. {AB} -> AB gets pushed to stack)
        } else {
            if (temp.length() > 0) {
                inputStack.push(temp);
                temp.clear();
            }
            inputStack.push(curr);
        }
    }

    return inputStack;
}

/* Applies the element input to every item in the result list */
void createCrossProduct(vector<string>& resultList, string element) {
    for (int i=0; i<resultList.size(); i++) {
        resultList[i] = element + resultList[i];
    }
}

/* Iterates through stack to determine when to apply cross product.
 * Returns final list with result of cross product expansion. */
vector<string> getCrossProductExpansion(string input) {
    stack<string> inputStack = createInputStack(input);
    vector<string> resultList;
    vector<string> tempList; // list to hold intermediate results before cross product

    if (inputStack.empty()) {
        cout << "Invalid Input. Input characters must match: [a-zA-Z{},]\n";
        return resultList;
    }

    string curr;
    string next;
    int rightBracketCounter = 0;

    while (!inputStack.empty()) {
        curr = inputStack.top(); // access top element
        inputStack.pop();

        if (curr == "{") {
            if (!inputStack.empty()) {
                next = inputStack.top();
                inputStack.pop();

                if (next == "}") {
                    next = inputStack.top();
                    inputStack.pop();
                }
                createCrossProduct(resultList, next);
            }
        } else if (regex_match(curr, regex("[a-zA-Z]+"))) {  //alphanumeric character(s)
            resultList.push_back(curr);
        } else if (curr == "}") {
            rightBracketCounter++;
        }
    }

    return resultList;
}

/* Prints cross product result in readable format*/
void printResult(vector<string> input) {
    if (input.size() != 0) {
        cout << "Cross Product Result: ";
        for (int i=input.size()-1; i>=0; i--) {
            cout << input[i] << " ";
        }
    } else {
        cout << "No Results or Invalid Input";
    }

    cout << "\n";
}

/* TODO: move to test suit & use Google Test (or similar test framework) to assert that these match expected output */
void runTestInputs() {
    vector<string> inputTests;
    inputTests.push_back("{ABC}");
    inputTests.push_back("{A}");
    inputTests.push_back("{A,B}");
    inputTests.push_back("A{B,C}");
    inputTests.push_back("AB{A,C}{D}"); //Note: does not work
    inputTests.push_back("{A,B}{C,D}"); //Note: does not work
    inputTests.push_back("123");
    inputTests.push_back("{1,2,3}");

    vector<string> result;

    for (int i=0; i<inputTests.size(); i++) {
        cout << "Input " << i << ": " << inputTests[i] << "\n";
        result = getCrossProductExpansion(inputTests[i]);
        printResult(result);
        result.clear();
        cout << "\n";
    }
}

/* Reads from Standard in */
int main() {
    cout << "Enter the input:" << endl;
    string input_str;
    getline(cin, input_str);

    vector<string> resultList = getCrossProductExpansion(input_str);
    printResult(resultList);

    return 0;
}