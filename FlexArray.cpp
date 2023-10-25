#include "FlexArray.h"
#include <iostream> // Include necessary header for string operations
#include <sstream>  // Include header for stringstream
using namespace std;

FlexArray::FlexArray() {
	capacity_ = INITIALCAP;
	size_ = 0;
	headroom_ = (capacity_ - size_) / 2;
	tailroom_ = capacity_ - headroom_ - size_;

	arr_ = new int[capacity_]();
	// cout << "c1 " << headroom_  << " "  << tailroom_ << endl; //TODO: remove
}

FlexArray::FlexArray(const int* arr, int size) {
	size_ = size;
	capacity_ = LO_THRESHOLD * size;
	headroom_ = (capacity_ - size_) / 2;
	tailroom_ = capacity_ - headroom_ - size_;
	arr_ = new int[capacity_];

	// Center the contents
	int centerOffset = headroom_;
	std::memcpy(arr_ + centerOffset, arr, size * sizeof(int)); // Copy inputArr to the centered part
	// cout << "c2 " << printAll() << endl; //TODO: remove
}

FlexArray::~FlexArray() {
	delete[] arr_;
	arr_ = nullptr;
	size_ = 0;
	capacity_ = 0;
	headroom_ = 0;
	tailroom_ = 0;
}

FlexArray::FlexArray(const FlexArray& other) {
	capacity_ = other.capacity_;
	size_ = other.size_;
	headroom_ = other.headroom_;
	tailroom_ = other.tailroom_;

	arr_ = new int[capacity_];

	for (int i = 0; i < size_; i++) {
		arr_[headroom_ + i] = other.get(headroom_ + i);
	}
}

FlexArray& FlexArray::operator=(const FlexArray& other) {
	if (this == &other) return *this;

	delete[] arr_;

	capacity_ = other.getCapacity();
	size_ = other.getSize();
	headroom_ = other.getHeadroom();
	tailroom_ = other.getTailroom();

	arr_ = new int[capacity_];
	for (int i = 0; i < size_; i++) {
		arr_[headroom_ + i] = other.get(headroom_ + i);
	}

	return *this;
}

int FlexArray::getSize() const {
	return size_;
}

int FlexArray::getCapacity() const {
	return capacity_;
}

int FlexArray::getHeadroom() const {
	return headroom_;
}

int FlexArray::getTailroom() const {
	return tailroom_;
}

string FlexArray::print() const {
	std::stringstream ss;
	ss << "[";
	for (int i = 0; i < size_; i++) {
		ss << arr_[headroom_ + i];
		if (i != size_ - 1) {
			ss << ", ";
		}
	}
	ss << "]";
	return ss.str();
}

string FlexArray::printAll() const {
	std::stringstream ss;
	ss << "[";
	for (int i = 0; i < capacity_; i++) {
		if (i < headroom_ || i >= headroom_ + size_) {
			ss << "X";
		}
		else {
			ss << arr_[i];
		}
		if (i != capacity_ - 1) {
			ss << ", ";
		}
	}
	ss << "]";
	return ss.str();
}

int FlexArray::get(int i) const {

	// cout << "get " << printAll() << " " << headroom_ << " " << tailroom_ << endl; //TODO: remove
	if (i >= 0 && i < size_) {
		return arr_[headroom_ + i];
	}

	// TODO: handle the case of an out-of-bounds index differently.
	return -1;
}

bool FlexArray::set(int i, int v) {
	if (i >= 0 && i < size_) {
		arr_[headroom_ + i] = v;
		return true;
	}

	return false;
}

void FlexArray::push_back(int v) {
	// cout << "pb if " << tailroom_ << " " << headroom_ << endl; //TODO: remove
	if (tailroom_ > 0) {
		arr_[headroom_ + size_] = v;
		tailroom_--;
		size_++;
		// cout << "pb if " << this->printAll() << endl; //TODO: remove
	}
	else {
		int new_capacity = std::max(3 * (size_ + 1), 2 * capacity_); // LO_THRESHOLD = 3
		resize(new_capacity);
		push_back(v);
		// cout << "pb else" << this->printAll() << endl; //TODO: remove
	}
}

bool FlexArray::pop_back() {
	if (size_ > 0) {
		tailroom_++;
		size_--;
		return true;
	}

	return false;
}

void FlexArray::push_front(int v) {
	if (headroom_ > 0) {
		headroom_--;
		arr_[headroom_] = v;
		size_++;
	}
	else {
		int new_capacity = std::max(3 * (size_ + 1), 2 * capacity_); // LO_THRESHOLD = 3
		resize(new_capacity);
		push_front(v);
	}
}

bool FlexArray::pop_front() {
	if (size_ > 0) {
		headroom_++;
		size_--;
		return true;
	}

	return false;
}

bool FlexArray::insert(int i, int v) {

	if (i >= 0 && i <= size_) {
		if (size_ == 0) {
			// If empty, insert at center
			headroom_ = (capacity_ - 1) / 2;
			arr_[headroom_] = v;
			size_++;
			tailroom_ = capacity_ - headroom_ - size_;
		}
		else if (i == 0) {
			// Inserting at the beginning (push_front equivalent)
			push_front(v);
		}
		else if (i == size_) {
			// Inserting at the end (push_back equivalent)
			push_back(v);
		}
		else {

			// Inserting at a specific position
			int shift = (i <= size_ / 2) ? -1 : 1;
			if (shift < 0 && headroom_ > 0) {
				headroom_--;
				for (int j = 0; j < i; j++) {
					arr_[headroom_ + j] = arr_[headroom_ + j - shift];
				}
			}
			else if (shift > 0 && tailroom_ > 0) {
				tailroom_--;
				for (int j = i + 1; j < size_ + 1; j++) {
					arr_[headroom_ + j] = arr_[headroom_ + j - shift];
				}
			}
			else {
				int new_capacity = std::max(3 * (size_ + 1), 2 * capacity_); // LO_THRESHOLD = 3
				resize(new_capacity);
				insert(i, v);
				return true;
			}

			arr_[headroom_ + i] = v;
			size_++;
			// cout << "insert p3" << printAll() << endl; //TODO: remove
		}
		return true;
	}
	return false;
}

bool FlexArray::erase(int i) {
	if (i >= 0 && i < size_) {
		if (size_ == 1) {
			// If only one element, remove it and reset headroom/tailroom
			headroom_ = (capacity_ - size_) / 2;
			size_--;
			tailroom_ = capacity_ - headroom_ - size_;
		}
		else if (i == 0) {
			// Erasing the first element (pop_front equivalent)
			pop_front();
		}
		else if (i == size_ - 1) {
			// Erasing the last element (pop_back equivalent)
			pop_back();
		}
		else {

			int shift = (i < size_ / 2) ? 1 : -1;

			if (shift < 0) {
				for (int j = i; j < size_; j++) {
					arr_[headroom_ + j] = arr_[headroom_ + j - shift];
				}
				tailroom_--;
			}
			else {
				for (int j = i; j > 0; j--) {
					arr_[headroom_ + j] = arr_[headroom_ + j - shift];
				}
				headroom_++;
			}
			size_--;
		}

		/*
		int new_capacity = std::max(3 * size_, 2 * capacity_); // HI_THRESHOLD = 7
		if (new_capacity != capacity_) {
			resize(new_capacity);
		}
		*/

		return true;
	}
	return false;
}

void FlexArray::resize(int new_capacity) {
	int* new_arr = new int[new_capacity];
	int new_headroom = (new_capacity - size_) / 2;

	for (int i = 0; i < size_; i++) {
		new_arr[new_headroom + i] = arr_[headroom_ + i];
	}

	delete[] arr_;
	arr_ = new_arr;
	headroom_ = new_headroom;
	tailroom_ = new_headroom;
	capacity_ = new_capacity;
}