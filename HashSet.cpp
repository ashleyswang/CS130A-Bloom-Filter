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

void HashSet::insert(const std::string& value){
  int key = strfn->hash(value);
  int index = intfn->hash(key);
  
  while(slots[index]!=NULL){
    index++;
  }
  slots[index]=new std::string(value);

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
  // creating new array for slots
  std::string** newSlots = new std::string*[nslots*2];
  for(int i=0; i<nslots*2; i++){
    newSlots[i] = NULL;
  }

  // redefine SquareRootHash
  delete intfn;
  IntegerHash* intfn = new SquareRootHash(10, nslots);
  
  // insert each element in slots into newSlots
  for(int i=0; i<nslots; i++){
    if(slots[i] != NULL){
      int key = strfn->hash(*(slots[i]));
      int index = intfn->hash(key);
      while (newSlots[index] != NULL){
	index++;
      }
      newSlots[index] = slots[i];
    }
  }

  // delete unneeded array
  delete [] slots;

  // update parameters
  slots = newSlots;
  nslots *= 2;
    
}

/*
int main(){

  return 0;

}
*/
