#include "level.h"
#include <sstream>
#include <bitset>
namespace LEVELH{

	int Object::GetPropertyInt(std::string name)//возвращаем номер свойства в нашем списке
	{
		return atoi(properties[name].c_str());
	}

	float Object::GetPropertyFloat(std::string name)
	{
		return strtod(properties[name].c_str(), NULL);
	}

	std::string Object::GetPropertyString(std::string name)//получить им€ в виде строки.вроде пон€тно
	{
		return properties[name];
	}
	std::vector<unsigned char> intToBytes(sf::Uint32 paramInt)
	{
		std::vector<unsigned char> arrayOfByte(4);
		for (int i = 0; i < 4; i++)
			arrayOfByte[i] = (paramInt >> (i * 8));
		return arrayOfByte;
	}
	std::pair<sf::Uint32, std::bitset<3> > resolveRotation(sf::Uint32 gid)
	{
		const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
		const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
		const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

		std::vector<unsigned char> bytes = intToBytes(gid);
		sf::Uint32 tileGID = bytes[0] | bytes[1] << 8 | bytes[2] << 16 | bytes[3] << 24;

		bool flipped_diagonally = (tileGID & FLIPPED_DIAGONALLY_FLAG);
		bool flipped_horizontally = (tileGID & FLIPPED_HORIZONTALLY_FLAG);
		bool flipped_vertically = (tileGID & FLIPPED_VERTICALLY_FLAG);

		std::bitset<3> b;
		b.set(0, flipped_vertically);
		b.set(1, flipped_horizontally);
		b.set(2, flipped_diagonally);

		tileGID &= ~(FLIPPED_HORIZONTALLY_FLAG |
			FLIPPED_VERTICALLY_FLAG |
			FLIPPED_DIAGONALLY_FLAG);
		return std::pair<sf::Uint32, std::bitset<3> >(tileGID, b);
	}
	void doFlips(std::bitset<3> bits, sf::Sprite* spr)
	{
		/*
		case    RotateNoneFlipNone: // = Rotate180FlipXY
			break;
		case         Rotate90FlipNone:  // = Rotate270FlipXY
			pRect.left = lTemp.top;
			pRect.top = pNewContainerHeight - lTemp.right;
			pRect.right = lTemp.bottom;
			pRect.bottom = pNewContainerHeight - lTemp.left;
			break;
		case         Rotate180FlipNone: // = RotateNoneFlipXY
			pRect.left = pNewContainerWidth - lTemp.right;
			pRect.top = pNewContainerHeight - lTemp.bottom;
			pRect.right = pNewContainerWidth - lTemp.left;
			pRect.bottom = pNewContainerHeight - lTemp.top;
			break;
		case         Rotate270FlipNone: // = Rotate90FlipXY
			pRect.left = pNewContainerWidth - lTemp.bottom;
			pRect.top = lTemp.left;
			pRect.right = pNewContainerWidth - lTemp.top;
			pRect.bottom = lTemp.right;
			break;
		case         RotateNoneFlipX: // = Rotate180FlipY
			pRect.left = pNewContainerWidth - lTemp.right;
			pRect.top = lTemp.top;
			pRect.right = pNewContainerWidth - lTemp.left;
			pRect.bottom = lTemp.bottom;
			break;
		case         Rotate90FlipX: // = Rotate270FlipY
			pRect.left = pNewContainerWidth - lTemp.bottom;
			pRect.top = pNewContainerHeight - lTemp.right;
			pRect.right = pNewContainerWidth - lTemp.top;
			pRect.bottom = pNewContainerHeight - lTemp.left;
			break;
		case         Rotate180FlipX: // = RotateNoneFlipY
			pRect.left = lTemp.left;
			pRect.top = pNewContainerHeight - lTemp.bottom;
			pRect.right = lTemp.right;
			pRect.bottom = pNewContainerHeight - lTemp.top;
			break;
		case         Rotate270FlipX:  // = Rotate90FlipY
			pRect.left = lTemp.top;
			pRect.top = lTemp.left;
			pRect.right = lTemp.bottom;
			pRect.bottom = lTemp.right;
			break;
		default:
			// ?!??!
			break;
			*/
		//000 = no change
		//001 = vertical = swap y axis
		//010 = horizontal = swap x axis
		//011 = horiz + vert = swap both axes = horiz+vert = rotate 180 degrees
		//100 = diag = rotate 90 degrees right and swap x axis
		//101 = diag+vert = rotate 270 degrees right
		//110 = horiz+diag = rotate 90 degrees right
		//111 = horiz+vert+diag = rotate 90 degrees right and swap y axis
		auto height = spr->getTexture()->getSize().y;
		auto width = spr->getTexture()->getSize().x;
		sf::IntRect rect = spr->getTextureRect();
		if (!bits.test(0) && !bits.test(1) && !bits.test(2))
		{
			//Shortcircuit tests for nothing to do
			return;
		}
		else if (bits.test(0) && !bits.test(1) && !bits.test(2))
		{
			//001
			rect.height = -rect.height;
			//flipY(v0, v1, v2, v3);
		}
		else if (!bits.test(0) && bits.test(1) && !bits.test(2))
		{
			//010
			rect.width = -rect.width;
			//flipX(v0, v1, v2, v3);
		}
		else if (bits.test(0) && bits.test(1) && !bits.test(2))
		{
			//011
			//flipY(v0, v1, v2, v3);
			//flipX(v0, v1, v2, v3);
		}
		else if (!bits.test(0) && !bits.test(1) && bits.test(2))
		{
			//100
			//flipD(v0, v1, v2, v3);
		}
		else if (bits.test(0) && !bits.test(1) && bits.test(2))
		{
			//101
			//flipX(v0, v1, v2, v3);
			//flipD(v0, v1, v2, v3);


		}
		else if (!bits.test(0) && bits.test(1) && bits.test(2))
		{
			//110
			//flipY(v0, v1, v2, v3);
			//flipD(v0, v1, v2, v3);

		}
		else if (bits.test(0) && bits.test(1) && bits.test(2))
		{
			//111
			//flipY(v0, v1, v2, v3);
			//flipX(v0, v1, v2, v3);
			//flipD(v0, v1, v2, v3);
		}
		spr->setTextureRect(rect);
	}
	int clearflags(int GID)
	{
		const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
		const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
		const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

		GID &= ~(FLIPPED_HORIZONTALLY_FLAG |
			FLIPPED_VERTICALLY_FLAG |
			FLIPPED_DIAGONALLY_FLAG);
		return GID;

	}
	bool Level::LoadFromFile(std::string filename)//двоеточи€-обращение к методам класса вне класса 
	{
		TiXmlDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument

												  // загружаем XML-карту
		if (!levelFile.LoadFile())//если не удалось загрузить карту
		{
			std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//выдаем ошибку
			return false;
		}

		// работаем с контейнером map
		TiXmlElement *map;
		map = levelFile.FirstChildElement("map");

		// пример карты: <map version="1.0" orientation="orthogonal"
		// width="10" height="10" tilewidth="34" tileheight="34">
		width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
		height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
		tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
		tileHeight = atoi(map->Attribute("tileheight"));

		// Ѕерем описание тайлсета и идентификатор первого тайла
		TiXmlElement *tilesetElement;
		tilesetElement = map->FirstChildElement("tileset");
		firstTileID = atoi(tilesetElement->Attribute("firstgid"));

		// source - путь до картинки в контейнере image
		TiXmlElement *image;


		std::vector<TiXmlElement> source;
		source.reserve(0);
		int count = 0;
		for (auto child = map->FirstChild("tileset"); child != NULL; child = child->NextSibling("tileset"))
		{
			
			source.push_back(tilesetElement->Attribute("source"));
			count++;
		}
		std::cout << "count = " << count << std::endl;
		std::vector<TiXmlDocument> Tilesets;
		Tilesets.reserve(0);
		std::vector<TiXmlElement*> subtileset;
		subtileset.reserve(0);
		std::vector<sf::Texture> txtvec;
		txtvec.reserve(0);
		std::vector<std::vector<sf::Rect<int>>> subRects;
		
		for (auto it = source.begin(); it != source.end(); ++it)
		{
			auto index = std::distance(source.begin(), it);

			if (index < source.size())
			{
				
				std::stringstream ss;
				
				auto p = "resources/";
				ss << p;
				ss << source[index].ValueTStr().c_str();
				Tilesets.push_back(TiXmlDocument(ss.str().c_str()));
				if (!Tilesets[index].LoadFile())//если не удалось загрузить тайслет
				{
					std::cout << "Loading tileset \"" << source[index].ValueTStr().c_str() << "\" failed." << std::endl;//выдаем ошибку
					return false;
				}
				subtileset.push_back(Tilesets[index].FirstChildElement("tileset"));
				int count2 = 0;
				//std::vector<sf::Texture> tmpvc;
				//tmpvc.reserve(0);
				subRects.push_back(std::vector<sf::IntRect>());
				for (auto child = subtileset[index]->FirstChildElement("tile"); child != NULL; child = child->NextSiblingElement("tile"))
				{
					count2++;
					sf::Texture txt;
					std::stringstream ss2;
					ss2 << "resources/";
					auto ch = child->FirstChildElement("image");
					auto pp = ch->Attribute("source");
					
					ss2 << pp;
					txt.loadFromFile(ss2.str());
					//tmpvc.push_back(txt);
					auto wid = atoi(ch->Attribute("width"));
					auto hei = atoi(ch->Attribute("height"));
					sf::Rect<int> rect;

					rect.top = 0;
					rect.height = hei;
					rect.left = 0;
					rect.width = wid;
					
					subRects[index].push_back(rect);
					txtvec.push_back(txt);
					
				}
				
				
				/*std::vector<TiXmlElement *>tileElement;
				tileElement= subtileset[index]FirstChildElement("tileset");*/

			}
			
		}
		

		tilesetImage.loadFromFile("resources/blocks/wall.png");
		
		/*image = tilesetElement->FirstChildElement("image");
		std::string imagepath = image->Attribute("source");

		// пытаемс€ загрузить тайлсет
		sf::Image img;

		if (!img.loadFromFile(imagepath))
		{
			std::cout << "Failed to load block texture." << std::endl;//если не удалось загрузить тайлсет-выводим ошибку в консоль
			return false;
		}


		//img.createMaskFromColor(sf::Color(255, 255, 255));//дл€ маски цвета.сейчас нет маски
		tilesetImage.loadFromImage(img);
		tilesetImage.setSmooth(false);//сглаживание
		*/
									  // получаем количество столбцов и строк тайлсета
		/*int columns = tilesetImage.getSize().x / tileWidth;
		int rows = tilesetImage.getSize().y / tileHeight;
		*/
		// вектор из пр€моугольников изображений (TextureRect)
	


		// работа со сло€ми
		TiXmlElement *layerElement;
		layerElement = map->FirstChildElement("layer");
		while (layerElement)
		{
			Layer layer;

			// если присутствует opacity, то задаем прозрачность сло€, иначе он полностью непрозрачен
			if (layerElement->Attribute("opacity") != NULL)
			{
				float opacity = strtod(layerElement->Attribute("opacity"), NULL);
				layer.opacity = 255 * opacity;
			}
			else
			{
				layer.opacity = 255;
			}

			//  контейнер <data> 
			TiXmlElement *layerDataElement;
			layerDataElement = layerElement->FirstChildElement("data");

			if (layerDataElement == NULL)
			{
				std::cout << "Bad map. No layer information found." << std::endl;
			}

			//  контейнер <tile> - описание тайлов каждого сло€
			TiXmlElement *tileElement;
			tileElement = layerDataElement->FirstChildElement("tile");

			if (tileElement == NULL)
			{
				std::cout << "Bad map. No tile information found." << std::endl;
				return false;
			}

			int x = 0;
			int y = 0;

			while (tileElement)
			{
				int tileGID = atoi(tileElement->Attribute("gid"));
				int subRectToUse = tileGID - firstTileID;

				// ”станавливаем TextureRect каждого тайла
				if (subRectToUse >= 0)
				{
					sf::Sprite sprite;
					auto idandflags = resolveRotation(tileGID);
					std::cout << idandflags.first << std::endl;
					//≈ЅјЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋЋ
					auto gid = clearflags(tileGID);
					sf::Texture txt = txtvec[gid];
					sprite.setTexture(txt);
					doFlips(idandflags.second, &sprite);
					//sprite.setTextureRect(subRects[subRectToUse]);
					sprite.setPosition(x * txt.getSize().x, y * txt.getSize().y);
					sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

					layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
				}

				tileElement = tileElement->NextSiblingElement("tile");

				x++;
				if (x >= width)
				{
					x = 0;
					y++;
					if (y >= height)
						y = 0;
				}
			}

			layers.push_back(layer);

			layerElement = layerElement->NextSiblingElement("layer");
		}

		// работа с объектами
		TiXmlElement *objectGroupElement;

		// если есть слои объектов
		if (map->FirstChildElement("objectgroup") != NULL)
		{
			objectGroupElement = map->FirstChildElement("objectgroup");
			while (objectGroupElement)
			{
				//  контейнер <object>
				TiXmlElement *objectElement;
				objectElement = objectGroupElement->FirstChildElement("object");

				while (objectElement)
				{
					// получаем все данные - тип, им€, позици€, и тд
					std::string objectType;
					if (objectElement->Attribute("type") != NULL)
					{
						objectType = objectElement->Attribute("type");
					}
					std::string objectName;
					if (objectElement->Attribute("name") != NULL)
					{
						objectName = objectElement->Attribute("name");
					}
					int x = atoi(objectElement->Attribute("x"));
					int y = atoi(objectElement->Attribute("y"));

					int width, height;

					sf::Sprite sprite;
					sprite.setTexture(tilesetImage);
					sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
					sprite.setPosition(x, y);

					if (objectElement->Attribute("width") != NULL)
					{
						width = atoi(objectElement->Attribute("width"));
						height = atoi(objectElement->Attribute("height"));
					}
					else
					{
						/*width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
						height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
						sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);*/
					}

					// экземпл€р объекта
					Object object;
					object.name = objectName;
					object.type = objectType;
					object.sprite = sprite;

					sf::Rect <float> objectRect;
					objectRect.top = y;
					objectRect.left = x;
					objectRect.height = height;
					objectRect.width = width;
					object.rect = objectRect;

					// "переменные" объекта
					TiXmlElement *properties;
					properties = objectElement->FirstChildElement("properties");
					if (properties != NULL)
					{
						TiXmlElement *prop;
						prop = properties->FirstChildElement("property");
						if (prop != NULL)
						{
							while (prop)
							{
								std::string propertyName = prop->Attribute("name");
								std::string propertyValue = prop->Attribute("value");

								object.properties[propertyName] = propertyValue;

								prop = prop->NextSiblingElement("property");
							}
						}
					}


					objects.push_back(object);

					objectElement = objectElement->NextSiblingElement("object");
				}
				objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
			}
		}
		else
		{
			std::cout << "No object layers found..." << std::endl;
		}

		return true;
	}

	Object Level::GetObject(std::string name)
	{
		// только первый объект с заданным именем
		for (int i = 0; i < objects.size(); i++)
			if (objects[i].name == name)
				return objects[i];
	}

	std::vector<Object> Level::GetObjects(std::string name)
	{
		// все объекты с заданным именем
		std::vector<Object> vec;
		for (int i = 0; i < objects.size(); i++)
			if (objects[i].name == name)
				vec.push_back(objects[i]);

		return vec;
	}


	std::vector<Object> Level::GetAllObjects()
	{
		return objects;
	};


	sf::Vector2i Level::GetTileSize()
	{
		return sf::Vector2i(tileWidth, tileHeight);
	}

	void Level::Draw(sf::RenderWindow &window)
	{
		// рисуем все тайлы (объекты не рисуем!)
		for (int layer = 0; layer < layers.size(); layer++)
			for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
				window.draw(layers[layer].tiles[tile]);
	}
}