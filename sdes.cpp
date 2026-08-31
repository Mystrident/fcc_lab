#include <iostream>
#include <string>
using namespace std;

// ---------- PERMUTATION TABLES ----------

int P10[]    = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int P8[]     = {6, 3, 7, 4, 8, 5, 10, 9};
int IP[]     = {2, 6, 3, 1, 4, 8, 5, 7};
int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};
int EP[]     = {4, 1, 2, 3, 2, 3, 4, 1};
int P4[]     = {2, 4, 3, 1};


// ---------- S-BOXES ----------

int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

string permute(string bits, int table[], int size){
    
    string result="";
    
    for(int i=0;i<size;i++){
        
        result+=bits[table[i]-1];
    }
    
    return result;
}

string xorr(string a, string b){
    
    string result="";
    
    for(int i=0;i<a.size();i++){
        if(a[i]==b[i])
            result+='0';
        else
            result+='1';
    
    }
    
    return result;
}

string sbox(int box[4][4],string bits){
    
    int row=(bits[3]-'0')*2+(bits[0]-'0');
    int col=(bits[2]-'0')*2+(bits[1]-'0');
    
    int value = box[row][col];
    
    if(value==0)
        return "00";
    if(value==1)
        return "01";
    if(value==2)
        return "10";
    return "11";
}

string f(string right, string key){
    
    string expanded =permute(right,EP,8);
    
    string xored= xorr(expanded,key);
    
    string l=xored.substr(0,4);
    string r=xored.substr(4,4);
    
    string s0=sbox(S0,l);
    string s1=sbox(S1,r);
    
    string combined=s0+s1;
    
    return permute(combined,P4,4);
    
}

string leftshift(string a,int n){
    
    string x=a.substr(n);
    string y=a.substr(0,n);
    
    return y+x;
}

void generatekeys(string keys,string &K1, string &K2){
    
    string key = permute(keys,P10,10);
    
    string left = key.substr(0,5);
    string right=key.substr(5,5);
    
    left=leftshift(left,1);
    right=leftshift(right,1);
    
    K1=permute(left+right,P8,8);
    
    left=leftshift(left,2);
    right=leftshift(right,2);
    
    K2=permute(left+right,P8,8);
}

string encrypt(string plaintext,string key){
    
    string K1,K2;
    generatekeys(key,K1,K2);
    
    string bits=permute(plaintext,IP,8);
    
    string left=bits.substr(0,4);
    string right=bits.substr(4,4);
    
    left = xorr(left,f(right,K1));
    
    swap(left,right);
    
    left=xorr(left,f(right,K2));
    
    bits=left+right;
    
    return permute(bits,IP_INV,8);
    

}

int main(){
    
    string plaintext;
    string key;
    
    cout<<"enter plain text";
    cin>>plaintext;
    
    cout<<"entery key";
    cin>>key;
    
    string ciphertext=encrypt(plaintext,key);
    
    cout<<"ciphertext is : "<<ciphertext<<endl;
    
    return 0;
}