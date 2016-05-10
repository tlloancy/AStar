
#include "noeud.h"

int AStar::run()
{
	_s = SDL_LoadBMP("big.bmp");
	if(!_s){
		std::cerr << "erreur lors du chargement du bmp de départ" << std::endl;
		return 1;
	}
	_NOIR  = SDL_MapRGB(_s->format, 0        , 0        , 0);
	_BLEU  = SDL_MapRGB(_s->format, 0        , 0        , (char)255);
	_BLANC = SDL_MapRGB(_s->format, (char)255, (char)255, (char)255);
	_ROUGE = SDL_MapRGB(_s->format, (char)255, 0        , 0);

	_arrivee._x = _s->w-1;
	_arrivee._y = _s->h-1;

	_depart._parent.first  = 0;
	_depart._parent.second = 0;

	std::pair <int,int> courant;

	/* déroulement de l'algo A* */

	courant.first  = 0;
	courant.second = 0;
	// ajout de courant dans la std::liste ouverte

	_liste_ouverte[courant]=_depart;
	ajouter_liste_fermee(courant);
	ajouter_cases_adjacentes(courant);


	while( !((courant.first == _arrivee._x) && (courant.second == _arrivee._y))
			&&
			(!_liste_ouverte.empty())
	     )
	{

		// on cherche le meilleur noeud de la std::liste ouverte, on sait qu'elle n'est pas vide donc il e_xiste
		courant = meilleur_noeud(_liste_ouverte);

		// on le passe dans la std::liste fermee, il ne peut pas déjà _y être
		ajouter_liste_fermee(courant);

		ajouter_cases_adjacentes(courant);
	}

	if ((courant.first == _arrivee._x) && (courant.second == _arrivee._y)){
		retrouver_chemin();

		ecrire_bmp();
	}
	else
	{
		/* pas de solution */
	}

	return 0;

}
