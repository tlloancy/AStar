
#include "noeud.h"


AStar::AStar()
{
}

AStar::AStar(AStar const & rhs)
{
	*this = rhs;
}

AStar::~AStar()
{
}

AStar	& AStar::operator=(AStar const & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}


int main(int argc, char **argv)
{
	AStar	astar;
	astar.run();
}


float AStar::distance(int _x1, int _y1, int _x2, int _y2)
{
	return sqrt((_x1 - _x2) * (_x1 - _x2) + (_y1 - _y2) * (_y1 - _y2));
	//return (_x1-_x2)*(_x1-_x2) + (_y1-_y2)*(_y1-_y2);
}


/*
   ajoute toutes les cases adjacentes à n dans la std::liste ouverte
 */
void AStar::ajouter_cases_adjacentes(std::pair <int,int>& n)
{
	_noeud tmp;

	// on met tous les _noeud adjacents dans la std::liste ouverte (+vérif)
	for (int i = n.first - 1; i <= n.first + 1; i++)
	{
		if ((i < 0) || (i >= _s->w))
			continue;
		for (int j = n.second - 1; j <= n.second + 1; j++)
		{
			if ((j < 0) || (j >= _s->h))
				continue;
			if ((i == n.first) && (j == n.second))  // case actuelle n
				continue;

			if (*((Uint8 *)_s->pixels + j * _s->pitch + i * _s->format->BytesPerPixel) == _NOIR)
				// obstace, terrain non franchissable
				continue;

			std::pair<int,int> it(i,j);

			if (!deja_present_dans_liste(it, _liste_fermee))
			{
				/* le _noeud n'est pas déjà présent dans la std::liste fermée */

				tmp._cout_g = _liste_fermee[n]._cout_g + distance(i,j,n.first,n.second);
				tmp._cout_h = distance(i,j,_arrivee._x,_arrivee._y);
				tmp._cout_f = tmp._cout_g + tmp._cout_h;
				tmp._parent = n;

				if (deja_present_dans_liste(it, _liste_ouverte))
				{
					/* le _noeud est déjà présent dans la std::liste ouverte, il faut comparer les std::couts */
					if (tmp._cout_f < _liste_ouverte[it]._cout_f)
					{
						/* si le nouveau _chemin est meilleur, on update */
						_liste_ouverte[it]=tmp;
					}

					/* le _noeud courant a un moins bon _chemin, on ne change rien */


				}
				else
				{
					/* le _noeud n'est pas présent dans la std::liste ouverte, on l'ajoute */
					_liste_ouverte[std::pair<int,int>(i,j)]=tmp;
				}
			}
		}
	}
}

bool AStar::deja_present_dans_liste(std::pair<int,int> n, _l_noeud& l)
{
	_l_noeud::iterator i = l.find(n);
	if (i==l.end())
		return false;
	else
		return true;
}

/*
   fonction qui renvoie la clé du meilleur _noeud de la std::liste
 */
std::pair<int,int> AStar::meilleur_noeud(_l_noeud& l)
{
	float m_coutf = l.begin()->second._cout_f;
	std::pair<int,int> m_noeud = l.begin()->first;

	for (_l_noeud::iterator i = l.begin(); i!=l.end(); i++)
		if (i->second._cout_f< m_coutf){
			m_coutf = i->second._cout_f;
			m_noeud = i->first;
		}

	return m_noeud;
}

/*
   fonction qui passe l'élément p de la std::liste ouverte dans la fermée
 */
void AStar::ajouter_liste_fermee(std::pair<int,int>& p)
{
	_noeud& n = _liste_ouverte[p];
	_liste_fermee[p]=n;

	// il faut le supprimer de la std::liste ouverte, ce n'est plus une solution e_xplorable
	if (_liste_ouverte.erase(p)==0)
		std::cerr << "n'apparait pas dans la std::liste ouverte, impossible à supprimer" << std::endl;
	return;
}

/*
   fonction qui met
   en bleu toutes les cases du _chemin final
 */
void AStar::ecrire_bmp()
{
	std::list<_point>::iterator j;

	for (j=_chemin.begin(); j!=_chemin.end(); j++)
		colorerPixel(j->_x,j->_y,_BLEU);

	std::cout << "_chemin final de longueur " << _chemin.size() << std::endl;
	std::cout << "dernière std::liste ouverte : " << _liste_ouverte.size() << " éléments" << std::endl;
	std::cout << "dernière std::liste fermee : " << _liste_fermee.size() << " éléments" << std::endl;

	SDL_SaveBMP(_s, "resultat.bmp");
}

void AStar::colorerPixel(int _x, int _y, Uint32 pixel)
{
	/* p est l'adresse du pi_xel que l'on veut modifier */
	Uint8 *p = (Uint8*)_s->pixels + _y * _s->pitch + _x * _s->format->BytesPerPixel;

	if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
		p[0] = (pixel >> 16) & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = pixel & 0xff;
	}else{
		p[0] = pixel & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = (pixel >> 16) & 0xff;
	}
}


void AStar::retrouver_chemin()
{
	// l'arrivée est le dernier élément de la std::liste fermée.
	_noeud& tmp = _liste_fermee[std::pair<int, int>(_arrivee._x,_arrivee._y)];

	struct _point n;
	std::pair<int,int> prec;
	n._x = _arrivee._x;
	n._y = _arrivee._y;
	prec.first  = tmp._parent.first;
	prec.second = tmp._parent.second;
	_chemin.push_front(n);

	while (prec != std::pair<int,int>(_depart._parent.first,_depart._parent.first)){
		n._x = prec.first;
		n._y = prec.second;
		_chemin.push_front(n);

		tmp = _liste_fermee[tmp._parent];
		prec.first  = tmp._parent.first;
		prec.second = tmp._parent.second;
	}
}

// end of file

