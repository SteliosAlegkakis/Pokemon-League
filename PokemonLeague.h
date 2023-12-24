#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <sstream>

using namespace std;

#define BEGIN_GAME int main(){
#define END_GAME ;return 0;}
#define SHOW ;cout<< 
#define END_LINE <<"\n";
#define CREATE ;
#define POKEMON Pokemon
#define POKEMONS Pokemons{}
#define NAME false?"name"
#define TYPE false?"type"
#define HP false?0
#define DEAR ;Pokemon::getPokemon(
#define LEARN )
#define ABILITY Ability
#define ABILITIES Abilities{}
#define ACTION false?[](Pokemon& p1, Pokemon& p2)->void{}
#define START [](Pokemon& attacker, Pokemon& defender)->void{
#define END ;}
#define ABILITY_NAME(ability_name) #ability_name" "
#define ATTACKER attacker,
#define DEFENDER defender,
#define IF if(
#define DO ){
#define ELSE_IF ;}else if(
#define ELSE ;}else{
#define HEAL ;Heal(),
#define DAMAGE ;Damage(),
#define GET_NAME(pokemon) getName(pokemon 0)
#define GET_HP(pokemon) getHp(pokemon 0)
#define GET_TYPE(pokemon) getType(pokemon 0)
#define IS_IN_POKEBALL(pokemon) isInPokeball(pokemon 0)
#define _heal 0
#define _damage 1


class Pokemon {
private:
    std::string name;
    std::string type;
    int health_points;
    bool inPokeball = false;
    int heal_damage = 0;
    static std::map<std::string,std::vector<std::string>> abilities;
    static std::map<std::string, Pokemon*> pokemons;

public:
    Pokemon(std::string _name ,std::string _type, int _health_points){
        name = _name;
        type = _type;
        health_points = _health_points;
        pokemons[_name] = this;
    }
    std::string getName() { return this->name; }
    std::string getType() { return this->type; }
    int getHealthPoints() { return this->health_points; }
    bool isInPokeball() { return this-> inPokeball; }
    void setHealDamage(int value) { this->heal_damage = value; }

    static const std::map<std::string, Pokemon*> getPokemons() { return pokemons; }
    static Pokemon getPokemon(std::string pokemon_name) { return *pokemons[pokemon_name]; }

    void damage(int damage_points) { health_points -= damage_points; }
    void heal(int heal_points) { health_points += heal_points; }

    static void printPokemons() {
        cout END_LINE
        SHOW "select pokemom :" END_LINE
        SHOW "--------------------------" END_LINE
        for (auto pair = pokemons.begin(); pair != pokemons.end(); ++pair) cout << pair->first END_LINE
        SHOW "--------------------------" END_LINE
        cout END_LINE
    }

    void printAbilities() { 
        std::vector<std::string> abs = abilities[name];
        cout END_LINE
        SHOW name << " select ability :" END_LINE
        SHOW "--------------------------" END_LINE
        for(int i=0;i<abs.size();i++) cout << abs.at(i) END_LINE
        SHOW "--------------------------" END_LINE
        cout END_LINE
    }

    void printStatus() {
        SHOW " " END_LINE
        SHOW "##########################" END_LINE
        SHOW "NAME : " << name END_LINE
        SHOW "HP : " << health_points END_LINE
        SHOW "Pokemon " << (inPokeball?"in pokeball":"out of Pokeball") END_LINE
        SHOW "##########################" END_LINE
        SHOW " " END_LINE
    }

    void operator[](std::string _abilities){
        std::istringstream s(_abilities);
        std::string token;
        std::vector<std::string> abilities_vector;

        while (s >> token) abilities_vector.push_back(token);

        abilities[name] = abilities_vector;
    }

    void operator,(const int& _hp){
        this->heal_damage == _damage?damage(_hp):heal(_hp);
    }
};

std::map<std::string, Pokemon*> Pokemon::pokemons;
std::map<std::string, std::vector<std::string>> Pokemon::abilities;

std::string getName(Pokemon pokemon,int foo) { return pokemon.getName(); }
std::string getType(Pokemon pokemon,int foo) { return pokemon.getType(); }
int getHp(Pokemon pokemon,int foo) { return pokemon.getHealthPoints(); }
bool isInPokeball(Pokemon pokemon,int foo) { return pokemon.isInPokeball(); }

class Pokemons{
public:
    Pokemons(){}
    template<typename... Args> 
    void operator[](Args... args){}   
};

class Heal{
public:
    Heal(){}
    Pokemon& operator,(Pokemon& pokemon){
        pokemon.setHealDamage(_heal);
        return pokemon;
    }
};

class Damage{
public:
    Damage(){}
    Pokemon& operator,(Pokemon& pokemon){ 
        pokemon.setHealDamage(_damage);
        return pokemon; 
    }
};

class Ability {
private:
    std::string name;
    std::function<void(Pokemon&, Pokemon&)> action;
    static std::map<std::string, Ability*> abilities;
public:
    using FunctionType = std::function<void(Pokemon&, Pokemon&)>;
    Ability(std::string _name, FunctionType _action) {
        name = _name;
        action = _action;
        abilities[_name] = this;
    }
    void execute(Pokemon& attacker, Pokemon& deffender){ action(attacker,deffender); }
    static const std::map<std::string, Ability*> getAbilities() { return abilities; }
    static Ability getAbility(std::string ability_name) { return *abilities[ability_name]; }
};

std::map<std::string, Ability*> Ability::abilities;

class Abilities {
public:
    Abilities(){}
    template<typename... Args> 
    void operator[](Args... args){} 
};

template<typename... Args>
bool AND(bool arg1,bool arg2,Args... args){
    if(!arg1 || !arg2) return false;
    bool result = ((args == false) || ...);
    return !result;
}

template<typename... Args>
bool OR(bool arg1,bool arg2,Args... args){
    if(arg1 || arg2) return true;
    bool result = ((args == true) || ...);
    return result;
}

bool NOT(bool argument){
    return !argument;
}