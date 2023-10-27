#include "FlexArray.h"
#include <iostream>
#include <sstream>

using namespace std;

FlexArray::FlexArray() {
	set_instance_variables_(0, INITIALCAP);
	arr_ = new int[capacity_];
}

FlexArray::FlexArray(const int* arr, int size) {
	set_instance_variables_(size, LO_THRESHOLD * size);
	arr_ = new int[capacity_];

	// Center the contents and copy arr to the centered part
	std::memcpy(arr_ + headroom_, arr, size * sizeof(int));
}

FlexArray::~FlexArray() {
	delete[] arr_;

	// Reset the member variables
	set_instance_variables_(0, 0);
	arr_ = nullptr;
}

FlexArray::FlexArray(const FlexArray& other) {
	set_instance_variables_(other.getSize(), other.getCapacity());
	arr_ = new int[capacity_];

	for (int i = 0; i < size_; i++) {
		arr_[headroom_ + i] = other.get(i);
	}
}

FlexArray& FlexArray::operator=(const FlexArray& other) {
	if (this == &other) return *this;

	delete[] arr_;

	set_instance_variables_(other.getSize(), other.getCapacity());
	arr_ = new int[capacity_];

	for (int i = 0; i < size_; i++) {
		arr_[headroom_ + i] = other.get(i);
	}

	return *this;
}

int FlexArray::getSize() const {
	return size_;
}

int FlexArray::getCapacity() const {
	return capacity_;
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
		} else {
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

	// TODO: handle the case of an out-of-bounds index differently.
	return false;
}

void FlexArray::push_back(int v) {

	// If empty, treat it as new array
	if (size_ == 0) {
		update_head_n_tail_();
	}

	if (tailroom_ == 0) {
		resize_();
	}

	arr_[headroom_ + size_] = v;
	tailroom_--;
	size_++;

}

bool FlexArray::pop_back() {
	if (size_ == 0) {
		return false;
	}

	tailroom_++;
	size_--;

	if (capacity_ > HI_THRESHOLD * size_ && size_ > 0) {
		resize_();
	}

	return true;
}

void FlexArray::push_front(int v) {

	// If empty, treat it as new array
	if (size_ == 0) {
		update_head_n_tail_();
		headroom_++;
		tailroom_--;
	}

	if (headroom_ == 0) {
		resize_();
	}

	headroom_--;
	arr_[headroom_] = v;
	size_++;
}

bool FlexArray::pop_front() {
	if (size_ == 0) {
		return false;
	}

	headroom_++;
	size_--;

	if (capacity_ > HI_THRESHOLD * size_ && size_ > 0) {
		resize_();
	}

	return true;
}

bool FlexArray::insert(int i, int v) {

	if (i >= 0 && i <= size_) {

		if (size_ == capacity_) {
			resize_();
		}

		// If empty, insert at center
		if (size_ == 0) {
			update_head_n_tail_();
			headroom_--;
			size_++;
			arr_[headroom_] = v;
			return true;
		}

		// Inserting at the beginning (push_front equivalent)
		if (i == 0 && headroom_ != 0) {
			push_front(v);
			return true;
		}

		// Inserting at the end (push_back equivalent)
		if (i == size_ && tailroom_ != 0) {
			push_back(v);
			return true;
		}

		// Inserting at a specific position
		int shiftHeadRoom = (i <= (size_ - 1) / 2.0);

		if ((shiftHeadRoom || tailroom_ == 0) && headroom_ > 0) {
			headroom_--;
			for (int j = 0; j < i; j++) {
				arr_[headroom_ + j] = arr_[headroom_ + j + 1];
			}
		} else {
			tailroom_--;
			for (int j = size_; j >= i + 1; j--) {
				arr_[headroom_ + j] = arr_[headroom_ + j - 1];
			}
		}

		arr_[headroom_ + i] = v;
		size_++;

		return true;
	}
	return false;
}

bool FlexArray::erase(int i) {
	if (i >= 0 && i < size_) {

		// Erasing the first element (pop_front equivalent)
		if (i == 0) {
			return pop_front();
		}

		// Erasing the last element (pop_back equivalent)
		if (i == size_ - 1) {
			return pop_back();
		}

		// If only one element, remove it and reset headroom/tailroom
		if (size_ == 1) {
			size_--;
			update_head_n_tail_();
			return true;
		}

		bool shiftHeadRoom = (i < (size_ - 1) / 2.0);

		if (shiftHeadRoom) {
			for (int j = i; j > 0; j--) {
				arr_[headroom_ + j] = arr_[headroom_ + j - 1];
			}
			headroom_++;
		} else {
			for (int j = i; j < size_; j++) {
				arr_[headroom_ + j] = arr_[headroom_ + j + 1];
			}
			tailroom_--;
		}

		size_--;
		if (capacity_ > HI_THRESHOLD * size_ && size_ > 0) {
			resize_();
		}

		return true;
	}
	return false;
}

void FlexArray::resize_() {

	int new_capacity = LO_THRESHOLD * size_; // LO_THRESHOLD = 3

	int* new_arr = new int[new_capacity];
	int new_headroom = (new_capacity - size_) / 2;

	for (int i = 0; i < size_; i++) {
		new_arr[new_headroom + i] = arr_[headroom_ + i];
	}

	delete[] arr_;

	set_instance_variables_(size_, new_capacity);
	arr_ = new_arr;
}

void FlexArray::set_instance_variables_(int size, int capacity) {
	size_ = size;
	capacity_ = capacity;
	update_head_n_tail_();
}

void FlexArray::update_head_n_tail_() {
	headroom_ = (capacity_ - size_) / 2;
	tailroom_ = capacity_ - headroom_ - size_;
}
