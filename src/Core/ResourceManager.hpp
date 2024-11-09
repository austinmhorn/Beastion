#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <SFML/Graphics/Color.hpp>

#include "SystemInfo.hpp"
#include "Sansation.hpp"

#include <filesystem>
#include <vector>
#include <map>

typedef unsigned int u_int;

static const sf::Font Sansation = load_sansation();

class TextureHolder
{
    public:

        TextureHolder()
        {
            
        }

        
        void addTexture(const std::string& texturePathFromProjectSourceDirectory)
        {
            sf::Texture texture;

            //if ( !texture.loadFromFile() )
            //    std::cerr << "Error loading texture" << std::endl;

            //m_textures.push_back(std::make_pair());
        }

    private: 

        std::vector<std::pair<u_int, sf::Texture>> m_textures;
        std::map<u_int, std::string>               m_map;
};








class ResourceManager
{
    public:

        ResourceManager(const std::filesystem::path& pathToProjectSourceDirectory)
            : m_sourceDirPath( pathToProjectSourceDirectory )
        {
            
        }

        void loadTextures()
        {

            

        }

    private:

        const std::filesystem::path m_sourceDirPath;
        TextureHolder               m_textureHolder;

};

/* 
    auto dir = m_sourceDir;
    dir.append("/cards/backs/");
    u_int file_count = directoryFileCount(dir.string(), "back_", ".png");
*/

/*
            auto dir = texture_dir;
            std::string prefix;
            std::string ext;

            // Read number of card back textures
            prefix = "back_";
            ext = ".png";
            dir.append("assets/textures/card/back/");
            u_int file_count = directoryFileCount(dir.string(), prefix, ext);

*/

static const sf::Color Gray        = sf::Color(  37,  37,  37, 255 );
static const sf::Color DarkRed     = sf::Color( 127,  91,  92, 255 );
static const sf::Color DarkGreen   = sf::Color(  92, 127,  99, 255 );
static const sf::Color LightGreen  = sf::Color( 151, 193, 169, 255 );
static const sf::Color DarkPurple  = sf::Color( 113,  92, 127, 255 );
static const sf::Color LightPurple = sf::Color( 223, 204, 241, 255 );
static const sf::Color DarkBlue    = sf::Color(  69,  80, 163, 255 );
static const sf::Color LightBlue   = sf::Color( 154, 183, 211, 255 );
static const sf::Color Seafoam     = sf::Color( 163, 225, 220, 255 );
static const sf::Color Peach       = sf::Color( 255, 218, 193, 255 );
static const sf::Color Tan         = sf::Color( 246, 234, 194, 255 );
static const sf::Color Pink        = sf::Color( 255, 200, 221, 255 );
static const sf::Color Orange      = sf::Color( 239, 190, 125, 255 );

#endif /* ResourceManager_hpp */
