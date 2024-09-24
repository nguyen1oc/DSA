
#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/dataset.h"
#include "ann/xtensor_lib.h"

using namespace std;

template <typename DType, typename LType>
class DataLoader {
 public:
 private:
  Dataset<DType, LType>* ptr_dataset;
  int batch_size;
  bool shuffle; //true = shuffle randon, false = not;
  bool drop_last;
  // TODO : add more member variables to support the iteration
  //CHUA BIET
  int totalBatches;//tong so batch
  int current_idx; //vi tri cua tung batch
 public:
  DataLoader(Dataset<DType, LType>* ptr_dataset, int batch_size,
             bool shuffle = true, bool drop_last = false): ptr_dataset(nullptr), batch_size(batch_size), shuffle(true), drop_last(drop_last), totalBatches(0), current_idx(0) {
    // TODO implement

  }
  virtual ~DataLoader() {
    // TODO implement

  }

  Iterator begin() {
    // TODO implement
    return Iterator(this, 0);
  }

  Iterator end() {
    // TODO implement
    return Iterator(this, totalBatches); //why? -> for (batch: totalBatches)?
  }

  // TODO implement forech
  class Iterator {
   public:
    // TODO implement contructor
    Iterator(DataLoader<DType, Ltype>* loader = 0, int current_idx = 0){
      this -> loader = loader;
      this -> current_idx = index;
    }

    Iterator& operator=(const Iterator& iterator) {
      // TODO implement
      this -> iterator = iterator.loader;
      this -> iterator = iterator.current_idx;
      return *this;
    }

    Iterator& operator++() {
      // TODO implement
      this -> current_idx++;
      reutrn *this;
    }

    Iterator operator++(int) {
      // TODO implement
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }

    bool operator!=(const Iterator& other) const {
      // TODO implement
      return current_idx != iterator.current_ix;
    }

    Batch<DType, LType> operator*() const {
      // TODO implement
      
    }

   private:
    // TODO implement
    DataLoader<Type, Ltype>* loader;
    int current_idx;
  };
};

#endif /* DATALOADER_H */
