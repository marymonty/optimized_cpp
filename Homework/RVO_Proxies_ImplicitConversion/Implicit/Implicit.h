//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//---------------------------------------------------------------------------- 

#ifndef IMPLICIT_H
#define IMPLICIT_H

// ------------------------------------------------------------------------
//   Modify This File - to generate Errors to prevent implicit conversions
// ------------------------------------------------------------------------

class Vect
{
public:
	Vect();
	Vect(const Vect &tmp);
	const Vect & operator = (const Vect &tmp);
	~Vect();

	Vect(const float inX, const float inY, const float inZ);

	void setX(const float inX);
	void setY(const float inY);
	void setZ(const float inZ);

	void set(const float inX, const float inY, const float inZ);

	float getX() const;
	float getY() const;
	float getZ() const;

	Vect operator + (const Vect tmp) const;


private:
	float x;
	float y;
	float z;
	template <typename T, typename U, typename V> Vect(const T inX, const U inY, const V inZ);
	template <typename T> void setX(const T inX) const;
	template <typename T> void setY(const T inY) const;
	template <typename T> void setZ(const T inT) const;
	template <typename T, typename U, typename V> void set(const T inX, const U inY, const V inZ);
};

#endif

// ---  End of File ---------------
