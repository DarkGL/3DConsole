#include "Cuboid.h"

Cuboid::Cuboid( double width , double height , double length ){

    double widthPart = width / 2.0,
            heightPart = height / 2.0,
            lengthPart = length / 2.0;

    int firstPoint = this->addPoint( -( widthPart ) , -( heightPart ), -( lengthPart ) );

	int secondPoint = this->addPoint( widthPart,  -( heightPart ), -( lengthPart ) );

	int thirdPoint = this->addPoint( widthPart , -( heightPart ), lengthPart );

	int fourthPoint = this->addPoint( -( widthPart ) , -( heightPart ), lengthPart );

	int fifthPoint = this->addPoint( -( widthPart ) , heightPart, -( lengthPart ) );

	int sixthPoint = this->addPoint( widthPart , heightPart, -( lengthPart ) );

	int seventhPoint = this->addPoint( widthPart , heightPart, lengthPart );

	int eighthPoint = this->addPoint( -( widthPart ) , heightPart, lengthPart );

	this->addVector( firstPoint , secondPoint );
	this->addVector( firstPoint , fourthPoint );
	this->addVector( firstPoint , fifthPoint );

	this->addVector( secondPoint , thirdPoint );
	this->addVector( secondPoint , sixthPoint );

	this->addVector( thirdPoint , fourthPoint );
	this->addVector( thirdPoint , seventhPoint );

	this->addVector( fourthPoint , eighthPoint );

	this->addVector( fifthPoint , sixthPoint );
	this->addVector( fifthPoint , eighthPoint );

	this->addVector( sixthPoint , seventhPoint );

	this->addVector( seventhPoint , eighthPoint );
}
