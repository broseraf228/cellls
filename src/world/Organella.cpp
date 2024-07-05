#include "Organella.hpp"
#include "Cell.hpp"
#include "World.hpp"

extern World* world;

Org_Chloroplast::Org_Chloroplast(Life_Cell* host) : host{host} {

}
void Org_Chloroplast::activate()
{
	host->energy += world->map_get_light_power(host->position.x, host->position.y);
}
Organella_I* Org_Chloroplast::clone(Life_Cell* host)
{
	return new Org_Chloroplast(host);
}