#ifndef ENTITY_HEADER_H
#define ENTITY_HEADER_H
#include <vector>
#include <array>
#include <stdexcept>
#include <cmath>

#include "Point.h"
#include "Vector.h"

class Entity{
	private:
		std::vector< Point > points;

		std::vector< Vector > vectors;

		double centerPosition[ 3 ];

		double currentRotation[ 3 ];

	public:
	    Entity(){
            currentRotation[ 0 ] = 0.0;
            currentRotation[ 1 ] = 0.0;
            currentRotation[ 2 ] = 0.0;

            centerPosition[ 0 ] = 0.0;
            centerPosition[ 1 ] = 0.0;
            centerPosition[ 2 ] = 0.0;
	    }

	    std::vector< Point > & getPoints(){
            return this->points;
	    }

	    std::vector< Vector > & getVectors(){
            return this->vectors;
	    }

		int addPoint(double positionX, double positionY, double positionZ){
			Point newPoint(positionX, positionY, positionZ);

			this->points.push_back(newPoint);

			return newPoint.getUniqueID();
		}

		void addVector(int startPoint, int endPoint){
			bool startFound = false,
				endFound = false;

			for (std::vector<Point>::iterator it = this->points.begin(); it != this->points.end(); ++it) {
				if ( (*it).getUniqueID() == startPoint){
					startFound = true;
				}

				if ( (*it).getUniqueID() == endPoint){
					endFound = true;
				}
			}

			if (!startFound || !endFound){
				throw std::invalid_argument( "Invalid argument" );
			}

			Vector newVector( startPoint , endPoint );

			this->vectors.push_back(newVector);
		}

		void setOrigin(double ( &position )[ 3 ] ){
			centerPosition[0] = position[ 0 ];
			centerPosition[1] = position[ 1 ];
			centerPosition[2] = position[ 2 ];
		}

		void setRotation( double rotation[] ){
			this->currentRotation[ 0 ] = rotation[ 0 ];
			this->currentRotation[ 1 ] = rotation[ 1 ];
			this->currentRotation[ 2 ] = rotation[ 2 ];

            for( int iPosition = 0 ; iPosition < 3 ; iPosition++ ){
                while( this->currentRotation[ iPosition ] > 360 || this->currentRotation[ iPosition ] < 0 ){
                    if (this->currentRotation[ iPosition ] > 360){
                        this->currentRotation[ iPosition ] -= 360;
                    }

                    if (this->currentRotation[ iPosition ] < 0){
                        this->currentRotation[ iPosition ] = 360 + this->currentRotation[ iPosition ];
                    }
                }
            }
		}

		void getRotation( double ( &angles )[ 3 ] ){
		    angles[ 0 ] = this->currentRotation[ 0 ];
		    angles[ 1 ] = this->currentRotation[ 1 ];
		    angles[ 2 ] = this->currentRotation[ 2 ];
		}

		void getOrigin(double ( &origin )[ 3 ] ){
			origin[0] = this->centerPosition[0];
			origin[1] = this->centerPosition[1];
			origin[2] = this->centerPosition[2];
		}

		bool getPointOrigin( int uniqueID , double ( &origin )[ 3 ] ){
		    double positionX , positionY , positionZ;

            for (std::vector<Point>::iterator it = this->points.begin(); it != this->points.end(); ++it) {
				if ( (*it).getUniqueID() == uniqueID){

                    double pointPosition[ 3 ];

                    (*it).getPointOrigin( pointPosition );

                    positionX = pointPosition[ 0 ];
                    positionY = pointPosition[ 1 ];
                    positionZ = pointPosition[ 2 ];

                    double xMatrix[ 3 ][ 3 ] = {
                        {
                             1 , 0 , 0
                        },
                        {
                            0 , cos( this->currentRotation[ 0 ] ) , -sin( this->currentRotation[ 0 ] )
                        },
                        {
                            0 , sin( this->currentRotation[ 0 ] ) , cos( this->currentRotation[ 0 ] )
                        }
                    };

                    double yMatrix[ 3 ][ 3 ] = {
                        {
                             cos( this->currentRotation[ 1 ] ) , 0 , sin( this->currentRotation[ 1 ] )
                        },
                        {
                            0 , 1 , 0
                        },
                        {
                            -sin( this->currentRotation[ 1 ] ) , 0 , cos( this->currentRotation[ 1 ] )
                        }
                    };

                    double zMatrix[ 3 ][ 3 ] = {
                        {
                             cos( this->currentRotation[ 2 ] ) , -sin( this->currentRotation[ 2 ] ) , 0
                        },
                        {
                            sin( this->currentRotation[ 2 ] ) , cos( this->currentRotation[ 2 ] ) , 0
                        },
                        {
                            0 , 0 , 1
                        }
                    };

                    double tmpMatrix[ 3 ][ 3 ] = {
                        {
                            ( xMatrix[ 0 ][ 0 ] * yMatrix[ 0 ][ 0 ] ) + ( xMatrix[ 0 ][ 1 ] * yMatrix[ 1 ][ 0 ] ) + ( xMatrix[ 0 ][ 2 ] * yMatrix[ 2 ][ 0 ] ),
                            ( xMatrix[ 0 ][ 0 ] * yMatrix[ 0 ][ 1 ] ) + ( xMatrix[ 0 ][ 1 ] * yMatrix[ 1 ][ 1 ] ) + ( xMatrix[ 0 ][ 2 ] * yMatrix[ 2 ][ 1 ] ),
                            ( xMatrix[ 0 ][ 0 ] * yMatrix[ 0 ][ 2 ] ) + ( xMatrix[ 0 ][ 1 ] * yMatrix[ 1 ][ 2 ] ) + ( xMatrix[ 0 ][ 2 ] * yMatrix[ 2 ][ 2 ] )
                        },
                        {
                            ( xMatrix[ 1 ][ 0 ] * yMatrix[ 0 ][ 0 ] ) + ( xMatrix[ 1 ][ 1 ] * yMatrix[ 1 ][ 0 ] ) + ( xMatrix[ 1 ][ 2 ] * yMatrix[ 2 ][ 0 ] ),
                            ( xMatrix[ 1 ][ 0 ] * yMatrix[ 0 ][ 1 ] ) + ( xMatrix[ 1 ][ 1 ] * yMatrix[ 1 ][ 1 ] ) + ( xMatrix[ 1 ][ 2 ] * yMatrix[ 2 ][ 1 ] ),
                            ( xMatrix[ 1 ][ 0 ] * yMatrix[ 0 ][ 2 ] ) + ( xMatrix[ 1 ][ 1 ] * yMatrix[ 1 ][ 2 ] ) + ( xMatrix[ 1 ][ 2 ] * yMatrix[ 2 ][ 2 ] )
                        },
                        {
                            ( xMatrix[ 2 ][ 0 ] * yMatrix[ 0 ][ 0 ] ) + ( xMatrix[ 2 ][ 1 ] * yMatrix[ 1 ][ 0 ] ) + ( xMatrix[ 2 ][ 2 ] * yMatrix[ 2 ][ 0 ] ),
                            ( xMatrix[ 2 ][ 0 ] * yMatrix[ 0 ][ 1 ] ) + ( xMatrix[ 2 ][ 1 ] * yMatrix[ 1 ][ 1 ] ) + ( xMatrix[ 2 ][ 2 ] * yMatrix[ 2 ][ 1 ] ),
                            ( xMatrix[ 2 ][ 0 ] * yMatrix[ 0 ][ 2 ] ) + ( xMatrix[ 2 ][ 1 ] * yMatrix[ 1 ][ 2 ] ) + ( xMatrix[ 2 ][ 2 ] * yMatrix[ 2 ][ 2 ] )
                        }
                    };

                    double rotationMatrix[ 3 ][ 3 ] = {
                        {
                            ( tmpMatrix[ 0 ][ 0 ] * zMatrix[ 0 ][ 0 ] ) + ( tmpMatrix[ 0 ][ 1 ] * zMatrix[ 1 ][ 0 ] ) + ( tmpMatrix[ 0 ][ 2 ] * zMatrix[ 2 ][ 0 ] ),
                            ( tmpMatrix[ 0 ][ 0 ] * zMatrix[ 0 ][ 1 ] ) + ( tmpMatrix[ 0 ][ 1 ] * zMatrix[ 1 ][ 1 ] ) + ( tmpMatrix[ 0 ][ 2 ] * zMatrix[ 2 ][ 1 ] ),
                            ( tmpMatrix[ 0 ][ 0 ] * zMatrix[ 0 ][ 2 ] ) + ( tmpMatrix[ 0 ][ 1 ] * zMatrix[ 1 ][ 2 ] ) + ( tmpMatrix[ 0 ][ 2 ] * zMatrix[ 2 ][ 2 ] )
                        },
                        {
                            ( tmpMatrix[ 1 ][ 0 ] * zMatrix[ 0 ][ 0 ] ) + ( tmpMatrix[ 1 ][ 1 ] * zMatrix[ 1 ][ 0 ] ) + ( tmpMatrix[ 1 ][ 2 ] * zMatrix[ 2 ][ 0 ] ),
                            ( tmpMatrix[ 1 ][ 0 ] * zMatrix[ 0 ][ 1 ] ) + ( tmpMatrix[ 1 ][ 1 ] * zMatrix[ 1 ][ 1 ] ) + ( tmpMatrix[ 1 ][ 2 ] * zMatrix[ 2 ][ 1 ] ),
                            ( tmpMatrix[ 1 ][ 0 ] * zMatrix[ 0 ][ 2 ] ) + ( tmpMatrix[ 1 ][ 1 ] * zMatrix[ 1 ][ 2 ] ) + ( tmpMatrix[ 1 ][ 2 ] * zMatrix[ 2 ][ 2 ] )
                        },
                        {
                            ( tmpMatrix[ 2 ][ 0 ] * zMatrix[ 0 ][ 0 ] ) + ( tmpMatrix[ 2 ][ 1 ] * zMatrix[ 1 ][ 0 ] ) + ( tmpMatrix[ 2 ][ 2 ] * zMatrix[ 2 ][ 0 ] ),
                            ( tmpMatrix[ 2 ][ 0 ] * zMatrix[ 0 ][ 1 ] ) + ( tmpMatrix[ 2 ][ 1 ] * zMatrix[ 1 ][ 1 ] ) + ( tmpMatrix[ 2 ][ 2 ] * zMatrix[ 2 ][ 1 ] ),
                            ( tmpMatrix[ 2 ][ 0 ] * zMatrix[ 0 ][ 2 ] ) + ( tmpMatrix[ 2 ][ 1 ] * zMatrix[ 1 ][ 2 ] ) + ( tmpMatrix[ 2 ][ 2 ] * zMatrix[ 2 ][ 2 ] )
                        }
                    };

                    origin[ 0 ] = ( positionX * rotationMatrix[ 0 ][ 0 ] ) + ( positionY * rotationMatrix[ 0 ][ 1 ] ) + ( positionZ * rotationMatrix[ 0 ][ 2 ] );
                    origin[ 1 ] = ( positionX * rotationMatrix[ 1 ][ 0 ] ) + ( positionY * rotationMatrix[ 1 ][ 1 ] ) + ( positionZ * rotationMatrix[ 1 ][ 2 ] );
                    origin[ 2 ] = ( positionX * rotationMatrix[ 2 ][ 0 ] ) + ( positionY * rotationMatrix[ 2 ][ 1 ] ) + ( positionZ * rotationMatrix[ 2 ][ 2 ] );

                    origin[ 0 ] += this->centerPosition[ 0 ];
                    origin[ 1 ] += this->centerPosition[ 1 ];
                    origin[ 2 ] += this->centerPosition[ 2 ];

					return true;
				}
			}

            return false;
		}
};

#endif
