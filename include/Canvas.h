#ifndef CANVAS_HEADER_H
#define CANVAS_HEADER_H

#include <vector>
#include <iostream>
#include <string>

#include "Cuboid.h"
#include "Point.h"
#include "Vector.h"

class Canvas{
	private:
		std::vector< std::vector< std::vector< char > > > currentCanvas;

		int sizeX,
			sizeY,
			sizeZ;

	public:
		Canvas(int sizeX, int sizeY, int sizeZ){
			this -> sizeX = sizeX;
			this -> sizeY = sizeY;
			this -> sizeZ = sizeZ;

			this -> currentCanvas.resize(sizeX );

			for (int iPositionX = 0; iPositionX < sizeX; iPositionX++){
				this -> currentCanvas[ iPositionX ].resize( sizeY );

				for (int iPositionY = 0; iPositionY < sizeY; iPositionY++){
					this->currentCanvas[iPositionX][iPositionY].resize(sizeZ);
				}
			}
		}

		void print( Cuboid & object ){

            std::vector< Point > pointsObject = object.getPoints();
            std::vector< Vector > vectorsObject = object.getVectors();

            for (std::vector<Point>::iterator it = pointsObject.begin(); it != pointsObject.end(); ++it) {
                int uniqueId = (*it).getUniqueID();

                double originPoint[ 3 ];

                object.getPointOrigin( uniqueId , originPoint );

                this->setPoint( round( originPoint[ 0 ] ) , round( originPoint[ 1 ] ) , round( originPoint[ 2 ] ) , '*' );

                for (std::vector<Vector>::iterator it = vectorsObject.begin(); it != vectorsObject.end(); ++it) {
                    if( ( *it ).getStart() == uniqueId ){

                        double originEnd[ 3 ],
                                vectorOrigin[ 3 ];

                        object.getPointOrigin(  (*it ).getSecond() , originEnd );

                        vectorOrigin[ 0 ] = originEnd[ 0 ] - originPoint[ 0 ];
                        vectorOrigin[ 1 ] = originEnd[ 1 ] - originPoint[ 1 ];
                        vectorOrigin[ 2 ] = originEnd[ 2 ] - originPoint[ 2 ];

                        double lengthVector = sqrt( ( vectorOrigin[ 0 ] * vectorOrigin[ 0 ] ) + ( vectorOrigin[ 1 ] * vectorOrigin[ 1 ] ) + ( vectorOrigin[ 2 ] * vectorOrigin[ 2 ] ) ) ;

                        vectorOrigin[ 0 ] /= lengthVector;
                        vectorOrigin[ 1 ] /= lengthVector;
                        vectorOrigin[ 2 ] /= lengthVector;

                        double currentLength = 0.0;

                        double newPosition[ 3 ];

                        newPosition[ 0 ] = originPoint[ 0 ];
                        newPosition[ 1 ] = originPoint[ 1 ];
                        newPosition[ 2 ] = originPoint[ 2 ];

                        for( ; currentLength < lengthVector ; ){

                            int newPositionX , newPositionY , newPositionZ;

                            newPosition[ 0 ] += vectorOrigin[ 0 ];
                            newPosition[ 1 ] += vectorOrigin[ 1 ];
                            newPosition[ 2 ] += vectorOrigin[ 2 ];

                            newPositionX = round( newPosition [ 0 ] );
                            newPositionY = round( newPosition [ 1 ] );
                            newPositionZ = round( newPosition [ 2 ] );

                            if( this->getPoint( newPositionX , newPositionY , newPositionZ ) == ' ' ){
                                this->setPoint( newPositionX , newPositionY , newPositionZ , '-' );
                            }

                            currentLength += 1.0;
                        }
                    }
                }
            }

            this -> clearConsole();

			char cPrint = ' ';

            std::string printString;

			for (int iPositionX = 0; iPositionX < this->sizeX; iPositionX++){
				for (int iPositionY = this->sizeY - 1; iPositionY >= 0; iPositionY--){
					cPrint = ' ';
					for (int iPositionZ = 0; iPositionZ < this->sizeZ; iPositionZ++){
						if (this->currentCanvas[iPositionX][iPositionY][iPositionZ] != ' '){
							cPrint = this->currentCanvas[iPositionX][iPositionY][iPositionZ];
							break;
						}
					}

					printString += cPrint;
				}

				printString += '\n';
			}

			std::cout << printString << std::endl;
		}

		void clear(){
			for (int iPositionX = 0; iPositionX < this -> sizeX; iPositionX++){
				for (int iPositionY = 0; iPositionY < this -> sizeY; iPositionY++){
					for (int iPositionZ = 0; iPositionZ < this -> sizeZ; iPositionZ++){
						this->currentCanvas[iPositionX][iPositionY][iPositionZ] = ' ';
					}
				}
			}
		}

		void setPoint(int positionX, int positionY, int positionZ, char character){
			if (positionX < 0 || positionY < 0 || positionZ < 0){
				return;
			}

			if (positionX >= this->sizeX || positionY >= this->sizeY || positionZ >= this->sizeZ ){
				return;
			}

			this->currentCanvas[positionX][positionY][positionZ] = character;
		}


		char getPoint(int positionX, int positionY, int positionZ){
			if (positionX < 0 || positionY < 0 || positionZ < 0){
				return ' ';
			}

			if (positionX >= this->sizeX || positionY >= this->sizeY || positionZ >= this->sizeZ ){
				return ' ';
			}

			return this->currentCanvas[positionX][positionY][positionZ];
		}

		void clearConsole(){
			system("cls");
		}
};

#endif
