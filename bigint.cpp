#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
using namespace std;

/*
//   Creates a default BigInt with base 10.
*/
BigInt::BigInt(){
    
    base = 10;
    isPositive = true;

}

/*
//  Creates a BigInt with a specified base.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        cout << "Invalid Base Error";
        return;
    }
    base = setbase;
    isPositive = true;
}

/*
//  Creates a BigInt from int (base 10) with a specified base.
//  Converts an int (base 10) into a specified base.
//  e.g., (10,2) <-- 10 base 10 to base 2 --> result:  BigInt with value 1010 base 2
//  e.g., (100,16) <--- 100 base 10 to base 16 --> result: BigInt with value 64 base 16
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        cout << "Invalid Base Error";
        return;
    }
    base = setbase;
    //deal with negatives
    if (input < 0) {
        isPositive = false;
        input *= -1;
    }
    else {
        isPositive = true;
    }
    
    if (input < base) {
        vec.push_back(input);
    }
    else {
        while (input!= 0) {
            vec.push_back(input % base);
            input /= base;
        }
    }   
}

/*
//  Creates a BigInt from string with a specified base.
//  Assumes that the string number input is in the same
//      base as the setbase input.
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        cout << "Invalid Base Error";
        return;
    }
    
    base = setbase;
    
    //deal with negatives
    if (s[0] == '-') {
        isPositive = false;
        for (int i = s.size() - 1; i > 0; i--) {
            if (s[i] > 64 && s[i] < 91) {
                vec.push_back((int) (s[i]) - 55);
            }
            else if (s[i] > 47 && s[i] < 58) {
                vec.push_back((int) (s[i]) - 48);
            }
        }  
    }
    else {
        isPositive = true;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] > 64 && s[i] < 91) {
                vec.push_back((int) (s[i]) - 55);
            }
            else if (s[i] > 47 && s[i] < 58) {
                vec.push_back((int) (s[i]) - 48);
            }
        }
    }
}

/*
//  Creates a BigInt from another BigInt.
*/

BigInt::BigInt(const BigInt &b){

    *this = b;
}

BigInt::~BigInt(){}



/*
// Convert to string and return the string
//  Displayed in its corresponding base
*/
string BigInt::to_string(){

    string output = "";
    for (int i=vec.size() - 1; i >= 0; i--) {
        if (vec[i] > 9) {
            output += (char) (vec[i]) + 55;
        }
        else {
            output += (char) (vec[i]) + 48; 
        }
    }
    if (!isPositive) {
        output.insert(0, "-");
    }
    return output;
}

/*
//  Converts BigInt to integer base 10 and return that int
//    If BigInt > INT_MAX, return INT_MAX.
//    If BigInt < INT_MIN, return INT_MIN.
*/
int BigInt::to_int() const{


    unsigned int total = 0;
    int based = 1;
    
    // Do the math and coninuallly check if it is
    // going passed the max/min
    for (unsigned int i=0; i<vec.size(); i++) {
        total+=(vec[i] * based);
        based *= base; 
        if (total > INT_MAX) {
            if (isPositive){
                return INT_MAX;
            }
            else {
                return INT_MIN;
            }
        }        
    }
    
    // Convert it to negative if it is negative
    if (!isPositive) {
        total *= -1;
    }
    return total;  
}

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        cout << "Invalid Base Error";
        return 10000000;
    }
    /************* You complete *************/
    bool asizegreater;
    bool different_sized = false;
    vector <int> smallersized;
    vector <int> biggersized;
    
    // Sets the values of smallersized and biggersized vectors
    // to be used to analyze whether they could be the same if 
    // you disregard leading zeroes
    if (b.vec.size() != vec.size()){
        different_sized = true;
        if (b.vec.size() > vec.size()) {
            asizegreater = false;
             smallersized = vec;
             biggersized = b.vec;
        }
        else {
            asizegreater = true;
             smallersized = b.vec;
             biggersized = vec;
        }
    }
    
    // Make sure all the values in the size difference are zeroes, else
    // return the proper value
    if (different_sized) {
        for (unsigned int i=smallersized.size(); i < biggersized.size(); i++) {
            if (biggersized[i] != 0) {
                if ((!asizegreater && b.isPositive) ||
                    (asizegreater && !isPositive)) {
                    return -1;
                }
                else {
                    return 1;
                }
            }
        }
    }
    else {
        smallersized = vec;
    }
    

    // Check from right to left, ignoring leading zeroes
    for (int i = smallersized.size() - 1; i >=0; i--) {
        if (b.vec[i] > vec[i]) {
            if (b.isPositive) {
                return -1;
            }
            else {
                return 1;
            } 
        }
        else if (vec[i] > b.vec[i]) {
            if (isPositive) {
                return 1;
            }
            else {
                return -1;
            }
        }
    }
    
    // If the magnitudes are equal, check the sign
    if ((isPositive == b.isPositive)) {
        return 0;
    }
    else if (isPositive) {
        return 1;
    }
    else {
        return -1;
    }
}



/*
//  Assignment operator. (i.e., BigInt a = b;)
*/
const BigInt & BigInt::operator = (const BigInt &b){


    base = b.base;
    vec = b.vec;
    isPositive = b.isPositive;
    return *this;
}

/*
//  Addition assignment operator.
//    - Compute a = a + b.
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        cout << "Invalid Base Exception";
        return *this;
    }
    
    // The primary function deals with the subtraction of two positive
    // numbers 
  if (isPositive == b.isPositive) {
      int a_size = vec.size();
      int b_size = b.vec.size();
      
      // This function is written for the lhs to be of greater magnitude
      // so if it isn't, the function calls itself, flipping rhs and lhs
      if (b_size > a_size) {
          BigInt copyofB = b;
          copyofB += *this;
          *this = copyofB;
          return *this;
      }
      else if (b_size == a_size) {
          for (int iterator = a_size - 1; iterator >= 0; iterator--) {
              if (vec[iterator] < b.vec[iterator]) {
                  BigInt copyofB = b;
                  copyofB += *this;
                  *this = copyofB;
                  return *this;
              }
              else if (vec[iterator] > b.vec[iterator]) {
                  break;
              }
          }              
      }
      
      for (int i=0; i<a_size; i++) {
          int a_addend, b_addend;
          
          // Deals with different lengths
          a_addend = vec[i];
          if (i >= b_size) {
              b_addend = 0;
          }
          else {
              b_addend = b.vec[i];
          }
          
          // Does the adition and carries a 1 if necessary
          if ((a_addend + b_addend) < base) {
            vec[i] = a_addend + b_addend;
          }
          else {
              if (i+1 >= a_size) {
                  vec.push_back(0);
              }
              vec[i] = a_addend + b_addend - base;
              vec[i+1]++;   
          }
      }
      return *this;
  }
    
    // if it is a positive plus a  negative it subtracts
    // the positve version of the negative
  else if (isPositive && !b.isPositive) {
      BigInt copyofB = b;
      copyofB.isPositive = true;
      return *this -= copyofB;
  }
    // If it is a negative plus a positive, it subtracts the
    // positive version of the lhs from the rhs
  else {
      BigInt copyofA = *this;
      BigInt copyofB = b;
      copyofA.isPositive = true;
      copyofB -= copyofA;
      *this = copyofB;
      return *this;
  }
}


/*
//  Subtraction assignment operator.
//    - Compute a = a - b
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){

        cout << "Invalid Base Error";
        return *this;
    }

    BigInt copyofB = b;
    // Calls addition if there is a negative
    if (!b.isPositive) {
        copyofB.isPositive = true;
        *this += copyofB;
        return *this;
    }
    else if (!isPositive) {
        isPositive = true;
        *this += b;
        isPositive = false;
        return *this;   
    }
    
    else {
        int longest_size;
        int a_size = vec.size();
        int b_size = b.vec.size();
        bool a_longer;
        if (a_size > b_size) {
            longest_size = a_size;
            a_longer = true;
            
        }
        else if (a_size < b_size) {
            longest_size = b_size;
            a_longer = false;
        }
        else {
            // Check to see which magnitude is greater if
            // They are the same size
            longest_size = a_size;
            a_longer = true;
            for (int iterator = a_size - 1; iterator >= 0; iterator--) {
                if (vec[iterator] < b.vec[iterator]) {
                    a_longer = false;
                    break;  
                }
                else if (vec[iterator] > b.vec[iterator]) {
                    break;
                }
            }
        }
        // Does the real subtraction math
        if (a_longer) {
            for (int i=0; i<longest_size; i++) {
                int bottom_value, top_value;
                top_value = vec[i];
                if (i >= b_size) {
                    bottom_value = 0;
                }
                else {
                    bottom_value = b.vec[i];
                }
                if ( top_value - bottom_value >= 0) {
                    vec[i] -= bottom_value;
                }
                else {
                    vec[i] = top_value - bottom_value + base;
                    (vec[i+1])--;
                }
            }
            
            // Gets rid of all of the extra zeroes
            for (int i = vec.size() - 1; i > 0; i--) {
                if (vec[i] == 0) {
                    vec.pop_back();
                }
                else {
                    break;
                }
            }
            
            // Returns final BigInt
            return *this;
        }
        
        // If a has the smaller magnitude, it calls this same
        // operator with b on the lhs and a on the rhs
        else {
            BigInt copyofA = *this;
            copyofB -= copyofA;
            *this = copyofB;
            isPositive = false;
            return *this;
        }
        
    }
}

/*
//  Multiplication assignment operator.
//    - Compute a = a * b;
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        
        cout << "Invalid Base Error";
        return *this;
    }

    int a_size = vec.size();
    int b_size = b.vec.size();
    vector<int>outputvector(a_size + b_size, 0);
    int outputvindex = 0;
    
    // Carry keeps track of all of the numbers that have to be carried for 
    // each digit on the bottom
    
    for (int b_i=0; b_i < a_size;
         b_i++, outputvindex++) {
        int carry = 0;
        for (int t_i = 0; t_i < b_size; t_i++) {
            if (vec[b_i] * b.vec[t_i] + carry < base) {
                outputvector[t_i + outputvindex] 
                    += vec[b_i] * b.vec[t_i] + carry; 
                carry = 0;
            }
            else {
                // Update carry variable
                int value = vec[b_i] * b.vec[t_i] + carry;
                carry = value / base;
                if (t_i + 1 == b_size) {
                    outputvector[t_i + outputvindex+ 1] = carry;
                }
                outputvector[t_i + outputvindex] += 
                    value - carry * base;                

            }

        }
    }
    
    // Deal with different signs
    if (isPositive == b.isPositive) {
        isPositive = true;
    }
    else {
        isPositive = false;
    }
    
    
    // Alter the outputvector so that none of its values are >= the base
    for (int i = 0; i < a_size + b_size; i++) {
        if (outputvector[i] >= base) {
            outputvector[i+1] += (outputvector[i] / base);
            outputvector[i] -= ((outputvector[i] / base) * base);
        }
    }
    
    // Delete leading zeroes in the outputvector
    for (int i = a_size + b_size - 1; i > 0; i--) {
        if (outputvector[i] == 0) {
            outputvector.pop_back();
            if (i == 1 && outputvector[0] == 0) {
                isPositive = true;
            }
        }
        // If the output is 0, it should be positive
        else {
            break;
        }
    }
    // Copy ouput vector to *this
    vec = outputvector;
    

    
    return *this;
}

/*
//  Division assignment operator.
//  Calls 'divisionMain' to compute a = a / b;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){

        cout << "Invalid Base Error";
        return *this;
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        cout << "Dividing by Zero Error";
        return *this;
    }

    BigInt remainder(base);
    BigInt quotient(base);
    divisionMain(b, quotient, remainder);
    *this = quotient;
    return *this;    

}

/*
//  Modulus assignment operator.
//  Calls 'divisionMain' to compute a = a % b.
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        cout << "Invalid Base Error";
        return *this;
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        cout << "Dividing by Zero Error";
        return *this;
    }

    BigInt remainder(base);
    BigInt quotient(base);
    
    // Set sign of remainder equal to the dividend and never touch it again
    // unless the remainder is 0
    
    remainder.isPositive = isPositive;
    divisionMain(b, quotient, remainder);
    if (remainder.vec.size() == 1 && remainder.vec[0] == 0) {
        remainder.isPositive = true;
    }
    *this = remainder;
    return *this;
}

/*
//  Main function for the Division and Modulus operator.
//  Computes (q)uotient and (r)emainder: a = (b * q) + r.
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/
    int a_size = vec.size();
    int b_size = b.vec.size();
    
    // Return 0 if b's magnitude is greater than a's

    if (b_size > a_size) {
        vector<int> zero (1, 0);
        quotient.vec = zero;
        remainder.vec = vec;
        quotient.isPositive = true;
        return;
    }
    else if (b_size == a_size) {  
         for (int i = a_size - 1; i >= 0; i--) {
             // If b's magnitude is greater than a's return 0
             if (vec[i] < b.vec[i]) {
                vector<int> zero (1, 0);
                quotient.vec = zero;
                quotient.isPositive = true;
                remainder.vec = vec;
                return;
             }
             else if (vec[i] > b.vec[i]) {
                 break;
             }
             
         }
    }
    
    BigInt tempdividend(base);
    BigInt basemultiply(base, base);
    BigInt positiveB = b;
    positiveB.isPositive = true;
    int dividend_index = a_size - 1;
    vector<int> reversedoutput;
    bool reachedfirstdigit = false;
    
    // Loops through the whole dividend, using long
    // division by comparing the temporary dividend 
    // to the divisor or positiveB
    
    while (dividend_index >= 0) {
        tempdividend *= basemultiply;
        tempdividend.vec[0] = vec[dividend_index];
        dividend_index--;
        if (tempdividend.compare(positiveB) == -1) {
            //if adding another digit to the front part of the
            // dividend, add a zero to the output
            if (reachedfirstdigit) {
                reversedoutput.push_back(0);
            }
            continue;
        }
        int timesdivisorgoesinto = 0;
        while (tempdividend.compare(positiveB) != -1) {
            tempdividend -= positiveB;
            timesdivisorgoesinto++;
            
        }
        reversedoutput.push_back(timesdivisorgoesinto);
        reachedfirstdigit = true;

    }
    remainder = tempdividend;
    int outputsize = reversedoutput.size();
    vector<int>orderedvec (outputsize, 0);
    
    // Reverse the vector to be like that of the BigInt class
    
    for (int i=0; i < outputsize; i++) {
        orderedvec[i] = reversedoutput[outputsize - 1 - i];
    }
    quotient.vec = orderedvec;
    
    //deal with different signs
    if (isPositive == b.isPositive) {
        quotient.isPositive = true;
    }
    else {
        quotient.isPositive = false;
    }
    remainder.isPositive = isPositive;
}


/*
//  Exponentiation assignment function.
//  Computes a BigInt whose value is a = pow(a,b).
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        cout << "Invalid Base Error";
        return *this;
    }
    if(!b.isPositive){
        cout << "Dividing by Zero Error";
        return *this;
    }

    
    
    if (b.vec.size() == 1) {
        if (b.vec[0] == 0) {
            vector<int>one (1, 1);
            vec = one;
            isPositive = true;
            return *this;
        }
        else if (b.vec[0] == 1) {
            return *this;
        }
    }
    bool even;
    BigInt two (2, base);
    if ((b % two).to_int() == 0) {
        even = true;
    }
    else {
        even = false;
    }
    int power = (b / two).to_int();
    BigInt asquared = *this * *this;
    BigInt cleanslate = asquared;

        
    for (int i=0; i < power - 1; i++) {
        cleanslate *= asquared;
    }
    if (!even) {
        *this *= cleanslate;
    }
    else {
        *this = cleanslate;
    }
    return *this;
}

/*
//  Modulus Exponentiation assignment function.
//  Computes a = (a ^ b) % m.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        cout << "Invalid Base Error";
        return *this;
    }
    if(!b.isPositive){
        cout << "No Negative Exponents";
        return *this;
    }

    if (b.vec.size() == 1) {
        if (b.vec[0] == 0) {
            vector<int>one (1, 1);
            vec = one;
            isPositive = true;
            return *this;
        }
        else if (b.vec[0] == 1) {
            *this %= b;
            return *this;
        }
    }

    BigInt two (2, base);
    BigInt one (1, base);
    BigInt n = b;
    BigInt tempbase = *this;
    vector<int>onevec (1, 1);
    vec = onevec;
    
 
    while (true){
        if ((n % two).to_int() == 0){

            n /= two;
   
            tempbase = ((tempbase * tempbase) % m);
           
        }
        else if (n.to_int() == 1) {
            break;
        }
        else {
            n -= one;

            *this = ((*this *tempbase) % m);
           
        }
    }
    
    *this *= tempbase;
    
    *this %= m;
    isPositive = true;
    return *this;
}


//----------------------------------------------------
//* Operator overloading, non-member functions
//----------------------------------------------------


//Calls the += function above to compute a BigInt whose value is a + b
BigInt operator + (const  BigInt &a, const BigInt & b){

    BigInt temp = a;
    return temp+=b;
}
//Calls the -= function above to compute a BigInt whose value is a - b
BigInt operator - (const  BigInt &a, const BigInt & b){

    BigInt temp = a;
    return temp -= b;
}
//Calls the *= function above to compute a BigInt whose value is a * b
BigInt operator * (const  BigInt &a, const BigInt & b){

    BigInt temp = a;
    return temp *= b;   
}

//Calls the /= function above to compute a BigInt whose value is a / b
BigInt operator / (const  BigInt &a, const BigInt & b){
    
    BigInt temp = a;
    return temp /= b;
}

//Calls the %= function above to compute a BigInt whose value is a % b
BigInt operator % (const  BigInt &a, const BigInt & b){

    BigInt temp = a;
    return temp %= b;
}
//Calls the exponentiation function above to compute a BigInt whose value is pow(a,b)
BigInt pow(const  BigInt &a, const BigInt & b){
    
  BigInt temp = a;
  return temp.exponentiation(b);
}

//Calls the modulusExp function above to compute a BigInt whose value is (a ^ b) mod c
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    BigInt temp = a;
    return temp.modulusExp(b, m);
}

//Calls the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    if (a.compare(b) == 0) {
        return true;
    }
    else {
        return false;
    }
}

//Calls the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    if (a.compare(b) != 0) {
        return true;
    }
    else {
        return false;
    }
}

//Calls the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    if (a.compare(b) != 1) {
        return true;
    }
    else {
        return false;
    }
}

//Calls the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    if (a.compare(b) != -1) {
        return true;
    }
    else {
        return false;
    }
}

//Calls the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    if (a.compare(b) == 1) {
        return true;
    }
    else {
        return false;
    }
}

//Calls the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    if (a.compare(b) == -1) {
        return true;
    }
    else {
        return false;
    }
}
