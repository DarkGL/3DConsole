#ifndef POINT_HEADER_H
#define POINT_HEADER_H

class Point{
	private:
		static int UNIQUE_ID;

		double pointOrigin[3];

		int uniqueID;

	public:
		Point(double originX, double originY, double originZ){
			this->pointOrigin[0] = originX;
			this->pointOrigin[1] = originY;
			this->pointOrigin[2] = originZ;

			this->uniqueID = Point::UNIQUE_ID++;
		}

		void getPointOrigin( double ( &origin )[ 3 ] ){
			origin[0] = this->pointOrigin[0];
			origin[1] = this->pointOrigin[1];
			origin[2] = this->pointOrigin[2];
		}

		int getUniqueID(){
			return this->uniqueID;
		}
};

#endif
