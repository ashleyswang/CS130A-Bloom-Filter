#include "HashSet.h"

#include "IntegerHashes.h"
#include "StringHashes.h"
#include <string>

HashSet::HashSet(){
  nitems = 0;
  nslots = 1000;
  intfn = new SquareRootHash(10, nslots);
  strfn = new JenkinsHash();
  slots = new std::string*[nslots];
  for (int i = 0; i< nslots; i++){
    slots[i] = NULL;
  }

}

HashSet::~HashSet(){
  delete [] slots;
  delete intfn;
  delete strfn;
}

void HashSet::insert(std::string& value){
  int key = strfn->hash(value);
  int index = intfn->hash(key);
  
  while(slots[index]!=NULL){
    index++;
  }
  //std::string* ptr =value;
  slots[index]=ptr;

  nitems++;

  if( ((double) nitems) / ((double) nslots) > 0.75){
    this->rehash();
  }

}
bool HashSet::lookup(const std::string& value) const{
  int key = strfn->hash(value);
  int index = intfn->hash(key);

  while (*(slots[index]) != value || slots[index] == NULL){
    if(slots[index]==NULL){
      return false;
    }
    else{
      index++;
    }
  }
  return true;
}


void HashSet::rehash(){
  int ogsize=nslots;
  nslots *=2;
  delete intfn;
  intfn = new SquareRootHash(10, nslots);
  std::string** newSlots = new std::string*[nslots];
  for(int i=0; i<ogsize; i++){
    
    
}


int main(){

  return 0;

}
