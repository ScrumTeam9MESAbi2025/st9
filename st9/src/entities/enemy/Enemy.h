#pragma once
#include "entities/entity/Entity.h"

class Enemy :
    public Entity
   {
   private:
       
       std::vector<glm::vec3> m_movements;
       size_t prev_size;
       double m_hp = 2;
       double m_id = 0;
       friend class EnemyManager;
   public:
       Enemy() = default;
       void die();
       void update();
       bool is_alive() const ;
       void take_damage(double damage);
       double get_hp() const;
};
