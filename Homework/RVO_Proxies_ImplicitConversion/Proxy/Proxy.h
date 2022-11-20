//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef PROXY_H
#define PROXY_H

// Modify This File

class Vect2D
{
public:
	Vect2D(const Vect2D &tmp) = default;
	Vect2D &operator =( const Vect2D &tmp) = default;
	Vect2D() = default;
	~Vect2D() = default;

	Vect2D(const float inX, const float inY);

	void setX(const float inX);
	void setY(const float inY);
	void set(const float inX, const float inY);

	float getX() const;
	float getY() const;

	//-----------------------------------------------
	// Rules   this function cannot be inlined 
	//         or implemented directly
	//-----------------------------------------------
	//  Vect2D operator + (const Vect2D &tmp) const;
	//-----------------------------------------------


private:
	float x;
	float y;

	//-----------------------------------------------
	// Add friends here... if you want (hint)
	//-----------------------------------------------
	// substitutions fully implemented here, conversion implemented in cpp
	/*	V2V
	*		add one Vect2D object with another Vect2D object 
	*/
	struct V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;

		V2V(const Vect2D& t1, const Vect2D& t2)
			: v1(t1), v2(t2) {};

		//conversion operator
		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x, v1.y + v2.y);
		}
	};

	friend inline V2V operator + (const Vect2D& a1, const Vect2D& a2)
	{
		return V2V(a1, a2);
	};

	/*	V2V2V	(3)
	*		add one V2V object with a Vect2D object
	*/
	struct V2V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;
		const Vect2D& v3;

		V2V2V(const V2V& t1, const Vect2D& t2)
			: v1(t1.v1), v2(t1.v2), v3(t2) {};

		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x + v3.x, v1.y + v2.y + v3.y);
		}
	};

	friend inline V2V2V operator + (const V2V& a1, const Vect2D& a2)
	{
		return V2V2V(a1, a2);
	};

	/*	V2V2V2V		(4)
	*		add one V2V2V object with a Vect2D object
	*/
	struct V2V2V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;
		const Vect2D& v3;
		const Vect2D& v4;

		V2V2V2V(const V2V2V& t1, const Vect2D& t2)
			: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t2) {};

		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x + v3.x + v4.x, 
						v1.y + v2.y + v3.y + v4.y);
		}
	};

	friend inline V2V2V2V operator + (const V2V2V& a1, const Vect2D& a2)
	{
		return V2V2V2V(a1, a2);
	};

	/*	V2V2V2V2V		(5)
	*		add one V2V2V2V object with a Vect2D object
	*/
	struct V2V2V2V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;
		const Vect2D& v3;
		const Vect2D& v4;
		const Vect2D& v5;

		V2V2V2V2V(const V2V2V2V& t1, const Vect2D& t2)
			: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t1.v4), v5(t2) {};

		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x + v3.x + v4.x + v5.x,
				v1.y + v2.y + v3.y + v4.y + v5.y);
		}
	};

	friend inline V2V2V2V2V operator + (const V2V2V2V& a1, const Vect2D& a2)
	{
		return V2V2V2V2V(a1, a2);
	};

	/*	V2V2V2V2V2V		(6)
	*		add one V2V2V2V2V object with a Vect2D object
	*/
	struct V2V2V2V2V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;
		const Vect2D& v3;
		const Vect2D& v4;
		const Vect2D& v5;
		const Vect2D& v6;

		V2V2V2V2V2V(const V2V2V2V2V& t1, const Vect2D& t2)
			: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t1.v4), v5(t1.v5), v6(t2) {};

		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x + v3.x + v4.x + v5.x + v6.x,
				v1.y + v2.y + v3.y + v4.y + v5.y + v6.y);
		}
	};

	friend inline V2V2V2V2V2V operator + (const V2V2V2V2V& a1, const Vect2D& a2)
	{
		return V2V2V2V2V2V(a1, a2);
	};

	/*	V2V2V2V2V2V2V		(7)
	*		add one V2V2V2V2V2V object with a Vect2D object
	*/
	struct V2V2V2V2V2V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;
		const Vect2D& v3;
		const Vect2D& v4;
		const Vect2D& v5;
		const Vect2D& v6;
		const Vect2D& v7;

		V2V2V2V2V2V2V(const V2V2V2V2V2V& t1, const Vect2D& t2)
			: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t1.v4), v5(t1.v5), v6(t1.v6), v7(t2) {};

		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x + v3.x + v4.x + v5.x + v6.x + v7.x,
				v1.y + v2.y + v3.y + v4.y + v5.y + v6.y + v7.y);
		}
	};

	friend inline V2V2V2V2V2V2V operator + (const V2V2V2V2V2V& a1, const Vect2D& a2)
	{
		return V2V2V2V2V2V2V(a1, a2);
	};

	/*	V2V2V2V2V2V2V2V			(8)
	*		add one V2V2V2V2V2V2V object with a Vect2D object
	*/
	struct V2V2V2V2V2V2V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;
		const Vect2D& v3;
		const Vect2D& v4;
		const Vect2D& v5;
		const Vect2D& v6;
		const Vect2D& v7;
		const Vect2D& v8;

		V2V2V2V2V2V2V2V(const V2V2V2V2V2V2V& t1, const Vect2D& t2)
			: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t1.v4), 
			v5(t1.v5), v6(t1.v6), v7(t1.v7), v8(t2) {};

		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x + v3.x + v4.x + v5.x + v6.x + v7.x + v8.x,
				v1.y + v2.y + v3.y + v4.y + v5.y + v6.y + v7.y + v8.y);
		}
	};

	friend inline V2V2V2V2V2V2V2V operator + (const V2V2V2V2V2V2V& a1, const Vect2D& a2)
	{
		return V2V2V2V2V2V2V2V(a1, a2);
	};

	/*	V2V2V2V2V2V2V2V2V			(9)
	*		add one V2V2V2V2V2V2V2V object with a Vect2D object
	*/
	struct V2V2V2V2V2V2V2V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;
		const Vect2D& v3;
		const Vect2D& v4;
		const Vect2D& v5;
		const Vect2D& v6;
		const Vect2D& v7;
		const Vect2D& v8;
		const Vect2D& v9;

		V2V2V2V2V2V2V2V2V(const V2V2V2V2V2V2V2V& t1, const Vect2D& t2)
			: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t1.v4),
			v5(t1.v5), v6(t1.v6), v7(t1.v7), v8(t1.v8), v9(t2) {};

		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x + v3.x + v4.x + v5.x + v6.x + v7.x + v8.x + v9.x,
				v1.y + v2.y + v3.y + v4.y + v5.y + v6.y + v7.y + v8.y + v9.y);
		}
	};

	friend inline V2V2V2V2V2V2V2V2V operator + (const V2V2V2V2V2V2V2V& a1, const Vect2D& a2)
	{
		return V2V2V2V2V2V2V2V2V(a1, a2);
	};

	/*	V2V2V2V2V2V2V2V2V2V			(10)
	*		add one V2V2V2V2V2V2V2V2V object with a Vect2D object
	*/
	struct V2V2V2V2V2V2V2V2V2V
	{
		const Vect2D& v1;
		const Vect2D& v2;
		const Vect2D& v3;
		const Vect2D& v4;
		const Vect2D& v5;
		const Vect2D& v6;
		const Vect2D& v7;
		const Vect2D& v8;
		const Vect2D& v9;
		const Vect2D& v10;

		V2V2V2V2V2V2V2V2V2V(const V2V2V2V2V2V2V2V2V& t1, const Vect2D& t2)
			: v1(t1.v1), v2(t1.v2), v3(t1.v3), v4(t1.v4),
			v5(t1.v5), v6(t1.v6), v7(t1.v7), v8(t1.v8), v9(t1.v9), v10(t2) {};

		operator Vect2D()
		{
			return Vect2D(v1.x + v2.x + v3.x + v4.x + v5.x + v6.x + v7.x + v8.x + v9.x + v10.x,
				v1.y + v2.y + v3.y + v4.y + v5.y + v6.y + v7.y + v8.y + v9.y + v10.y);
		}
	};

	friend inline V2V2V2V2V2V2V2V2V2V operator + (const V2V2V2V2V2V2V2V2V& a1, const Vect2D& a2)
	{
		return V2V2V2V2V2V2V2V2V2V(a1, a2);
	};
};

#endif

// ---  End of File ---------------