#include <iostream>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
//#include <chrono>
//#include <thread>

#include "Canvas.h"
#include "Entity.h"
#include "Cuboid.h"

using namespace std;

/*int iVectorSort[ 12 ];

void sortVectors( int iPointPos[ 8 ][ 3 ] ){
	int iPointsPosTmp[ 8 ][ 4 ];

	for( int i = 0 ; i < 8 ; i++ ){objectOrigin
		iPointsPosTmp[ i ][ 0 ]	=	iPointPos[ i ][ 0 ];
		iPointsPosTmp[ i ][ 1 ]	=	iPointPos[ i ][ 1 ];
		iPointsPosTmp[ i ][ 2 ]	=	iPointPos[ i ][ 2 ];

		iPointsPosTmp[ i ][ 3 ]	=	i;
	}

	bool bChanged	=	false;
	int iTmp[ 4 ];

	do {
		bChanged	=	false;
		for( int i = 0 ; i < 7 ; i++ ){
			if( iPointsPosTmp[ i + 1 ][ 2 ]	> iPointsPosTmp[ i ][ 2 ] ){
				iTmp[ 0 ]	=	iPointsPosTmp[ i + 1 ][ 0 ];
				iTmp[ 1 ]	=	iPointsPosTmp[ i + 1 ][ 1 ];
				iTmp[ 2 ]	=	iPointsPosTmp[ i + 1 ][ 2 ];

				iTmp[ 3 ]	=	iPointsPosTmp[ i + 1 ][ 3 ];

				iPointsPosTmp[ i + +1 ][ 0 ]	=	iPointsPosTmp[ i ][ 0 ];
				iPointsPosTmp[ i + 1 ][ 1 ]	=	iPointsPosTmp[ i ][ 1 ];
				iPointsPosTmp[ i + 1 ][ 2 ]	=	iPointsPosTmp[ i ][ 2 ];

				iPointsPosTmp[ i + 1 ][ 3 ]	=	iPointsPosTmp[ i ][ 3 ];

				iPointsPosTmp[ i ][ 0 ]	=	iTmp[ 0 ];
				iPointsPosTmp[ i ][ 1 ]	=	iTmp[ 1 ];
				iPointsPosTmp[ i ][ 2 ]	=	iTmp[ 2 ];

				iPointsPosTmp[ i ][ 3 ]	=	iTmp[ 3 ];

				bChanged	=	true;
			}
		}
	} while( bChanged );

	int j	=	0;

	for( int i = 0 ; i < 8 ; i++ ){
		for( int k = 0 ; k < 12 ; k++ ){
			if( iPointsPosTmp[ i ][ 3 ]	==	iPointsVectors[ k ][ 0 ] ){
				iVectorSort[ j++ ]	=	k ;
			}
		}
	}

}

void createVectors( Canvas & canvas , int iPointPos[8][3]){
	int vVecPoints[ 2 ];
	int vVecSec[ 2 ];

	for( int i = 0 ; i < 12 ; i++ ){
		vVecPoints[ 0 ]	=	iPointPos[ iPointsVectors[ iVectorSort[ i ] ][ 1 ]][ 0 ] - iPointPos[ iPointsVectors[ iVectorSort[ i ] ][ 0 ]][ 0 ];
		vVecPoints[ 1 ]	=	iPointPos[ iPointsVectors[ iVectorSort[ i ] ][ 1 ]][ 1 ] - iPointPos[ iPointsVectors[ iVectorSort[ i ] ][ 0 ]][ 1 ];

		vVecSec[ 0 ]	=	0;
		vVecSec[ 1 ]	=	-iPointPos[ iPointsVectors[ iVectorSort[ i ] ][ 0 ]][ 1 ];

		double fAngle	=	( (double)vVecPoints[ objectOrigin0 ] * (double)vVecSec[ 0 ] + (double)vVecPoints[ 1 ] * (double)vVecSec[ 1 ] ) / ( sqrt( (double)vVecPoints[ 0 ] * (double)vVecPoints[ 0 ] + (double)vVecPoints[ 1 ] * (double)vVecPoints[ 1 ] ) * sqrt( (double)vVecSec[ 0 ] * (double)vVecSec[ 0 ] + (double)vVecSec[ 1 ] * (double)vVecSec[ 1 ] ) ) ;

		fAngle	=	min( fAngle , 1.0 );
		fAngle	=	max( -1.0 , fAngle );

		fAngle	=	acos( fAngle );

		printf( "%0.2f | %i | %i | %i | %i\n" , fAngle , vVecPoints[ 0 ] , vVecPoints[ 1 ] , vVecSec[ 0 ] , vVecSec[ 1 ] );

		char cChar =	'|';

		canvas.setPoint( iPointPos[iPointsVectors[iVectorSort[i]][0]][0] , iPointPos[iPointsVectors[iVectorSort[i]][0]][1] , iPointPos[iPointsVectors[iVectorSort[i]][0]][2] , '*' );
		canvas.setPoint( iPointPos[iPointsVectors[iVectorSort[i]][1]][0] , iPointPos[iPointsVectors[iVectorSort[i]][1]][1] , iPointPos[iPointsVectors[iVectorSort[i]][1]][2] , '*' );

		if( iPointPos[ iPointsVectors[ iVectorSort[ i ] ][ 0 ]][ 2 ] == iPointPos[ iPointsVectors[ iVectorSort[ i ] ][ 1 ]][ 2 ] )	continue;

	}
}*/

int main(){
	Canvas canvas( 40 , 40 , 40  );

	Cuboid firstObject( 20 , 20 , 20 );

	double objectOrigin[ 3 ] = { 20.0 , 20.0 , 20.0 };

	firstObject.setOrigin( objectOrigin );

	while( true ){
		canvas.clear();

		canvas.print( firstObject );

        if( kbhit() != 0 ){
            int keyCode = getch();

            if( keyCode != 72 && keyCode != 75 && keyCode != 80 && keyCode != 77 ){
                continue;
            }

            double angles[ 3 ];

            firstObject.getRotation( angles );

            if( keyCode == 72 ){//up
                angles[ 1 ] += 0.05;
            }
            else if( keyCode == 75 ){//left
                angles[ 0 ] += 0.05;
            }
            else if( keyCode == 80 ){//down
                angles[ 1 ] -= 0.05;
            }
            else if( keyCode == 77 ){//right
                angles[ 0 ] -= 0.05;
            }

            firstObject.setRotation( angles );
        }

        //std::this_thread::sleep_for(std::chrono::milliseconds( 100 ));
        Sleep( 50 );
	}

	exit( 0 );
}
