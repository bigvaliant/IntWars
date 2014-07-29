#include "stdafx.h"
#include "Champion.h"

Champion::Champion(const std::string& type, Map* map, uint32 id) : Unit(map, id, new Stats()), type(type), skillPoints(1), level(1)  
{
   stats->setCurrentHealth(666.0f);
   stats->setMaxHealth(1337.0f);
   stats->setGold(475.0f);
   stats->setAttackSpeedMultiplier(1.0f);
}

Spell* Champion::castSpell(uint8 slot, float x, float y, Unit* target) {
   if(slot >= spells.size()) {
      return 0;
   }
   
   Spell* s = spells[slot];
   
   if(s->getCost() > stats->getCurrentMana() || s->getState() != STATE_READY) {
      return 0;
   }
   
   s->cast(x, y, target);
   stats->setCurrentMana(stats->getCurrentMana()-s->getCost());
   return s;
}

Spell* Champion::levelUpSpell(uint8 slot) {
   if(slot >= spells.size()) {
      return 0;
   }
   
   if(skillPoints == 0) {
      return 0;
   }
   
   spells[slot]->levelUp();
   --skillPoints;
   
   return spells[slot];
}

void Champion::update(int64 diff) {
   Unit::update(diff);
   
   for(Spell* s : spells) {
      s->update(diff);
   }
}

Spell* Champion::GetSpell(int index)
{
	if(index >= spells.size() || index < 0)
		return 0;

	return spells[index];
}