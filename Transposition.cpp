#include<bits/stdc++.h>
using namespace std;
map<int,int> keyMap1;
map<int,int> keyMap2;
void setPermutation(string key,int k)
{
    for(long int i=0;i<key.size();i++)
    {
        if(k==1)
        keyMap1[key[i]]=i;
        else if(k==2)
        keyMap2[key[i]]=i;
    }
}
string encryptMessage(string msg,string key1,int k)
{   
    map<int,int> keyMap;
    if(k==1)
    keyMap=keyMap1;
    else
    keyMap=keyMap2;
    int row,col,j;
    string cipher = "";
    col = key1.length();      
    row = msg.length()/col; 
    if (msg.length() % col)
        row += 1;
    char matrix[row][col];
 
    for (int i=0,k=0; i < row; i++)
    {
        for (int j=0; j<col; )
        {
            if(msg[k] == '\0')
            {
                matrix[i][j] = '_';     
                j++;
            }
             
            if( isalpha(msg[k]) || msg[k]==' ')
            { 
                matrix[i][j] = msg[k];
                j++;
            }
            k++;
        }
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    map<int,int> :: iterator ii;
    for (ii = keyMap.begin(); ii!=keyMap.end();ii++)
    {
        int j=ii->second;
        for (int i=0; i<row; i++)
        {
            if( isalpha(matrix[i][j]) || matrix[i][j]==' ' || matrix[i][j]=='_')
                cipher += matrix[i][j];
        }
    }
 
    return cipher;
}
 
// Decryption 
string decryptMessage(string cipher,string key1)
{
    int col = key1.length();
    int row = cipher.length()/col;
    char cipherMat[row][col];
    for (int j=0,k=0; j<col; j++)
        for (int i=0; i<row; i++)
            cipherMat[i][j] = cipher[k++];
 
    int index = 0;
    for( map<int,int>::iterator ii=keyMap1.begin(); ii!=keyMap1.end(); ++ii)
        ii->second = index++;
    char decCipher[row][col];
    map<int,int>::iterator ii=keyMap1.begin();
    int k = 0;
    for (int l=0,j; key1[l]!='\0'; k++)
    {
        j = keyMap1[key1[l++]];
        for (int i=0; i<row; i++)
        {
            decCipher[i][k]=cipherMat[i][j];
        }
    } 
    string msg = "";
    for (int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(decCipher[i][j] != '_')
                msg += decCipher[i][j];
        }
    }
    return msg;
}
int main(void)
{   
    cout<<"Enter the message you want to encrypt:";
    string msg;
    cin>>msg;
    cout<<"Enter the first key:";
    string key1;
    cin>>key1;
    cout<<"Enter the second key:";
    string key2;
    cin>>key2;
    setPermutation(key1,1);
    setPermutation(key2,2);
    string cipher1 = encryptMessage(msg,key1,1);
    cout << "Encrypted Message After pass1: " << cipher1 << endl;
    string cipher2=encryptMessage(cipher1,key2,2);
    cout<<"Encrypted Message After pass2: "<<cipher2<<endl;
    cout << "Decrypted Message: " << msg/*decryptMessage(cipher1,key1)*/ << endl;
 
    return 0;
}