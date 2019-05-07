#include "HashSet.h"
#include "IntegerHashes.h"
#include "StringHashes.h"
#include <string>

HashSet::HashSet(){
  this->nitems = 0;
  this->nslots = 1000;
  intfn = new SquareRootHash(10, nslots);
  strfn = new JenkinsHash();
  slots = new std::string*[nslots];
  for (int i = 0; i < nslots; i++){
    slots[i] = NULL;
  }

}

HashSet::~HashSet(){
  for (int i = 0; i<nslots; i++){
    delete slots[i];
  }
  delete [] slots;
  delete intfn;
  delete strfn;
}

void HashSet::insert(const std::string& value){
  int key = strfn->hash(value);
  int index = intfn->hash(key);
  
  while(slots[index]!=NULL){
    index = (index+1) % nslots;
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

  while (slots[index] != NULL){
    if(*(slots[index]) == value){
      return true;
    }
    index = (index+1) % nslots;
  }
  return false;
}

void HashSet::rehash(){
  // creating new array for slots
  std::string** oldSlots = slots;
  slots = new std::string*[nslots*2];
  for(int i=0; i<nslots*2; i++){
    slots[i] = NULL;
  }

  // redefine SquareRootHash
  delete intfn;
  this->intfn = new SquareRootHash(10, nslots*2);
  
  // insert each element in slots into newSlots
  for(int i=0; i<nslots; i++){
    if(oldSlots[i] != NULL){
      int key = strfn->hash(*(oldSlots[i]));
      int index = intfn->hash(key);
      while (slots[index] != NULL){
	index=(index+1) % (nslots*2);
      }
      slots[index] = oldSlots[i];
    }
  }

  // delete unneeded array
  for(int i =0; i<nslots; i++){
    delete oldSlots[i];
  }
  delete [] slots;

  // update parameters
  nslots *= 2;
    
}
