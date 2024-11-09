#include "Card.hpp"

#include <string>   // std::find_last_of
#include <cmath>

Card::Card(const std::string& pathToBackTexture, const std::string& pathToFaceTexture)
    : m_face_down( true )
    , m_is_animating_flip( false )
    , m_needs_texture_swap( false )
    , m_flip_anim_scale_down_complete( false )
    , m_flip_anim_speed( 1.f )
{

    loadTexture(m_back, pathToBackTexture);
    loadTexture(m_face, pathToFaceTexture);

    // Smooth texture edges
    m_back.setSmooth(true);
    m_face.setSmooth(true);

    m_sprite.setTexture(m_back); // Initially assigns the card back texture to the sprite

    // Track original size of texture rectangle
    m_size = { static_cast<float>(m_sprite.getTextureRect().width), static_cast<float>(m_sprite.getTextureRect().height) };
    
    adjustFlipAnimation(); // Calculate flip animation values
}
 void Card::setPosition(const sf::Vector2f& position)
 {
    m_sprite.setPosition(position);
 }
void Card::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}
const sf::Vector2f& Card::getPosition() const
{
    return m_sprite.getPosition();
}
void Card::setSize(const sf::Vector2f& size)
{
    
}
const sf::Vector2f Card::getSize() const
{
    return m_size;
}
void Card::setFlipAnimationSpeed(float speed)
{
    m_flip_anim_speed = speed;
    adjustFlipAnimation(); // Recalculate flip animation values
}
float Card::getFlipAnimationSpeed() const
{
    return m_flip_anim_speed;
}
void Card::flip()
{
    m_is_animating_flip = true;
    m_needs_texture_swap = true;
}

void Card::handleEvent(sf::Event event) 
{
    sf::Vector2f mouseMovePosition;
    sf::Vector2f mouseButtonPressedPosition;
    sf::Vector2f mouseButtonReleasedPosition;


    switch (event.type)
    {
        case sf::Event::MouseMoved:
            mouseMovePosition = { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) }; ///< Get new mouse position

            setMouseIn( contains(mouseMovePosition) );
            break;
            
        case sf::Event::MouseButtonPressed:
            mouseButtonPressedPosition = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) }; ///< Get location for mouse button press event

            setPressed( contains(mouseButtonPressedPosition) );

            if ( isPressed() )
                //std::cout << "pressed" << std::endl;
            
            break;
            
        case sf::Event::MouseButtonReleased:
            mouseButtonReleasedPosition = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) }; ///< Get location for mouse button release event

            setClicked( isPressed() && contains(mouseButtonReleasedPosition) );
            
            if ( isPressed() )
                //std::cout << "released" << std::endl;
            
            if ( isClicked() ) 
                flip();
            

            setClicked(false); // Reset
            setPressed(false); // Reset
            break;
            
        case sf::Event::KeyPressed:
            break;
            
        case sf::Event::TextEntered:
            break;
            
        default:
            break;
    }
}
void Card::handleKeyEvent(sf::Keyboard::Key key, bool press) 
{

}
void Card::handleTextEvent(sf::Utf32 character) 
{

}
void Card::handleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) 
{

}
void Card::handleMouseMoveEvent(int x, int y) 
{

}
void Card::handleMouseEnter(int x, int y) 
{

}
void Card::handleMouseLeave(int x, int y) 
{

}
void Card::handleMouseClick(sf::Mouse::Button button, int x, int y) 
{

}

bool Card::contains(const sf::Vector2f& point) const 
{
    return m_sprite.getGlobalBounds().contains(point);
}

void Card::update(sf::Time delta_time) 
{
    if ( m_is_animating_flip )
        playFlipAnimation(delta_time);

    if ( isPressed() && !isClicked() )
    {
        //std::cout << "holding" << std::endl;
    }
}
void Card::playFlipAnimation(sf::Time delta_time)
{
    auto currXScaleVal = m_sprite.getScale().x;
    float newXScaleVal;

    // Check if this animation play has finished
    if ( m_flip_anim_scale_down_complete && currXScaleVal >= 1.f )
    {
        m_sprite.setScale( 1.f, m_sprite.getScale().y ); // Correct any accidental overscaling
        m_is_animating_flip = false;                     // Disbale control boolean for animation
        m_flip_anim_scale_down_complete = false;         // Reset control boolean for scale down completion
        m_face_down = !m_face_down;                      // Invert control boolean for texture determination
        return;                                          // The animation is finished and the remaining code should not run
    }

    // Determine if scale down process is complete
    if ( currXScaleVal < 0.f )
    {
        newXScaleVal = 0.f; // Correct any accidental downscaling
        m_flip_anim_scale_down_complete = true; // Set control boolean for scale down completion to true
    }

    // Calculate sprite's new x scale value
    // This ensures the scale value always remains in the positive as to prevent a backwards texture
    newXScaleVal = ( !m_flip_anim_scale_down_complete ) 
        ? currXScaleVal - m_flip_anim_rescale_factor   // Performing initial scale down
        : currXScaleVal + m_flip_anim_rescale_factor;  // Now scaling back up

    // Adjust sprite's x scale 
    m_sprite.setScale( newXScaleVal, m_sprite.getScale().y );

    // Calculate new x coordinate position for sprite with adjustment to flip animation speed
    const auto newXPos = ( m_flip_anim_scale_down_complete ) 
        ? m_sprite.getPosition().x - (m_flip_anim_anchor * m_flip_anim_speed) 
        : m_sprite.getPosition().x + (m_flip_anim_anchor * m_flip_anim_speed);

    // Assign new position to sprite
    m_sprite.setPosition( newXPos, m_sprite.getPosition().y );

    // This controls the sprite texturing swapping process to occurr at the correct time
    if ( m_needs_texture_swap && m_flip_anim_scale_down_complete )
    {
        if ( m_face_down ) // Card is showing the back texture and flipping to face texture
        {
            m_sprite.setTexture(m_face);
            m_needs_texture_swap = false; 
        }
        else if ( !m_face_down )// Card is showing the face texture and flipping to back texture
        {
            m_sprite.setTexture(m_back);
            m_needs_texture_swap = false;
        }
    }
}
void Card::adjustFlipAnimation()
{
    m_flip_anim_anchor = 0.5f * ( (m_sprite.getTextureRect().width / 2.f) / 10.f ); // Set anchor position to the center of the card
    m_flip_anim_rescale_factor = m_flip_anim_speed * (m_flip_anim_anchor / (0.5f * m_size.x)); // Determine rescale factor with respect to the speed of the flip
}
void Card::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}