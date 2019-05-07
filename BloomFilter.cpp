#include "BloomFilter.h"
#include "IntegerHashes.h"
#include "StringHashes.h"
#include <cstdint>
#include <string>


BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn){
  this->k = k;
  this->m = m;
  
  // initialize bit array
  this->bits = new uint64_t[m]();

  // initialize intfns array
  intfns = new IntegerHash*[k];
  if(intfn=="division"){
    for(int i = 0; i<k; i++){
      intfns[i] = new DivisionHash(i,m);
    }
  } else if (intfn=="reciprocal"){
    for(int i =0; i<k;i++){
      intfns[i] = new ReciprocalHash(i, m);
    }  
  } else {
    for(int i =0; i<k;i++){
      intfns[i] = new SquareRootHash(i, m);
    }
  }

  // initialize strfn
  if(strfn=="pearson"){
    this->strfn = new PearsonHash();
  } else {
    this->strfn = new JenkinsHash();
  }

}

BloomFilter::~BloomFilter(){
  delete [] bits;
  delete strfn;
  for(int i=0; i<k; i++){
    delete intfns[i];
  }
  delete [] intfns;
}

void BloomFilter::insert(const std::string& value){
  uint64_t key;
  for(int i = 0; i < k; i++){
    key = intfns[i] -> hash(strfn -> hash(value));
    bits[key/64] |= (uint64_t(1) << (key % 64));
  }
}

bool BloomFilter::lookup(const std::string& value) const{
  for(int i=0; i<k; i++){
    uint64_t key;
    key = intfns[i] -> hash(strfn -> hash(value));
    if((bits[key/64] & (uint64_t(1) << (key % 64))) == 0){
      return false;
    }
  }
  return true;
}
