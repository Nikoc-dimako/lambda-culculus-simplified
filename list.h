#include <iostream>
#include <cstring> 

using namespace std;

class Node {
	private:
			string lam;
			Node *next;
			Node *previous;
	public:
		Node(string s,Node *ptr=NULL,Node* prev=NULL):lam(s),next(ptr),previous(prev){}
		
		void take_lambda( string str){ lam=str; }
		void take_next( Node* pt){ next=pt; }
		void take_previous(Node* p){ previous=p; }
	
		string get_lambda() const{ return lam; }
		void get_next(Node* &p) const{ p=next; }
		void get_previous(Node* &ptr) const{ ptr=previous; }
};
			
class List{
	private:

			int size;
			Node* ptr;
			Node *start;
			Node *last;
	
	public:
			List():size(0),start(NULL),last(NULL),ptr(NULL){}
			List(const List &cp){
				Node*temp;
				
				temp=cp.start;
				start=last=NULL;
				size=0;
				
				while(temp!=NULL){
					push(temp->get_lambda());
					temp->get_next(temp);
				}
			}
			
			~List(){
				Node* temp=NULL;
				
				while(start!=NULL){
					start->get_next(temp);
					delete start;
					start=temp;
				}
				
			}
			
			List* operator+(const List &l){
				Node *temp;
				List *list=new List;
				temp=this->start;
				
				while(temp!=NULL){
					list->push(temp->get_lambda());
					temp->get_next(temp);
				}
				
				temp=l.start;
				
				while(temp!=NULL){
						list->push(temp->get_lambda());
					temp->get_next(temp);
				}
				
				return list;
				
			}
			
			/***********************************/
			
			int get_size(){ return size; }
			
			void push(const string s){
				Node *temp;
				
				temp = new Node(s);
				if(!size){
					ptr=temp;
					start=temp;
					last=start;
					size=1;
				}
				else{
						last->take_next(temp);
						temp->take_previous(last);
						last=temp;
						size++;
				}
			}

			void push_at_start(const string s){
				Node *temp=new Node(s);
				start->take_previous(temp);
				start=temp;
				size++;
			}

			void delete_at_start(){
				Node*temp=start;

				start->get_next(start);

				delete temp;
			}
			
			void printList(){
				Node *temp=start;
				while(temp!=NULL){
					cout << temp->get_lambda()<<endl;
					temp->get_next(temp);
				}
			}
			
			Node* get_start()
			{
				return this->start;
			}
			
			Node* get_last()
			{
				return this->last;
			}
			
			bool contains(string str)
			{
				Node *temp=this->start;
				string lambda;

				while(temp!=NULL)
				{
					lambda=temp->get_lambda();

					if(str==lambda)
					{
						return true;
					}
					
					temp->get_next(temp);
				}
				return false;
			}
			bool equal(List* li){
				Node* temp1,*temp2;
				temp1=start;
				temp2=li->get_start();
				if(size==li->get_size()){
					while(temp1!=NULL){
						if(temp1->get_lambda()==temp2->get_lambda()){
							temp1->get_next(temp1);
							temp2->get_next(temp2);
						}
						else
							return false;
					}
					return true;
				}
				else
					return false;

			}
};
