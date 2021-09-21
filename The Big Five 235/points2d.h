#ifndef POINTS2D_H_
#define POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {


template<typename Object>
class Points2D {
 public:

  Points2D(){size_ = 0;}

  // Copy-constructor.
  Points2D(const Points2D &rhs){
    if (rhs.size() == 0){ 
      size_ = 0;
      sequence_ = nullptr;
    }
    else{ 
      size_ = rhs.size();
      sequence_ = new std::array<Object, 2>[size_]; 
      std::copy(rhs.sequence_, rhs.sequence_ + rhs.size_, sequence_);
    }
  }

  Points2D& operator = (const Points2D &rhs){
    Points2D copy = rhs; 
    std::swap(*this, copy);
    return *this;
  }


  Points2D(Points2D &&rhs) {
    size_ = rhs.size_;
    sequence_ = rhs.sequence_;
    rhs.size_ = 0;
    rhs.sequence_ = nullptr;

  }


  Points2D& operator = (Points2D &&rhs){
    if (this != &rhs){
      std::swap(size_, rhs.size_);
      std::swap(sequence_, rhs.sequence_);
    
    }
    return *this;
  }


  ~Points2D(){
    delete[] sequence_;
    sequence_ = nullptr;
  }




  Points2D(const std::array<Object, 2>& item) {
  
    size_ = (item.size()/2); 
    sequence_ = new std::array<Object, 2>[size_];
    sequence_[0] = item;
  }

  
  void ReadPoints2D() {
    
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    
    int size_of_sequence;
    input_stream >> size_of_sequence;
   
    sequence_ = new std::array<Object,2>[size_of_sequence];
    
    Object token;
    for (int i = 0 ;input_stream >> token; ++i) {
     
      sequence_[i][0] = token;
      input_stream >> token; 
      sequence_[i][1] = token;
      size_++; 
    }
  }


  size_t size() const {
    return size_;
  }


  const std::array<Object, 2>& operator[](size_t location) const { 
    if(location < 0 || location >= size_){
      std::cout<< "Out-of-range\n";
      abort();
    }
    else{
      return sequence_[location]; 
    }
  }


  friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
   
    Points2D<double> result; 
    if (c1.size() == c2.size()) {
      result.size_ = c2.size();
      result.sequence_ = new std::array<Object, 2>[result.size_];
      for (size_t i = 0; i < result.size(); i++) {
        
        result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      }
    }else if (c1.size() > c2.size()) { 
      result.size_ = c1.size();
      result.sequence_ = new std::array<Object, 2>[result.size_];
      for (size_t i = 0; i < c2.size(); i++) {
       
        result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      }
     
      for (size_t i = c2.size(); i < result.size_; i++) {
        result.sequence_[i][0] = c1.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1];
      }
    }else { 
      result.size_ = c2.size();
      result.sequence_ = new std::array<Object, 2>[result.size_];
      for (size_t i = 0; i < c1.size(); i++) {
        
        result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      }
      
      for (size_t i = c1.size(); i < result.size_; i++) {
        result.sequence_[i][0] = c2.sequence_[i][0];
        result.sequence_[i][1] = c2.sequence_[i][1];
      }
    }
    return result; 
  }


 
 friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2) {

    if (some_points2.size_ == 1 && some_points2.sequence_ != nullptr) { 
      std::cout << "(" << some_points2.sequence_->at(0) << ", " << some_points2.sequence_->at(1) << ") ";
    }
    
    if (some_points2.size_ > 1 && some_points2.sequence_ != nullptr) {
      for (size_t i = 0; i < some_points2.size(); i++) { 
        std::cout << "(" << some_points2.sequence_[i][0] << ", ";
        std::cout << some_points2.sequence_[i][1] << ") ";
      }
    }
    if (some_points2.sequence_ == nullptr) {
      std::cout << "()";
    }
    return out;
 }
 
 private:
  
  std::array<Object, 2> *sequence_;
 
  size_t size_;

};

}  
#endif 
