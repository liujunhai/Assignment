#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>      /* srand, rand */
#include "myClass.h"

void Human::setName(std::vector<std::string>& nameList)
{
    int i = rand() % nameList.size();
    name = nameList[i];
    nameList.erase(nameList.begin() + i);   // erase the chosen name to prevent duplicate name
}
void Human::setAge()
{
    int age = rand() % 20+30;
    (*this).age = age;
}
void Human::showInitials()                                     // show details function
{
   std::cout << "MaxHealth: " << maxHealth << std::endl;
   std::cout << "MaxMana: " << maxMana << std::endl;
   std::cout << "AttackRange: " << attackRange << std::endl;
}
void Human::setHitTreshold()
{
   if(cast == "Warriors")
   hitTreshold = 80/100.0;
   else if(cast == "Sorcerer")
   hitTreshold = 50/100.0;
}
/************************* Warriors ****************************/
std::vector<Human*> Warriors::chooseTarget(std::vector<Human*> candidateList)
{
    std::vector<Human*> nearby = (*this).getNearbyEnmy();
    std::vector<Human*> targets;            // contains chosen targets
    int len = candidateList.size();
    int index = rand() % len;
    if(nearby.size()>0)              // if this adventurer has enenmies by his side, he will choose neaby enenmies at first
    {
        std::cout << (*this).getName() << " chooses " << nearby[index]->getName() << " to be his target" << std::endl;
        targets.push_back(nearby[index]);
    }
    else
    {
        std::cout << (*this).getName() << " chooses " << candidateList[index]->getName() << " to be his target" << std::endl;
        targets.push_back(candidateList[index]);
    }
    return targets;
}
void Warriors::move(std::vector<Human*> targets)
{
    std::vector<Human*> nearbyEnmy;
    (*this).setNearbyEnmy(targets);
    std::cout << (*this).getName() << " moves to " << targets[0]->getName() << std::endl;

    nearbyEnmy.push_back(this);
    targets[0]->setNearbyEnmy(nearbyEnmy);
}
void Warriors::setDamage()                                    // set close range combat damage
{
   damage = rand() % 26+50;                                   // set to between 50~75
}
int Warriors::castSpell()
{
    std::cout << "Warriors cannot cast spells!" << std::endl;
    return 0;
}
/************************* Sorcerer ****************************/
std::vector<Human*> Sorcerer::chooseTarget(std::vector<Human*> candidateList)
{
    std::vector<Human*> target;            // contains chosen targets
    // if Sorcerer runs out of his mana, he will act like a Warriors (close ranged combat Only):
    if((*this).getCurrMana() == 0)
    {
        target = Warriors::chooseTarget(cnadidateList);
        return target;
    }
    else
    {
        // if there are some enenmies nearby the Sorcerer, he will always choose to keep distance with thses enenmies:
        std::vector<Human*> nearby = (*this).getNearbyEnmy();
        if(nearby>0)
        {
            (*this).move(nearby);
            std::cout << (*this).getName() << " choose to keep distance with his nearby enenmies." << std::endl;
            return target;              // return empty target;
        }
        else
        {
            int len = candidateList.size();
            int index = rand() % len;
            std::cout << (*this).getName() << " chooses " << candidateList[index]->getName() << " to be his target" << std::endl;
            target.push_back(candidateList[index]);
            return target;
        }
    }
}
void Sorcerer::setDamage()
{
   damage = rand() % 26+10;                                   // set to between 10~35
}
int Sorcerer::castSpell()
{
    int index = rand() % 3;                  // randomly cast a spell from spell list (Only 3 types of spells in spell list)
    std::cout << getName() << " casts " << spells.getSpellName(index) << std::endl;
    currMana = currMana - spells.getSpellCost(index);              // spend corresponding magic to cast each spell
    return spells.getSpellDmg(index);
}
int Sorcerer::OffSpells::getSpellDmg(int index)
{
    int dmg;
    switch(index)
    {
        case 0:                     // FireBall
            dmg = rand() % 26+50;   // dmg between 50~75
            break;
        case 1:                     // IceBlade
            dmg = rand() % 26+50;   // dmg between 50~75
            break;
        case 2:                     // ThunderLance
            dmg = rand() % 31+70;   // dmg between 70~100
            break;
    }
    return dmg;
}
/************************* Priest ****************************/
void Priest::setDamage()
{
    damage = rand() % 26+10;                                   // set to between 10~35
}
int Priest::castSpell()
{
    int index = rand() % 3;                  // randomly cast a spell from spell list (Only 3 types of spells in spell list)
    std::cout << getName() << " casts " << spells.getSpellName(index) << std::endl;
    currMana = currMana - spells.getSpellCost(index);              // spend corresponding magic to cast each spell
    return spells.getSpellBuff(index);
}
int Priest::DefSpells::getSpellBuff(int index)
{
    int buff;
    switch(index)
    {
        case 0:                     // HolyLight
            buff = rand() % 26+50;   // Healing between 50~75
            break;
        case 1:                     // FocusBlessing
            buff = rand() % 11+10;   // Buff hit rate between 10~20
            break;
        case 2:                     // StrengthBlessing
            buff = rand() % 16+15;   // Buff close range damage between 15~30
            break;
    }
    return buff;
}
