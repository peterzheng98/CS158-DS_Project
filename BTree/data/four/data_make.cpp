#include <cassert>
#include <iostream>
#include <fstream>  
#include <string>
const long long maxn = 6 * 1e6;
int flag[maxn] = {0};
int key;
const bool random_type = 1;
int random_seed = 99962;
using namespace std;
inline int abs(int a){
    return a > 0 ? a : -a;
}

int rand(){
    random_seed = abs(55762 * random_seed * random_seed + 10744 * random_seed + 233 * random_seed * random_seed * random_seed + 103421);
    return random_seed;
}


int main(){
  ofstream OpenFile("insert.data");
　 if(OpenFile.fail()){  
    cout<<"Error while opening files."<<endl;
      exit(2);
    }  
  for(long long i = 0; i < maxn; i++){
    key = (random_type) ? rand() % maxn : i;
    if(flag[key]) ;
    else{
      cout << i << '\n';
      flag[key] = 1;
      int value = rand();
      //if(rand() % 2) OpenFile << 'q' << ' ' << key << '\n';
      //else OpenFile << 'e' << ' ' << key << '\n';
      OpenFile << 'i' << ' ' << key << ' ' << value << '\n';
    }
  }
  OpenFile.close();  
}
