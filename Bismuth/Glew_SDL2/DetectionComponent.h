#pragma once



class DetectionComponent
{
public :
    enum Shape {CUBE, SPHERE, RAY, PLANE};
   
	virtual Shape getShape() const = 0;

};
