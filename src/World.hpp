#pragma once

class World {
private:
	float size{ 0 };
public:
	World(float size);

	float get_size();
};