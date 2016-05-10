
#ifndef __noeud_h__
#define __noeud_h__
#include <string>

#include <iostream>
#include <SDL/SDL.h>
#include <cmath>
#include <map>
#include <list>
#include <utility>
class AStar
{
	public:
		AStar();
		~AStar();

		int	run();
	private:
		AStar	& operator=(AStar const & rhs);
		AStar(AStar const & rhs);
		struct _noeud {
		float _cout_g; 
		float _cout_h;
		float _cout_f;
		std::pair<int,int> _parent;    // 'adresse' du parent (qui sera toujours dans la map fermée
		};
		struct _point {
		int	_x;
		int	_y;
		};
		typedef std::map< std::pair<int,int>, _noeud> _l_noeud;

		_l_noeud _liste_ouverte;
		_l_noeud _liste_fermee;
		std::list<_point> _chemin;

		struct _point _arrivee;
		_noeud _depart;

		float distance(int, int, int, int);
		void ajouter_cases_adjacentes(std::pair<int,int>&);
		bool deja_present_dans_liste( std::pair<int,int>,
				_l_noeud&);
		std::pair<int,int> meilleur_noeud(_l_noeud&);
		void ajouter_liste_fermee(std::pair<int,int>&);
		void ecrire_bmp();
		void colorerPixel(int, int, Uint32);
		void retrouver_chemin();

		Uint32 _BLANC; 
		Uint32 _NOIR; 	
		Uint32 _BLEU; 
		Uint32 _ROUGE;
		SDL_Surface *_s;

};

#endif
