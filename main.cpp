#include <iostream>
#include<cstring>
#include<cstdio>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cstddef>
#include <vector>
#include <map>
#include <array>


using namespace std;

void encodeTea (unsigned int* k, unsigned int* w,unsigned int* v) {

      register unsigned int delta=0x9E3779B9;//https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm max deðeri
      register unsigned int v0=v[0], v1=v[1], i, sum=0;

    for(i=0;i<32;i++){
       v0+=(((v1<<4)^(v1>>5))+v1)^(sum+k[sum&3]);
         sum+=delta;
        v1+=(((v0<<4)^(v0>>5))+v0)^(sum+k[(sum>>11)&3]);

    }
    w[0]=v0; w[1]=v1;

}

void TeaEncode(const std:: string &str,const std:: string& key,std::string*out)
{
    unsigned int keybuffer[4];
    unsigned int k[4];
    unsigned int w[2];
    unsigned int v[2];
    //unsigned int kullanmak iþaretsiz integer deðerleri saðladýðý için þifre metni ne olacaðýný bilmediðimizden daha avantajlýdýr.

    // Dizinin uzunluðunu belirleyerek deðerini set ediyoruz.-->
    memset (k,0,sizeof(k));
    memset (w,0,sizeof(w));
    memset (v,0,sizeof(v));
    memset ( keybuffer, 0, sizeof(keybuffer) );
    out->clear();
    // Process the key
    int len=key.length();
    if (len>16)
        len=16;
    memcpy(keybuffer ,key.c_str() ,len );
    for ( int i=0;i<4;++i){
       k[i]=keybuffer[i];
    }
    // Giriþ dizisini tampon belleðe kopyalýyoruz
    int strbuflen= str.length ();
    if (strbuflen == 0){
        return ;
    }
    if((strbuflen%4)>0){
       strbuflen += 4 - (strbuflen % 4);
    }
    unsigned char*strbuf=new unsigned char[strbuflen];
    memset(strbuf,0,strbuflen);
    memcpy (strbuf,str.c_str(),str.length() );

    // Encoding Ýþleminin Çalýþmasý
    v[1]=0;
    for(int i=0;i<strbuflen;i+=4)
    {
        v[0]=*(unsigned int*) &strbuf[ i ];

        encodeTea (&v[0],&w[0],&k[0]);
        out->append(( char* ) &w [0],4);

        v[1]=w[1];

    }
    out->append((char*) &v[1] ,4);

    delete []strbuf;//tamponu gerek kalmadýðý için siliyoruz.
}
int main ()
{
// Dosyalama Ýþlemleri
	ifstream fileIn;
	ofstream fileOut;

    string f1, f2, f3;
	string *fileName=&f1;//Dosyamýz
	string *key=&f2;//Anahtar

	cout << "Anahtari(Key Value) giriniz:" << endl;
	getline(cin, *key);
	cout << "Hedef Dosyanin Ismini Giriniz:" << endl;
	getline(cin, *fileName);
    fileIn.open(*fileName,ios::in|ios::binary);
    string str (( istreambuf_iterator <char> (fileIn)),istreambuf_iterator <char>() );
    fileIn.close();

	cout << "Dosya Sisteme Basarili Yuklendi!" << endl;
	system("pause");

string outdata;
	TeaEncode(str,f2,&outdata);
	str = "0";
	cout<<"Cikti Dosyasinin Ismini Giriniz:"<<endl;
	getline (cin, *fileName);
	fileOut.open( *fileName,ios:: out|ios:: binary );
    fileOut.write (outdata.c_str(),outdata.size() );
	cout << "Ýslem Tamamlandi !!!" << endl<<endl<<endl;


	system("pause");
	cout<<"Program Calisma Dizinindeki Uzerinde Ýslem Yaptiniz Dosyayi Kontrol Ediniz!"<<endl;
}
