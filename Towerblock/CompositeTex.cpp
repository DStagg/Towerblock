#include "CompositeTex.h"

//	CompositeText
CompositeTex::CompositeTex()
{

};
CompositeTex::~CompositeTex()
{

};

sf::Sprite CompositeTex::BuildSprite()
{
	return BuildSprite(PairInt(0, 0), PairInt(_Texture.getSize().x, _Texture.getSize().y));
}

sf::Sprite CompositeTex::BuildSprite(PairInt topLeft, PairInt size)
{
	sf::Sprite tempspr(_Texture);

	tempspr.setTextureRect(sf::IntRect(topLeft._X, topLeft._Y, size._X, size._Y));

	return tempspr;
};

sf::Texture* CompositeTex::GetTexPntr()
{
	return &_Texture;
};
/////////////////

//	CompositeBuilder
CompositeBuilder::CompositeBuilder(sf::Image tilesheet, PairInt tile_size, std::map<int, PairInt> dic)
{
	_TileSheet = tilesheet;
	_TileSize = tile_size;
	_Dictionary = dic;
};
CompositeBuilder::~CompositeBuilder()
{

};

void CompositeBuilder::BuildCompositeTex(Grid grid, CompositeTex* comp)
{
	//	Sanity check for all of the date (3 x generic, 2 x specific)
	if ((_TileSheet.getSize().x == 0) && (_TileSheet.getSize().y == 0))
		return;
	if ((_TileSize._X <= 0) || (_TileSize._Y <= 0))
		return;
	if ((int)_Dictionary.size() == 0)
		return;
	if (comp == 0)
		return;
	if ((grid.GetWidth() == 0) || (grid.GetHeight() == 0))
		return;

	//	Build the blank texture of the correct dimensions
	comp->GetTexPntr()->create((unsigned int)(grid.GetWidth() * _TileSize._X), (unsigned int)(grid.GetHeight() * _TileSize._Y));
	
	//	Create a temporary blank image of the correct dimensions
	sf::Image tempimg;
	tempimg.create((unsigned int)(grid.GetWidth() * _TileSize._X), (unsigned int)(grid.GetHeight() * _TileSize._Y));

	//	Loop through each cell
	for (int x = 0; x < grid.GetWidth(); x++)
		for (int y = 0; y < grid.GetHeight(); y++)
		{
			//	Pull the cell value from grid, translate it into tilesheet coordinates using _Dictionary, copy from _TileSheet		
			tempimg.copy(_TileSheet, x * _TileSize._X, y * _TileSize._Y, sf::IntRect(
				_Dictionary[grid.GetCell(x,y)]._X * _TileSize._X,
				_Dictionary[grid.GetCell(x,y)]._Y * _TileSize._Y,
				_TileSize._X , 
				_TileSize._Y)
			);
		}

	//	Load the created composite image into the CompositeTex's internal texture
	comp->GetTexPntr()->loadFromImage(tempimg);
};
////////////////////

