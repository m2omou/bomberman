
#include	"LoadMap.hpp"

LoadMap::LoadMap()
{

}

LoadMap::LoadMap(const std::string &file)
{
  select_map(file);
}

void	LoadMap::select_map(const std::string &file)
{
  std::string                   str;
  std::ifstream                 infile;

  this->width = 0;
  this->height = 0;
  infile.open(file.c_str());
  if (infile.is_open() && infile.good())
    {
      while (getline(infile, str))
	{
	  this->height++;
	  if ((str.size() > this->width) && !this->width)
	    this->width = str.size();
	  if ((str.size() != this->width) || !str.size())
	    {
	      std::cerr << "Error: map [width] [height]" << std::endl;
	      exit(1);
	    }
	  data.push_back(str);
	}
      if (!this->width || !this->height)
	{
	  std::cerr << "Error: the map is empty" << std::endl;
	  exit(1);
	}
    }
  else
    std::cerr << "Error: this file does not exist" << std::endl;
  infile.close();
}

LoadMap::~LoadMap()
{

}
