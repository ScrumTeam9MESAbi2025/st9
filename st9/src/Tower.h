#pragma once
#include <SFML/Graphics.hpp>
#include "entities/entity/Entity.h"
#include "glm/glm.hpp"

class Sounds;
class EnemyManager;


enum towerKind
{
	tower_1,
	tower_2,
	tower_3,
	tower_4,
	tower_5,
	tower_6
};



class TowerTexture
{
	inline static TowerTexture* s_instance;
public:
	sf::Texture base;
	sf::Texture tops[2];
	TowerTexture()
	{
		base.loadFromFile("resources/images/buttom.png");
		tops[0].loadFromFile("resources/images/top.png");
		tops[1].loadFromFile("resources/images/Besser_als_Simon-_Maschienen_Gewehr.png");
	}
	static TowerTexture* get_instance()
	{
		if (!s_instance)
		{
			s_instance = new TowerTexture;
		}
		return s_instance;
	}
};

class Tower
	: public Entity
{
	int m_ressourcen;
	//double m_hp;
	float m_radius{6};
	int m_penetration{5};
	float m_speed{5};//i show speed
	double m_damage;
	float m_angle{};
	glm::vec3 m_prev_bullet_dir{ 1,0,0 };
	float m_cooldown = 0.8f;
	float m_condt{ 0.8f };
	sf::Sprite sprites[2];
	sf::Transform t;
public:
	Tower(glm::vec3);
	Tower(glm::vec3 i_pos, float i_cooldown, double i_damage, double i_health);
	Tower(glm::vec3 i_pos,towerKind tower_kind, int ressourcen);
	~Tower() override;
	void drawtower(sf::RenderTarget&) const;
	void fire(const EnemyManager& em,Sounds& sounds ,float deltatime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//glm::vec3 get_pos()const { return m_pos; }
	//warten auf hinzufügen von projectile klasse


};

