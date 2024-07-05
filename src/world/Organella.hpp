#pragma once

class Life_Cell;

class Organella_I {
public:
	virtual void activate() = 0;
	virtual Organella_I* clone(Life_Cell*) = 0;
};

class Org_Chloroplast : public Organella_I{
private:
	Life_Cell* host;
public:
	Org_Chloroplast(Life_Cell* host);

	void activate();
	Organella_I* clone(Life_Cell*);
};