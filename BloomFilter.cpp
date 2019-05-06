#include "BloomFilter.h"
#include "IntegerHashes.h"
#include "StringHashes.h"
#include <cstdint>
#include <string>

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn){
  this->k = k;
  this->m = m;
  int arraySize;
  
  // not really sure why we divide by 64 ask kevin
  if(m%64 != 0){
    arraySize=m/64+1;
  }else{
    arraySize=m/64;
  }
  
  // initialize bit array
  bits = new uint64_6[arraySize];
  for(int i:bits){
    i=0;
  }
  
  // initialize intfns array
  intfns = new IntegerHash*[arraySize]
}

BloomFilter::~BloomFilter(){
  //code
}

void BloomFilter::insert(const std::string& value){
  //code
}

bool BloomFilter::lookup(const std::string& value) const{
  //code
}
