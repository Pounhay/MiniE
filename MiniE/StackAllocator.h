#pragma once
#include <cstdlib>
#include <cstdint>
#define KB 1024
#define MB 1024*1024
class StackAllocator {

public:
	typedef intptr_t U32;
	typedef intptr_t Marker;

	StackAllocator(U32 stackSize_bytes) {
		this->marker = (Marker)malloc(stackSize_bytes);
		this->currMarker = this->marker;
	}

	void* alloc(U32 size_bytes) {
		Marker temp = this->currMarker;
		this->currMarker += size_bytes;

		return (void*)temp;
	}

	Marker getMarker() {
		return this->currMarker;
	}

	void freeToMarker(Marker marker) {

		this->currMarker = marker;
	}

	void clear() {

		this->currMarker = this->marker;
	}

	~StackAllocator() {

		free((void*)this->marker);
	}

private:
	Marker marker;
	Marker currMarker;

};