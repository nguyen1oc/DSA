
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
  xt::xarray<int> shuffle_time;
 public:
  DataLoader(Dataset<DType, LType>* ptr_dataset, int batch_size,
             bool shuffle = true, bool drop_last = false): ptr_dataset(ptr_dataset), batch_size(batch_size), shuffle(shuffle), drop_last(drop_last), current_idx(0) {
    // TODO implement
    totalBatches = ptr_dataset -> len() / batch_size;
    if (!drop_last && (ptr_dataset -> len() % batch_size != 0)) totalBatches++; //fasle = gop
    shuffle_time = xt::arange<int>(0, ptr_dataset -> len() - 1); //true = k gop
    if (shuffle) xt::random::shuffle(shuffle_time);
  }
  virtual ~DataLoader() {
    // TODO implement

  }

  // TODO implement forech
  class Iterator {
   public:
    // TODO implement contructor
    Iterator(DataLoader<DType, LType>* loader = 0, int current_idx = 0){
      this -> loader = loader;
      this -> current_idx = current_idx;
    }

    Iterator& operator=(const Iterator& iterator) {
      // TODO implement
      loader = iterator.loader;
      current_idx = iterator.current_idx;
      return *this;
    }

    Iterator& operator++() {
      // TODO implement
      this -> current_idx++;
      return *this;
    }

    Iterator operator++(int) {
      // TODO implement
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }

    bool operator!=(const Iterator& other) const {
      // TODO implement
      return current_idx != other.current_idx;
    }

    Batch<DType, LType> operator*() const {
      // TODO implement
      //return Batch()
      unsigned int front = current_idx * loader -> batch_size;
      unsigned int rear = min(front + loader -> batch_size, static_cast<unsigned int>(loader -> ptr_dataset -> len()));
      xt::xarray<DType> data_batch = xt::xarray<DType>::from_shape({rear - front});
      xt::xarray<LType> label_batch = xt::xarray<LType>::from_shape({rear - front});
      for (unsigned int i = front; i < rear; i++){
        data_batch(i - front) = loader -> ptr_dataset -> getitem(i).getData()(0);
        label_batch(i - front) = loader -> ptr_dataset -> getitem(i).getLabel()(0);
        
      }
      return Batch<DType, LType>(data_batch, label_batch);
    }

   private:
    // TODO implement
    DataLoader<DType, LType>* loader;
    int current_idx;
  };

  Iterator begin() {
    // TODO implement
    return Iterator(this, 0);
  }

   Iterator end() {
    // TODO implement
    return Iterator(this, totalBatches); //why? -> for (batch: totalBatches)?
  }
};

#endif /* DATALOADER_H */
