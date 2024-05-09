#include<bits/stdc++.h>
using namespace std;
map<int,int> keymap1;
map<int,int> keymap2;
void setPermutations(string key,int k)
{
    for(int i=0;i<key.size();i++)
    {
        if(k==1)keymap1[key[i]]=i;
        else keymap2[key[i]]=i;
    }
}
string encrypt(string plaintext,string key,int k)
{
    map<int,int> keymap;
    if(k==1)keymap=keymap1;
    else keymap=keymap2;
    int row,col,j;
    col=keymap.size();
    row=plaintext.size()/col;
    if(plaintext.size()%col)row++;
    char matrix[row][col];
    for(int i=0,k=0;i<row;i++)
    {
        for(int j=0;j<col;)
        {
            if(plaintext[k]=='\0')
            {matrix[i][j]='_';j++;}
            if(isalpha(plaintext[k]) || plaintext[k]==' ')
            {
                matrix[i][j]=plaintext[k];
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
    map<int,int> :: iterator itr;
    string ciphertext="";
    for(itr=keymap.begin();itr!=keymap.end();itr++)
    {
        int j=itr->second;
        for(int i=0;i<row;i++)
        {
            if(isalpha(matrix[i][j]) || matrix[i][j]==' '|| matrix[i][j]=='_')
            ciphertext+=matrix[i][j];
        }
    }
    return ciphertext;
}
string decrypt(string ciphertext,string key,int ke)
{
    map<int,int> keymap;
    if(ke==1)keymap=keymap1;
    else keymap=keymap2;
    int row,col,j;
    col=keymap.size();
    row=ciphertext.size()/col;
    if(ciphertext.size()%col)row++;
    char cipherMat[row][col];
    for (int j=0,k=0; j<col; j++)
        for (int i=0; i<row; i++)
            cipherMat[i][j] = ciphertext[k++];
 
    int index = 0;
    for( map<int,int>::iterator ii=keymap.begin(); ii!=keymap.end(); ++ii)
        ii->second = index++;
    char decCipher[row][col];
    map<int,int>::iterator ii=keymap.begin();
    int k = 0;
    for (int l=0,j; key[l]!='\0'; k++)
    {
        j = keymap[key[l++]];
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
int main()
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
    setPermutations(key1,1);
    setPermutations(key2,2);
    string cipher1 = encrypt(msg,key1,1);
    cout << "Encrypted Message After pass1: " << cipher1 << endl;
    string cipher2=encrypt(cipher1,key2,2);
    cout<<"Encrypted Message After pass2: "<<cipher2<<endl;
    cout << "Decrypted Message: " << decrypt(decrypt(cipher2,key2,2),key1,1)<< endl;
 
    return 0;
}
