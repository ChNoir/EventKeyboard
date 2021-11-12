#pragma once
#include <thread>
#include <mutex>
#include <conio.h>


struct KeyCode
{
	enum Key_presse {


		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		ECHAP = 27,
		SPACE = 32,
		ENTRE = 13,
		POINT = 46,
		EGALE = 13,
		PLUS = 43,
		MOIN = 45,
		FOIS = 42,
		SLASH = 47,


		a = 97,
		b = 98,
		c = 99,
		d = 100,
		e = 101,
		f = 102,
		g = 103,
		h = 104,
		i = 105,
		j = 106,
		k = 107,
		l = 108,
		m = 109,
		n = 110,
		o = 111,
		p = 112,
		q = 113,
		r = 114,
		s = 115,
		t = 116,
		u = 117,
		v = 118,
		w = 119,
		x = 120,
		y = 121,
		z = 122,

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		_0 = 48,
		_1 = 49,
		_2 = 50,
		_3 = 51,
		_4 = 52,
		_5 = 53,
		_6 = 54,
		_7 = 55,
		_8 = 56,
		_9 = 57,

		
		
	};

};


class EventKeyboard
{
public :
	EventKeyboard();
	~EventKeyboard();
	
	// lanche la recuperation des touche tape, deja fait dans le constructeur.
	void run();
	// arrete la recuperation des touche taoe, deja fait dans le déconstruteur
	void stop();

	/// Recupere le code de la touche tape sans block le programe, elle renvoit -1 si il y a rien .
	int getKey();

	/// Recuper le code de la touche tape sans block le programe et que elle sois dans la list , elle revoit -1 si il y a rien. 
	int getKey(std::string WhiteList, bool inverseur = 1);
	
	/// Retrun 1 si la conditions est ok, ou si non 0  
	bool Eventkey(int conditions);

	/// Retrun 1 si la conditions est ok et lance la function, ou si non 0 et rien   
	template<typename T>
	static bool EventKey(int conditions, T(*Fun)()) {
		if (getKey() == conditions) {
			Fun();
			return true;
		}
		return false;
	}

	
private:

	void RunFun();
	
	static int key ;
	static bool keyChange;
	static bool getRun;
	static std::mutex mt;
	static std::thread* th;

};

namespace Events {

	template<typename T, typename R>
	/// Retrun 1 si la conditions est ok avec l'event et lance la function, ou si non 0 et rien.
	static bool C_connector(R Event, R conditions, T(*Fun)()) {

		if (Event == conditions) {
			
			Fun();
			return true ;
		}
		return false;
		
	}

	template<typename T, typename R>
	/// Retrun 1 si la conditions est ok avec l'event et lance la function avec le retoure de la function (callback), ou si non 0 et rien 
	static bool C_connector(R Event, R conditions, T(*Fun)(), T &callback_Fun) {

		if (Event == conditions) {

			callback_Fun = Fun();
			return true;
		}
		return false;

	}

	template<typename R>
	/// Retrun 1 si la conditions est ok avec l'event , ou si non 0 et rien 
	static bool C_connector(R Event, R conditions) {

		if (Event == conditions) {
			return true;
		}
		return false;

	}


}