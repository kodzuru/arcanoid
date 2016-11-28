#pragma once

class Brick
{
public:
	short raw, col, hit; //координаты сетки блоков и прочность
	float w, h; //ширина и высота блока	
	bool active; // станет false после того как мяч заденет блок
	Brick();
	Brick(short, short, float, float, short);
	~Brick();

private:

};
Brick::Brick() : raw(), col(), w(20), h(20), hit(1), active(false) {
}
Brick::Brick(short r_, short c_, float w_, float h_, short hit_):
	raw(r_), col(c_), w(w_), h(h_), hit(hit_), active(false){
}

Brick::~Brick()
{
}
