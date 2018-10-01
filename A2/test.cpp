#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



using namespace std;

class Human
{
// friend declarations for nonmember Human operations added

private:
    std::string name;
    int age;
    double hitTreshold;         // the ability to hit something, and it will vary among different casts
    static int id;
    std::vector<Human*> targets;
protected:
    int maxHealth;
    int maxMana;
    int currHealth;
    int currMana;
    int attackRange;
    std::string cast;
    std::vector<Human*> nearbyEnemies;
    std::vector<int> targetIndex;
public:
    Human(int mxHealth, int mxMana, int atkRange, std::string c): maxHealth(mxHealth), currHealth(mxHealth), maxMana(mxMana), currMana(mxMana),  attackRange(atkRange), cast(c){id++;}
    // Personal info:
    void setName(std::vector<std::string>& nameList);
    std::string getName() const {return name;}
    void setAge();
    int getAge() const {return age;}
    virtual std::string getCast() = 0;
    void showInitials();
    int getID()const {return id;}
    std::vector<Human*> getNearbyEnmy(){return nearbyEnemies;}
    void setNearbyEnmy(std::vector<Human*>);
    // Choose a target/targets
    virtual void chooseTarget(std::vector<Human*> &candidateList);
    // set targets:
    void setTargets(std::vector<Human*>t) {targets = t;}
    const std::vector<Human*>& getTargets() const {return targets;}
    std::vector<int> getTargetIndex() const {return targetIndex;}
    // Move to target:
    virtual void moveTo(std::vector<Human*>);
    virtual void moveAway(std::vector<Human*>) {std::cout << "Only ranged units need move away from their enemies" << std::endl;}
    void attack(std::vector<Human*> &targets);
    // Hit Treshold:
    void setHitTreshold();
    double getHitTreshold() const {return hitTreshold;}
    // Close range damage:
    virtual void setDamage() = 0;
    virtual int getDamage() = 0;
    // Current Health:
    int getCurrHealth() const {return currHealth;}
    void reduceCurrHealth(int dmg);
    void resetCurrHealth(int newCurrHealth) {currHealth = newCurrHealth;}
    void showCurrHealth() {std::cout << getName() << " Current Health: " << currHealth << std::endl;}
    // Current Mana:
    int getCurrMana()const{return currMana;}
    void resetCurrMana(int newCurrMana) {currMana = newCurrMana;}
    // Cast Spells
    virtual void castSpell(std::vector<Human*> &) = 0;
    // Take acitons:
    virtual void takeAction(std::vector<Human*> &candidateList);
    virtual ~Human() = default;

};

/************************** Warriors ***************************/
class Warriors:public Human
{
private:
    int damage;                  // + damage, which is a randomly generate number between 50~75

public:
    Warriors(int mxHealth = 100, int mxMana = 0, int atkRange = 1, std::string c = "Warriors"):Human(mxHealth, mxMana, atkRange, c){};


    //std::vector<Human*> chooseTarget(std::vector<Human*>) override;
    //void move(std::vector<Human*> targets) override;
    void setDamage() override;     // randomly generate damage (between 50~75)
    int getDamage() override {return damage;}
    //void attack(std::vector<Human*> &targets) override;
    std::string getCast() override {return cast;}
    void castSpell(std::vector<Human*> &) override;
    ~Warriors() = default;
};
/******************  Sorcerer (Offensive Mages) ****************/
class Sorcerer:public Human
{
private:
    int damage;                // + close range damage (Only appear when the distance to an enemy is equal to 1)
    double spellsHitTreshold = 90/100.0;
    class OffSpells
    {
    private:
        std::string spellNames[3] = {"FireBall", "IceBlade", "ThunderLance"};
        int spellCosts[3] = {10, 10, 20};
    public:
        OffSpells() = default;
        std::string getSpellName(int index){return spellNames[index];}
        int getSpellCost(int index){return spellCosts[index];}
        int getSpellDmg(int index);
        ~OffSpells() = default;
    };
    OffSpells spells;
public:
    Sorcerer(int mxHealth = 70, int mxMana = 100, int atkRange = 3, std::string c = "Sorcerer"): Human(mxHealth, mxMana, atkRange, c){};

    void moveAway(std::vector<Human*> targets) override;
    void chooseTarget(std::vector<Human*> &candidateList) override;
    void takeAction(std::vector<Human*> &candidateList) override;
    void setDamage() override;      // randomly generate close range damage(between 10~35)
    int getDamage() override {return damage;}
    std::string getCast() override {return cast;}
    ~Sorcerer() = default;
    void castSpell(std::vector<Human*> &) override;
};

int Human::id = 0;
void Human::setNearbyEnmy(std::vector<Human*> targets)
{
    nearbyEnemies = targets;
}
void Human::setName(std::vector<std::string>& nameList)
{
    int i = rand() % nameList.size();
    name = nameList[i];
    nameList.erase(nameList.begin() + i);   // erase the chosen name to prevent duplicate name
}
void Human::setAge()
{
    int tol = rand() % 20+30;
    (*this).age = tol;
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
void Human::reduceCurrHealth(int dmg)
{
    currHealth = currHealth - dmg;
    if(currHealth < 0)
    {
        currHealth = 0;
    }
}
void Human::chooseTarget(std::vector<Human*> &candidateList)
{
    std::vector<Human*> nearby = (*this).getNearbyEnmy();
    std::vector<Human*> t;      // contains chosen targets
    if(nearby.size()>0)              // if this adventurer has enenmies by his side, he will choose neaby enenmies at first
    {
        int len = nearby.size();
        int index = rand() % len;
        (*this).targetIndex.push_back(index);
        std::cout << (*this).getName() << " chooses " << nearby[index]->getName() << " to be his target" << std::endl;
        t.push_back(nearby[index]);
    }
    else
    {
        int len = candidateList.size();
        int index = rand() % len;
        (*this).targetIndex.push_back(index);
        std::cout << (*this).getName() << " chooses " << candidateList[index]->getName() << " to be his target" << std::endl;
        t.push_back(candidateList[index]);
    }
    (*this).setTargets(t);
}
void Human::moveTo(std::vector<Human*> targets)
{
    std::vector<Human*> nearbyEnmy;
    (*this).setNearbyEnmy(targets);
    std::cout << (*this).getName() << " moves to " << targets[0]->getName() << std::endl;

    nearbyEnmy.push_back(this);
    targets[0]->setNearbyEnmy(nearbyEnmy);
}
void Human::attack(std::vector<Human*> &targets)
{
    (*this).setDamage();
    int dmg = (*this).getDamage();
    std::cout << (*this).getName() << " causes " << dmg << " damage to his target." << std::endl;
    for(Human* ptr : targets)
    {
        ptr->reduceCurrHealth(dmg);
        std::cout << ptr->getName() << "'s current health is: " << ptr->getCurrHealth() << std::endl;
    }
}
void Human::takeAction(std::vector<Human*> &candidateList)
{
    std::vector<Human*> existTargets = (*this).getTargets();
    std::cout << "Original Exist target size: " << existTargets.size() << std::endl;
    // has not chosen a target yet or last target just died:
    if(existTargets.size() == 0 )
    {
        std::cout << "No target found, choose new target" << std::endl;
        (*this).chooseTarget(candidateList);
        existTargets = (*this).getTargets();
        (*this).moveTo(existTargets);
        (*this).attack(existTargets);
        for(Human* ptr : existTargets)
        {
            std::cout << "target remain HP: " << ptr->getCurrHealth() << std::endl;
            if(ptr->getCurrHealth() == 0)
            {
                existTargets.erase(existTargets.begin());   // delete dead enemies from target list
                ptrdiff_t pos1 = distance(candidateList.begin(), find(candidateList.begin(), candidateList.end(), ptr));
                candidateList.erase(candidateList.begin() + pos1);
                targetIndex.erase(targetIndex.begin());
                ptrdiff_t pos2 = distance(nearbyEnemies.begin(), find(nearbyEnemies.begin(), nearbyEnemies.end(), ptr));
                nearbyEnemies.erase(nearbyEnemies.begin() + pos2);
            }
            std::cout << "Target list check:" << existTargets.size() <<std::endl;
        }
        (*this).setTargets(existTargets);
    }
    else
    {
        std::cout << "Detect exist targets" << std::endl;
        // pick one target to check whether it is dead, if target is dead, clean the target list:
        for(Human* subject : existTargets)
        {
            std::cout << "Candidate size(before delete already dead target): " << candidateList.size() << std::endl;
            std::cout << "existTargets size: " << existTargets.size() << std::endl;
            std::cout << "subject HP: " << subject->getName() << " " << subject->getCurrHealth() << std::endl;
            if(subject->getCurrHealth() == 0)
            {
                std::vector<Human*> clean;
                existTargets = clean;
                (*this).setTargets(existTargets);
                std::cout << "clean dead targets and rechoose new target" << std::endl;
                ptrdiff_t pos2 = distance(nearbyEnemies.begin(), find(nearbyEnemies.begin(), nearbyEnemies.end(), subject));
                nearbyEnemies.erase(nearbyEnemies.begin() + pos2);
                std::cout << "Candidate size(after delete already dead target): " << candidateList.size() << std::endl;
                if(candidateList.size() > 0)
                Human::takeAction(candidateList);
            }
            else
            {
                (*this).attack(existTargets);
                for(Human* ptr : existTargets)
                {
                    if(ptr->getCurrHealth() == 0)
                    {
                        existTargets.erase(existTargets.begin());   // delete dead enemies from target list
                        ptrdiff_t pos1 = distance(candidateList.begin(), find(candidateList.begin(), candidateList.end(), ptr));
                        candidateList.erase(candidateList.begin() + pos1);
                        targetIndex.erase(targetIndex.begin());
                        ptrdiff_t pos2 = distance(nearbyEnemies.begin(), find(nearbyEnemies.begin(), nearbyEnemies.end(), ptr));
                        nearbyEnemies.erase(nearbyEnemies.begin() + pos2);
                    }
                }
            }
        }

    }
    (*this).setTargets(existTargets);
}
/************************* Warriors ****************************/

void Warriors::setDamage()                                    // set close range combat damage
{
   damage = rand() % 26+50;                                   // set to between 50~75
}
void Warriors::castSpell(std::vector<Human*> &)
{
    std::cout << "Warriors cannot cast spells!" << std::endl;
}
/************************* Sorcerer ****************************/
void Sorcerer::chooseTarget(std::vector<Human*> &candidateList)
{
    std::vector<Human*> t; // contains chosen targets
    // if Sorcerer runs out of his mana, he will act like Warriors (close ranged combat Only):
    if((*this).getCurrMana() == 0)
    {
        Human::chooseTarget(candidateList);
    }
    else
    {
        // if there are some enenmies nearby the Sorcerer, he will always choose to keep distance with thses enenmies:
        std::vector<Human*> nearby = (*this).getNearbyEnmy();
        if(nearby.size()>0)
        {
            (*this).moveAway(nearby);
            std::cout << (*this).getName() << " choose to keep distance with his nearby enenmies." << std::endl;
            (*this).setTargets(t);  // return empty target;
        }
        // if there is no enenmy nearby the sorcerer, he will cast spells and those spells causes AOE (1~3 enemies) damage:
        else
        {
            if(candidateList.size() == 0)
            std::cout << "No enemy exist" << std::endl;
            else
            {
                int len = candidateList.size();
                int index = rand() % len;
                if(len > 2)
                {
                    // if index == 0, this AOE damage will cover enenmies whose indexes are 0, 1 and 2:
                    if(index == 0)
                    {
                        std::cout << (*this).getName() << " chooses " << candidateList[index]->getName() << ", " << candidateList[index+1]->getName() << " and " <<  candidateList[index+2]->getName() << " to be his targets" << std::endl;
                        t.push_back(candidateList[index]);
                        t.push_back(candidateList[index+1]);
                        t.push_back(candidateList[index+2]);
                        (*this).targetIndex.push_back(index);
                        (*this).targetIndex.push_back(index+1);
                        (*this).targetIndex.push_back(index+2);
                    }
                    // if index == len - 1, this AOE damage will cover enenmies whose indexes are index-2, index-1 and index:
                    else if(index == len-1)
                    {
                        std::cout << (*this).getName() << " chooses " << candidateList[index-2]->getName() << ", " << candidateList[index-1]->getName() << " and " <<  candidateList[index]->getName() << " to be his targets" << std::endl;
                        t.push_back(candidateList[index-2]);
                        t.push_back(candidateList[index-1]);
                        t.push_back(candidateList[index]);
                        (*this).targetIndex.push_back(index-2);
                        (*this).targetIndex.push_back(index-1);
                        (*this).targetIndex.push_back(index);
                    }
                    // otherwise, this AOE will always cover the target (index points) and his nearby enenmies:
                    else
                    {
                        std::cout << (*this).getName() << " chooses " << candidateList[index-1]->getName() << ", " << candidateList[index]->getName() << " and " <<  candidateList[index+1]->getName() << " to be his targets" << std::endl;
                        t.push_back(candidateList[index-1]);
                        t.push_back(candidateList[index]);
                        t.push_back(candidateList[index+1]);
                        (*this).targetIndex.push_back(index-1);
                        (*this).targetIndex.push_back(index);
                        (*this).targetIndex.push_back(index+1);
                    }
                }
                else if(len == 2)
                {
                    // if index == 0, this AOE damage will cover enenmies whose indexes are 0, 1 and 2:
                    if(index == 0)
                    {
                        std::cout << (*this).getName() << " chooses " << candidateList[index]->getName() << " and " << candidateList[index+1]->getName() << " to be his targets " << std::endl;
                        t.push_back(candidateList[index]);
                        t.push_back(candidateList[index+1]);
                        (*this).targetIndex.push_back(index);
                        (*this).targetIndex.push_back(index+1);
                    }
                    else
                    {
                        std::cout << (*this).getName() << " chooses " << candidateList[index-1]->getName() << " and " << candidateList[index]->getName() << " to be his targets " << std::endl;
                        t.push_back(candidateList[index-1]);
                        t.push_back(candidateList[index]);
                        (*this).targetIndex.push_back(index-1);
                        (*this).targetIndex.push_back(index);
                    }
                }
                else
                {
                    std::cout << (*this).getName() << " chooses " << candidateList[index]->getName() << " to be his targets " << std::endl;
                    t.push_back(candidateList[index]);
                    (*this).targetIndex.push_back(index);
                }
                (*this).setTargets(t);
            }
        }
    }
}
void Sorcerer::moveAway(std::vector<Human*> nearbyEnmy)     // move away from enemies
{
    std::vector<Human*> clean;
    // use this empty vector to clean (*this).nearbyEnemies (represents the Sorcerer has moved away from his nearby enenmies):
    (*this).setNearbyEnmy(clean);
    // clean the nearbyEnemies in those nearbyEnmys as well:
    for(Human* enemy: nearbyEnmy)
    {
        enemy->setNearbyEnmy(clean);
    }
    std:: cout << (*this).getName() << " has moved away with his enemies." << std::endl;
}
void Sorcerer::setDamage()
{
   damage = rand() % 26+10;                                   // set to between 10~35
}
void Sorcerer::castSpell(std::vector<Human*> &targets)
{
    int index = rand() % 3;                  // randomly cast a spell from spell list (Only 3 types of spells in spell list)
    double spellsHitRate = rand() % 101/100.0;
    std::cout << getName() << " costs " << spells.getSpellCost(index) << " mana to cast " << spells.getSpellName(index) << " to his targets." <<std::endl;
    currMana = currMana - spells.getSpellCost(index);              // spend corresponding magic to cast each spell
    if(currMana < 0)
    currMana = 0;
    int dmg = spells.getSpellDmg(index);
    if(spellsHitRate < spellsHitTreshold)
    {
        std::cout << "Hit targets! Cause " << dmg << " damage!" << std::endl;
        for(Human* ptr : targets)
        {
            ptr->reduceCurrHealth(dmg);
            std::cout << ptr->getName() << "'s current health is: " << ptr->getCurrHealth() << std::endl;
        }
    }
    else std::cout << "Miss!" << std::endl;
}
void Sorcerer::takeAction(std::vector<Human*> &candidateList)
{
    std::vector<Human*> existTargets = (*this).getTargets();
    // if the sorcerer has not chosen a target yet or last target just died:
    if(existTargets.size() == 0 )
    {
        // if the Sorcerer run out of his mana, he will conduct close ranged combat:
        if((*this).getCurrMana() == 0)
        {
            Human::takeAction(candidateList);
        }
        else
        {
            (*this).chooseTarget(candidateList);
            existTargets = (*this).getTargets();
            if(existTargets.size() > 0)
            {
                (*this).castSpell(existTargets);
                // if the first target's index is 0:
                if(targetIndex[0] == 0)
                {
                    cout << "1st target's index is 0" << endl;
                    std::cout << "In here 1" << std::endl;
                    int counter = 0;        // record the dead target's index
                    std::vector<int> counters;      // store all dead targets' indexes
                    for(Human* ptr : existTargets)
                    {
                        if(ptr->getCurrHealth() == 0)
                        {
                            ptrdiff_t pos = distance(candidateList.begin(), find(candidateList.begin(), candidateList.end(), ptr));
                            std::cout << "pos:" << pos << std::endl;
                            std::cout << "Actual Target: " << ptr->getName() << std::endl;
                            std::cout << "Size: " << candidateList.size() << std::endl;
                            std::cout << candidateList[pos]->getName() << " was deleted" << std::endl;
                            candidateList.erase(candidateList.begin() + pos);
                            std::cout << "done" << std::endl;
                            targetIndex.erase(targetIndex.begin());
                            counters.push_back(counter);
                        }
                        counter++;
                    }
                    if(counters.size() > 0)
                    {
                        int i = 0;
                        // Delete the dead targets from existTargets:
                        for(int eraseIndex : counters)
                        {
                            existTargets.erase(existTargets.begin() + (eraseIndex - i));
                            i++;
                        }
                    }
                }
                // if the first target's index is not 0, delete those targets in this order: 1st target's index - 0, 2nd target's index - 1, 3rd target's index - 2, in order to delete the target correctly since those target were picked up adjacently:
                else
                {
                    std::cout << "In here 2" << std::endl;
                    int counter = 0;        // record the dead target's index
                    std::vector<int> counters;      // store all dead targets' indexes
                    for(Human* ptr : existTargets)
                    {
                        if(ptr->getCurrHealth() == 0)
                        {
                            ptrdiff_t pos = distance(candidateList.begin(), find(candidateList.begin(), candidateList.end(), ptr));
                            std::cout << "pos:" << pos << std::endl;
                            std::cout << "Actual Target: " << ptr->getName() << std::endl;
                            std::cout << "Size: " << candidateList.size() << std::endl;
                            std::cout << candidateList[pos]->getName() << " was deleted" << std::endl;
                            candidateList.erase(candidateList.begin() + pos);
                            std::cout << "done" << std::endl;
                            targetIndex.erase(targetIndex.begin());
                            std::cout << "counter: " << counter << std::endl;
                            counters.push_back(counter);
                        }
                        counter++;
                    }
                    if(counters.size() > 0)
                    {
                        int i = 0;
                        // Delete the dead targets from existTargets:
                        for(int eraseIndex : counters)
                        {
                            existTargets.erase(existTargets.begin() + (eraseIndex - i));
                            i++;
                        }
                    }
                }
                (*this).setTargets(existTargets);
                std::cout << "setTargets Done1" << std::endl;
            }
            else
            {
                std::cout << "Target does not exist!" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Exist targets need to be checked: " << existTargets.size() << std::endl;
        // find those targets who were dead already (Killed by teamates):
        int counter = 0;        // record the dead target's index
        std::vector<int> counters;      // store all dead targets' indexes
        for(Human* subject : existTargets)
        {
            if(subject->getCurrHealth() == 0)
            {
                std::cout << subject->getName() << "'s index: " << counter << std::endl;
                counters.push_back(counter);
            }
            counter++;
        }
        if(counters.size() > 0)
        {
            // Delete the dead targets from existTargets:
            for(int eraseIndex : counters)
            {
                std::cout << existTargets[0+eraseIndex]->getName() << " was deleted" << std::endl;
                existTargets.erase(existTargets.begin() + eraseIndex);
            }
        }
        // if all his targets were dead already, clean the old target list and take action again:
        if(existTargets.size() == 0)
        {
            std::vector<Human*> clean;
            (*this).setTargets(clean);
            Sorcerer::takeAction(candidateList);
        }
        else
        {
            (*this).castSpell(existTargets);
            if(targetIndex[0] == 0)
            {
                std::cout << "In here 3" << std::endl;
                int counter = 0;        // record the dead target's index
                std::vector<int> counters;      // store all dead targets' indexes
                for(Human* ptr : existTargets)
                {
                    if(ptr->getCurrHealth() == 0)
                    {
                        std::cout << "existTargets size: " << existTargets.size() << std::endl;
                        ptrdiff_t pos = distance(candidateList.begin(), find(candidateList.begin(), candidateList.end(), ptr));
                        std::cout << "pos:" << pos << std::endl;
                        std::cout << "Actual Target: " << ptr->getName() << std::endl;
                        std::cout << "Size: " << candidateList.size() << std::endl;
                        std::cout << candidateList[pos]->getName() << " was deleted" << std::endl;
                        candidateList.erase(candidateList.begin() + pos);
                        std::cout << "done" << std::endl;
                        targetIndex.erase(targetIndex.begin());
                        std::cout << "counter: " << counter << std::endl;
                        counters.push_back(counter);
                        std::cout << "All module done" << std::endl;
                    }
                    counter++;
                }
                if(counters.size() > 0)
                {
                    int i = 0;
                    // Delete the dead targets from existTargets:
                    for(int eraseIndex : counters)
                    {
                        existTargets.erase(existTargets.begin() + (eraseIndex - i));
                        i++;
                    }
                }
                std::cout << "existTargets size: " << existTargets.size() << std::endl;
            }
            else
            {
                std::cout << "In here 4" << std::endl;
                int counter = 0;        // record the dead target's index
                std::vector<int> counters;      // store all dead targets' indexes
                for(Human* ptr : existTargets)
                {
                    if(ptr->getCurrHealth() == 0)
                    {
                        std::cout << "existTargets size: " << existTargets.size() << std::endl;
                        ptrdiff_t pos = distance(candidateList.begin(), find(candidateList.begin(), candidateList.end(), ptr));
                        std::cout << "pos:" << pos << std::endl;
                        std::cout << "Actual Target: " << ptr->getName() << std::endl;
                        std::cout << "Size: " << candidateList.size() << std::endl;
                        std::cout << candidateList[pos]->getName() << " was deleted" << std::endl;
                        candidateList.erase(candidateList.begin() + pos);
                        std::cout << "done" << std::endl;
                        targetIndex.erase(targetIndex.begin());
                        std::cout << "counter: " << counter << std::endl;
                        counters.push_back(counter);
                        std::cout << "All module done" << std::endl;
                    }
                    counter++;
                }
                if(counters.size() > 0)
                {
                    int i = 0;
                    // Delete the dead targets from existTargets:
                    for(int eraseIndex : counters)
                    {
                        existTargets.erase(existTargets.begin() + (eraseIndex - i));
                        i++;
                    }
                }
                std::cout << "existTargets size: " << existTargets.size() << std::endl;
            }
                    (*this).setTargets(existTargets);
                    std::cout << "setTargets Done2" << std::endl;
        }
    }
    std::cout << "Sorcerer module finish" << std::endl;
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

/*
template <typename T>
Human* Create() {return new T();}

typedef Human* (*CreateFn)();
//using Human* CreateFn()= (*)

CreateFn create[] =
{
    &Create<Warriors>,
    &Create<Sorcerer>
};
const size_t fncount = sizeof(create)/sizeof(*create);


Human* Create()
{return create[rand() % fncount]();}

Human* choose(vector<Human*> TargetList)
{
    int len = TargetList.size();
    int index = rand() % len;
    return TargetList[index];
}*/

int main()
{
    srand (unsigned(time(NULL)));

    vector<string> nameList = {"Bob", "Peter", "Jane", "Sam", "Gaush", "Jack", "Michael"};

    Human* p1 = new Warriors;
    p1->setName(nameList);
    Human* p2 = new Warriors;
    p2->setName(nameList);
    Human* p3 = new Warriors;
    p3->setName(nameList);
    Human* p4 = new Warriors;
    p4->setName(nameList);
    Human* p5 = new Warriors;
    p5->setName(nameList);
    vector<Human*>  collection = {p1, p2, p3, p4, p5};
    // test for Sorcerer:
    Human* p6 = new Sorcerer;
    p6->setName(nameList);
    //vector<Human*> target = p6->chooseTarget(collection);
    //cout << target.size() << endl;
    //p6->castSpell(target);
    // test for Warriors:
    Human* p7 = new Warriors;
    p7->setName(nameList);
    vector<Human*> adventurer = {p6, p7};
    for(int i = 0; i < 5; i ++)
    {
        if(collection.size() > 0)
        {
            std::cout << "Round times: " << i+1 << std::endl;
            for(Human* ptr : adventurer)
            ptr->takeAction(collection);
        }
    }


    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    delete p6;
    delete p7;
}
