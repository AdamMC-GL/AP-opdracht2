#include <stdio.h>
#include <iostream> 
#include <map>
#include <vector>
#include <random>
#include <time.h>
using namespace std;



class Node{
public:
	string node_name;
	bool end_node;
	vector<string> wins_to;
	
	vector<float> jump_chance;
	vector<Node> connected;

	Node next_node(){

		float randomnr = ((float) rand() / (RAND_MAX));
		
		for(unsigned int i = 0; i < jump_chance.size(); i++){
			randomnr = randomnr - jump_chance[i];
			if (randomnr <= 0){
				return connected[i];
			}
		}
	}

public:
	void connect(Node node, float chance){
		connected.push_back(node);
		jump_chance.push_back(chance);
	}
	void multi_connect(vector<Node> nodes, vector<float> chance){
		for(unsigned int i = 0; i < nodes.size(); i++){
			connected.push_back(nodes[i]);
			jump_chance.push_back(chance[i]);
		}
	}

	string play_game(string move){

		
		if (end_node != false){
			
			string returnstr = "You played: " + move + "\n The PC played: " + node_name + "\n";
			if(move == node_name){
				returnstr += "Tie";
				return returnstr;
			}
			
			for(unsigned int i = 0; i < wins_to.size(); i++){
				
				if (wins_to[i] == move){
					returnstr += "You lose";
					return returnstr;
				
				}
			}
			returnstr += "You win";
			return returnstr;
		}

		return next_node().play_game(move);
		
	}
	
};


int main()
{
	srand(time(NULL));
	Node n0 {"n0", false};
	Node n1 = {"n1", false};
	Node n2 = {"n2", false};
	Node n3 = {"n3", false};
	Node n4 = {"n4", false};
	Node n5 = {"n5", false};

	//end nodes
	Node scissors = {"scissors", true, {"lizard", "paper"}};
	Node paper = {"paper", true, {"rock"}};
	Node rock = {"rock", true, {"lizard", "scissors"}};
	Node lizard = {"lizard", true, {"paper"}};
	
	
	n0.multi_connect({n1, n2}, {0.5, 0.5});
	n1.multi_connect({n3, n4}, {0.5, 0.5});
	n2.multi_connect({n4, n5}, {0.5, 0.5});
	
	cout << n2.jump_chance.size() << "\n";
	
	//connected with ends
	n3.multi_connect({rock, paper}, {0.5, 0.5});
	n4.multi_connect({paper, lizard}, {0.5, 0.5});
	n5.multi_connect({lizard, scissors}, {0.5, 0.5});
	
	cout << n0.play_game("scissors");
	
	


}
