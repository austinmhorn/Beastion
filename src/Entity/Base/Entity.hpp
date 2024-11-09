#ifndef Entity_hpp
#define Entity_hpp

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/// \class Entity
/// \defgroup Entities
/// \brief Base class representing drawable entities (sf::Shape, sf::Sprite, etc.)
/////////////////////////////////////////////////////////////////////////////////////////
class Entity 
    : virtual public sf::Transformable
    , virtual public sf::Drawable
{
    protected:
    
        Entity() = default;
        ~Entity() override = default;
        
        Entity(const Entity&) = default;
        Entity& operator=(const Entity&) = default;
        
        Entity(Entity&&) noexcept = default;
        Entity& operator=(Entity&&) noexcept = default;
    
    private:
    
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

#endif /* Entity_hpp */