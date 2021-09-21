// File: points2.h
// Description: This class implements a "sequence" of coordinates (x, y) using C++14 semantics and the "big 5".
// (Copy Constructor, Copy Assignment Operator, Move Constructor, Move Assignment Operator and Destructor)
// Object member ReadPoints2() is implemented so that the user can input its own "sequence". 
// The user must first enter the size of the "sequence", followed by the coordinates (x, y).
// Example: 3 7 4 3 2 1 10
// 3 specifies number of points. Points are the pairs:
// (7, 4) (3, 2) and (1, 10).

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor. 
  // Set size to 0.
  Points2D(){size_ = 0;}

  // Copy-constructor.
  Points2D(const Points2D &rhs){
    if (rhs.size() == 0){ // if rhs has no sequence
      size_ = 0;
      sequence_ = nullptr;
    }
    else{ // if rhs has sequence
      size_ = rhs.size();
      sequence_ = new std::array<Object, 2>[size_]; // assigning the memory dynamically to copy
      std::copy(rhs.sequence_, rhs.sequence_ + rhs.size_, sequence_);
    }
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2D copy = rhs; 
  // std::swap(*this, copy);
  // return *this;
  // }
  Points2D& operator = (const Points2D &rhs){
    Points2D copy = rhs; 
    std::swap(*this, copy);
    return *this;
  }

  // Move-constructor. 
  Points2D(Points2D &&rhs) {
    size_ = rhs.size_;
    sequence_ = rhs.sequence_;
    rhs.size_ = 0;
    rhs.sequence_ = nullptr;
    // A new object is created such that it is the same as rhs. rhs is now set to nullptr
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2D& operator = (Points2D &&rhs){
    if (this != &rhs){
      std::swap(size_, rhs.size_);
      std::swap(sequence_, rhs.sequence_);
      // created such that lhs is the same as rhs
    }
    return *this;
  }

  // destructor
  ~Points2D(){
    delete[] sequence_;
    sequence_ = nullptr;
  }

  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item) {
    // Provide code.
    size_ = (item.size()/2); // dividing the item size by 2 since we have 2 points
    sequence_ = new std::array<Object, 2>[size_];
    sequence_[0] = item; // item assigned as the first element in the array
  }

  // Read a chain from standard input.
  void ReadPoints2D() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    // Add code here.
    sequence_ = new std::array<Object,2>[size_of_sequence];
    //reads the rest of the input line the user entered
    Object token;
    for (int i = 0 ;input_stream >> token; ++i) {
      // Read coordinates.
      // Fill sequence_ here.
      // inserting every pair of two items into the sequence_.
      sequence_[i][0] = token;
      input_stream >> token; // next element in token
      sequence_[i][1] = token;
      size_++; //incrementing the size
    }
  }


  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const { 
    if(location < 0 || location >= size_){
      std::cout<< "Out-of-range\n";
      abort();
    }
    else{
      return sequence_[location]; //to call a specific index
    }
  }

  //  @c1: A sequence.
  //  @c2: A second sequence.
  //  @return their sum. If the sequences are not of the same size, append the
  //    result with the remaining part of the larger sequence.
  friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
    // Code missing.
    // e.g.: c1 = () (1,2), (3,4), (5, 6) ), 
    // c2 = ((100, 200), (300, 400) ), 
    // c1 + c2 = () (101, 202), (303, 404), (5, 6) )
    Points2D<double> result; // creating a points2d template double type result
    if (c1.size() == c2.size()) {// if same size, allocating space and computing addition
      result.size_ = c2.size();
      result.sequence_ = new std::array<Object, 2>[result.size_];
      for (size_t i = 0; i < result.size(); i++) {
        // adding the sequences c1 & c2
        result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      }
    }else if (c1.size() > c2.size()) { // if c1 is the larger sequence
      result.size_ = c1.size();
      result.sequence_ = new std::array<Object, 2>[result.size_];
      for (size_t i = 0; i < c2.size(); i++) {
        // adding the sequences c1 & c2
        result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      }
      // appending the result with the remaining part of the larger sequence (c1).
      for (size_t i = c2.size(); i < result.size_; i++) {
        result.sequence_[i][0] = c1.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1];
      }
    }else { // c2 is the larger sequence
      result.size_ = c2.size();
      result.sequence_ = new std::array<Object, 2>[result.size_];
      for (size_t i = 0; i < c1.size(); i++) {
        // adding the sequences c1 & c2
        result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
        result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      }
      // appending the result with the remaining part of the larger sequence (c2).
      for (size_t i = c1.size(); i < result.size_; i++) {
        result.sequence_[i][0] = c2.sequence_[i][0];
        result.sequence_[i][1] = c2.sequence_[i][1];
      }
    }
    return result; 
  }


 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2) {
   // Code missing.
   // friend function of operator overloading with two parameters
   // Prints out the sequence in (x,y) form
   // post-condition
   // if (equal to 1 & not equal to null) using dynamic array sequence_ and array_
    if (some_points2.size_ == 1 && some_points2.sequence_ != nullptr) { // condition is true, printing sequence at I and II location
      std::cout << "(" << some_points2.sequence_->at(0) << ", " << some_points2.sequence_->at(1) << ") ";
    }
    // if (greater than 1 & not equal to null)
    if (some_points2.size_ > 1 && some_points2.sequence_ != nullptr) {
      for (size_t i = 0; i < some_points2.size(); i++) { // condition is true, for loop until the size of the array
        std::cout << "(" << some_points2.sequence_[i][0] << ", ";
        std::cout << some_points2.sequence_[i][1] << ") ";
      }
    }
    // if the array is null, print empty brackets
    if (some_points2.sequence_ == nullptr) {
      std::cout << "()";
    }
    return out;
 }
 
 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2D_H_
