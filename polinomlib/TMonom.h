#pragma once
struct TMonom
{
	double coef; // коэффициент монома
	int index; // индекс (свертка степеней)


	TMonom() 
	{ 
		coef = 0;
		index = 0;
	}

	TMonom(double _coef, int degX, int degY, int degZ)
	{
		coef = _coef;
		index = 100 * degX + 10 * degY + degZ;
	}

	void SetCoef(int cval) { coef = cval; }
	int GetCoef(void) { return coef; }

	void SetIndex(int ival) { index = ival; }
	int GetIndex(void) { return index; }


	bool operator==(const TMonom& other) {
		if ((other.coef == this->coef) && (other.index == this->index))
			return true;
		else
			return false;
	}
	
	bool operator>(const TMonom& other) {
		if ((other.coef > this->coef) && (other.index > this->index))
			return true;
		else
			return false;
	}

	bool operator<(const TMonom& other) {
		if ((other.coef < this->coef) && (other.index < this->index))
			return true;
		else
			return false;
	}


};