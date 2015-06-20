#ifndef VECTORS_HEADER_H
#define VECTORS_HEADER_H

class Vector{
	private:
		int startAnchor;
		int endAnchor;
	public:
		Vector(int first, int second){
			this->startAnchor = first;
			this->endAnchor = second;
		}

		int getStart(){
			return this->startAnchor;
		}

		int getSecond(){
			return this->endAnchor;
		}
};

#endif