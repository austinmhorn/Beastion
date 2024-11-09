#ifndef Kinetic_hpp
#define Kinetic_hpp

#include "Entity.hpp"

class Kinetic
     : public Entity
{
    public:
        
        Kinetic(const sf::Vector2f& velocity, const sf::Vector2f& velocityMax)
            : m_velocity( velocity ) , m_velocity_max( velocityMax ) {}

    protected:

        void limitVelocity()
        {
            if ( std::abs(m_velocity.x) > m_velocity_max.x ) // Limit X axis velocity
                m_velocity.x = m_velocity_max.x * ((m_velocity.x < 0) ? -1.f : 1.f);

            if ( std::abs(m_velocity.y) > m_velocity_max.y ) // Limit Y axis velocity
                m_velocity.y = m_velocity_max.y * ((m_velocity.y < 0) ? -1.f : 1.f);
        }

        sf::Vector2f m_velocity;
        sf::Vector2f m_velocity_max;
};

#endif /* Kinetic_hpp */ 