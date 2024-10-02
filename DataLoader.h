
#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/dataset.h"
#include "ann/xtensor_lib.h"
//#include "list/listheader.h"

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
  //int temp;
  int current_idx; //vi tri cua tung batch
  xt::xarray<int> shuffle_array = xt::arange<int>(ptr_dataset -> len());;
 public:
  DataLoader(Dataset<DType, LType>* ptr_dataset, int batch_size,
             bool shuffle = true, bool drop_last = false): ptr_dataset(ptr_dataset), batch_size(batch_size), shuffle(shuffle), drop_last(drop_last), current_idx(0) {
    // TODO implement
    if (ptr_dataset -> len() < batch_size && drop_last == false) totalBatches = 1;
    else totalBatches = (ptr_dataset -> len()) / batch_size;

    if (drop_last == true && ptr_dataset -> len() < batch_size){
     totalBatches = 0;
     return;
    }
    //temp = totalBatches;
    if (shuffle == true){ 
      xt::random::default_engine_type engine(0);
      xt::random::shuffle(shuffle_array, engine);
    }
    //-----------------------------------------------------
    // cout << "Shuffle Time: ";
    // for(int i = 0; i < shuffle_array.size(); ++i) {
    //   cout << shuffle_array(i) << " ";
    // }
    //   cout << endl;
    //------------------------------------------------------
  }
  virtual ~DataLoader(){
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

    Iterator& operator=(const Iterator& iterator){
      // TODO implement
      loader = iterator.loader;
      current_idx = iterator.current_idx;
      return *this;
    }

    Iterator& operator++(){
      // TODO implement
      this -> current_idx++;
      return *this;
    }

    Iterator operator++(int){
      // TODO implement
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }

    bool operator!=(const Iterator& other) const{
      // TODO implement
      return current_idx != other.current_idx;
    }

    Batch<DType, LType> operator*() const{
    //loader -> temp = loader -> totalBatches;
    unsigned int front = current_idx * loader -> batch_size;
    unsigned int rear = front + loader -> batch_size;

    //ktra drop last, phai batch cuoi hay ko, va co du k
    if (loader -> drop_last == false && current_idx == loader -> totalBatches - 1 && loader -> ptr_dataset->len() % loader -> batch_size != 0 ){
      rear += loader -> ptr_dataset -> len() % loader -> batch_size;
    }
    //cout <<"Front: " << front << ", Rear: " << rear << ", Temp: " << loader->temp << ", totalBatch: "<< loader ->totalBatches<< std::endl;
    if (rear > loader -> ptr_dataset -> len()) rear = loader -> ptr_dataset -> len();

    xt::svector<unsigned long> data_shape = loader -> ptr_dataset -> get_data_shape();
    data_shape[0] = rear - front;
    xt::svector<unsigned long> label_shape = loader -> ptr_dataset -> get_label_shape();;
    if (label_shape.size() != 0){
      label_shape[0] = rear - front;
    }
    
    xt::xarray<DType> data_batch = xt::xarray<DType>::from_shape(data_shape);
    xt::xarray<LType> label_batch;
    if (label_shape.size() != 0){
      label_batch = xt::xarray<LType>::from_shape(label_shape);
    } 

    //cout<<"Its here!";
    for (unsigned int i = front; i < rear; ++i){
      unsigned int after_shuffle = loader->shuffle_array(i);

      //------------------------------------------------------
      // cout << "Shuffle Time: ";
      // for(int i = 0; i < loader -> shuffle_array.size(); ++i) {
      //   cout << loader -> shuffle_array(i) << " ";
      // }
      // cout << endl;
      //------------------------------------------------------

      xt::xarray<DType> dataItem = loader -> ptr_dataset->getitem(after_shuffle).getData();
      xt::view(data_batch, i - front) = dataItem;

      xt::xarray<LType> labelItem = loader -> ptr_dataset->getitem(after_shuffle).getLabel();
      if (label_shape.size() != 0){
        xt::view(label_batch, i - front) = labelItem;
      }
      //std::cout << "Batch Index: " << current_idx << ", Front: " << front << ", Rear: " << rear << ", Temp: " << loader->temp << std::endl;
    }
    //loader->temp -= 1; // Giảm temp
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
