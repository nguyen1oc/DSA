
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
  xt::xarray<int> shuffle_time = xt::arange(ptr_dataset -> len());
  //XArrayList<Batch<DType, LType>> batch;
 public:
  DataLoader(Dataset<DType, LType>* ptr_dataset, int batch_size,
             bool shuffle = true, bool drop_last = false): ptr_dataset(ptr_dataset), batch_size(batch_size), shuffle(shuffle), drop_last(drop_last), current_idx(0) {
    // TODO implement
    if (ptr_dataset -> len() < batch_size && drop_last == false) totalBatches = 1;
    else totalBatches = (ptr_dataset -> len()) / batch_size;
    //temp = totalBatches;
    if (shuffle == true) xt::random::shuffle(shuffle_time);
    if (drop_last == true) return;
    //batch = XArrayList<Batch<DType, LType>>(nullptr, 0 , totalBatches);
    //for(i:totalbatch)
    //xt::array<DType> data
    //batch.add(Batch<DType, LType>(batch_data, batch_label))
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

    if (loader -> drop_last == false && current_idx == loader -> totalBatches - 1 && loader -> ptr_dataset->len() % loader -> batch_size != 0 ){
      rear += loader -> ptr_dataset -> len() % loader -> batch_size;
    }
    //std::cout <<"Front: " << front << ", Rear: " << rear << ", Temp: " << loader->temp << ", totalBatch: "<< loader ->totalBatches<< std::endl;
    if (rear > loader -> ptr_dataset -> len()) rear = loader -> ptr_dataset -> len();

    auto data_shape = loader -> ptr_dataset -> get_data_shape();
    auto label_shape = loader -> ptr_dataset -> get_label_shape();
    data_shape[0] = rear - front;
    label_shape[0] = rear - front;

    xt::xarray<DType> data_batch = xt::xarray<DType>::from_shape(data_shape);
    xt::xarray<LType> label_batch = xt::xarray<LType>::from_shape(label_shape);

    for (unsigned int i = front; i < rear; ++i) {
        xt::xarray<DType> dataItem = loader->ptr_dataset->getitem(i).getData();
        xt::xarray<LType> labelItem = loader->ptr_dataset->getitem(i).getLabel();
        //std::cout << "Batch Index: " << current_idx << ", Front: " << front << ", Rear: " << rear << ", Temp: " << loader->temp << std::endl;

        xt::view(data_batch, i - front) = dataItem;
        xt::view(label_batch, i - front) = labelItem;
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
