#include <iostream>

#include "FileToVecClass.h"
#include "cr/cryptlib.h"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "src/md5.h"
#include "cryptEssential.h"

vector<char> hashVec(vector<char> dig) {
    md5::md5_t md5;
    md5.process(dig.data(), dig.size());
    md5.finish();
    char in[MD5_STRING_SIZE];
    vector<char> hash(MD5_STRING_SIZE);
    md5.get_string(hash.data());
    return hash;
}

lli genMutPrime(lli p) {
    lli check = 0, d;

    while (check == 0) {
        d = random(4, p);

        if (extGCD(p, d).at(0) == 1) {
            check = 1;
        }
    }
    return d;
}
lli invEv(lli a,lli b){
    if((a%b*(extGCD(b,a).at(2)+b))%b){

        return (extGCD(b,a).at(2)+b);
    }
    return 0;
}
int ElGamalSub(const string &filename) {
    FileVec temp(filename);
    vector<char> hash = hashVec(temp.getCharVec());
    lli iQ = 0;
    lli iP = 0;
    lli iG = 0;
    do {
        iQ = rand() % ((lli) pow(10, 9) - 1) + (lli) pow(10, 6);
        iP = 2 * iQ + 1;
    } while (!(checkSimple(iQ) && checkSimple(iP)));
    do {
        iG = rand() % (iP - 2) + 2;
    } while (modPow(iG, iQ, iP) == 1);
    lli x = random(2,iP-1);
    lli y=modPow(iG,x,iP);
    lli k = genMutPrime(iP - 1);
    lli r= modPow(iG,k,iP);
    vector<lli> hashEncVec;

    for(int i=0;i<MD5_STRING_SIZE;i++){

        lli t=((hash.at(i)-x*r)%(iP-1));
    //   cout<<t;
    //    cout<<modPow(invEv(k,iP),t,iP-1);
     //   cout<<endl;
        hashEncVec.push_back((invEv(k,iP)*t)%(iP-1));
    }
    cout<<endl;
    for(auto &i:hashEncVec){
        cout<<i<<" ";
        cout<<((lli)pow(y,r)*(lli)pow(r,i));
    }
    cout<<endl;
    int count=0;
    for(int i=0;i<MD5_STRING_SIZE;i++){
        //cout<<(modPow(iG,hash.at(i),iP))<<" ";
        cout<< (pow(y,r)*pow(r,hashEncVec.at(i)));
        count++;
    }

}
lli genPrime(lli min = 4, lli max = 100) {
    lli temp = 4;
    while (!checkSimple(temp)) {
        temp = random(min, max);

    }
    return temp;
}
int RSASub(const string &filename){
    lli p,q,n,phi;

    int iter=0;

    q= genPrime(4,(lli)pow(10,4));
    p= genPrime(4,(lli)pow(10,5));
    n=p*q;
    phi=(p-1)*(q-1);
    lli c,d=phi+1;
    lli check=0;
    while(d>phi||check==0){
        d= random(4,phi);
        if(extGCD(phi,d).at(0)==1){
            check=1;
        }
        else{
            check=0;

        }


    }
    FileVec temp(filename);
    vector<char> hash = hashVec(temp.getCharVec());
    // nlPrint("check");
    //  nlPrint(check);
    //nlPrint( d);
    // nlPrint( extGCD(phi,d));
    c= invEv(d,phi);
    vector<lli> hashEncVec;

    for(int i=0;i<MD5_STRING_SIZE;i++){
   //     hashEncVec.push_back(modPow(invEv(k,iP),t,iP-1));
    }

}
int main(int argc, char *argv[]) {
    string filename = "../test.txt";
    ElGamalSub(filename);
    RSASub(filename);
}