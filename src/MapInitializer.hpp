#ifndef		__MAP_INITIALIZER__
#define		__MAP_INITIALIZER__

#include	<map>

template<typename T, typename U>
class MapInitializer
{
public:
  MapInitializer(T key, U value)
  {
    _map[key] = value;
  }

  ~MapInitializer() {};

  MapInitializer& operator()(T key, U value)
  {
    _map[key] = value;
    return (*this);
  }

  operator std::map<T, U> const &() const
  {
    return (_map);
  }

private:
  MapInitializer();
  MapInitializer(const MapInitializer &);
  MapInitializer &operator=(const MapInitializer &);

  std::map<T, U> _map;
};

#endif
