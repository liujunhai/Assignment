#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>
#include <string>
#include <vector>

/*************************** Human *****************************/
class Human
{
// friend declarations for nonmember Human operations added
    friend Human* adGenerate(std::vector<Human*> adList, int i);

private:
    std::string name;
    int age;
    double hitTreshold;         // the ability to hit something, and it will vary among different casts
    std::vector<Human*> nearbyEnemies;
    static int id;
protected:
    int maxHealth;
    int maxMana;
    int currHealth;
    int currMana;
    int attackRange;
    std::string cast;
public:
    Human(int mxHealth, int mxMana, int atkRange, std::string c): maxHealth(mxHealth), currHealth(mxHealth), maxMana(mxMana), currMana(mxMana),  attackRange(atkRange), cast(c){id++};
    // Personal info:
    void setName(std::vector<std::string>& nameList);
    std::string getName() const {return name;}
    void setAge();
    int getAge() const {return age;}
    virtual std::string getCast() = 0;
    void showInitials();
    void getID() const {return id;}
    // Nearby Enemies:
    std::vector<Human*> getNearbyEnmy() const {return nearbyEnemies;}
    void setNearbyEnmy(std::vector<Human*>);
    // Choose a target/targets:
    virtual std::vector<Human*> chooseTarget(std::vector<Human*>) = 0;
    // Move to/Move away from target:
    virtual void move(std::vector<Human*> targets) = 0;
    // Hit Treshold:
    void setHitTreshold();
    double getHitTreshold() const {return hitTreshold;}
    // Close range damage:
    virtual void setDamage() = 0;
    virtual int getDamage() = 0;
    // Current Health:
    int getCurrHealth() const {return currHealth;}
    void resetCurrHealth(int newCurrHealth) {currHealth = newCurrHealth;}
    void showCurrHealth() {std::cout << getName() << " Current Health: " << currHealth << std::endl;}
    // Current Mana:
    int getCurrMana() const {return currMana;}
    // Cast Spells:
    virtual int castSpell() = 0;
    virtual ~Human() = default;
};

/************************** Warriors ***************************/
class Warriors:public Human
{
    friend class Sorcerer;
private:
    int damage;                  // + damage, which is a randomly generate number between 50~75

public:
    Warriors(int mxHealth = 100, int mxMana = 0, int atkRange = 1, std::string c = "Warriors"):Human(mxHealth, mxMana, atkRange, c){};

    std::vector<Human*> chooseTarget(std::vector<Human*>) override;
    void move(std::vector<Human*> targets) override;
    void setDamage() override;     // randomly generate damage (between 50~75)
    int getDamage() override {return damage;}
    std::string getCast() override {return cast;}
    int castSpell() override;
    ~Warriors() = default;
};

/******************  Sorcerer (Offensive Mages) ****************/
class Sorcerer:public Human
{
private:
    int damage;                // + close range damage (Only appear when the distance to an enemy is equal to 1)
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

    std::vector<Human*> chooseTarget(std::vector<Human*>) override;
    void setDamage() override;      // randomly generate close range damage(between 10~35)
    int getDamage() override {return damage;}
    std::string getCast() override {return cast;}
    ~Sorcerer() = default;
    int castSpell() override;
};
/******************  Priest (Defensive Mages) ****************/
class Priest: public Human
{
private:
    int damage;
    class DefSpells
    {
    private:
        std::string spellNames[3] = {"HolyLight", "FocusBlessing", "StrengthBlessing"};
        int spellCosts[3] = {10, 15, 5};
    public:
         DefSpells() = default;
         std::string getSpellName(int index){return spellNames[index];}
         int getSpellCost(int index){return spellCosts[index];}
         int getSpellBuff(int index);
         ~DefSpells() = default;
    };
    DefSpells spells;
public:
    Priest(int mxHealth = 70, int mxMana = 100, int atkRange = 3, std::string c = "Priest"): Human(mxHealth, mxMana, atkRange, c){};

    void setDamage() override;      // randomly generate close range damage(between 10~35)
    int getDamage() override {return damage;}
    std::string getCast() override {return cast;}
    int castSpell() override;
    ~Priest() = default;
};

#endif
