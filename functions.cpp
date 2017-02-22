#include "functions.h"

/*returns a List of all sub-terms of the ginen lambda term*/
List*  num_Lambda(string s){
	int i=0,count=0,n=0,j=0;
	string lambda="";
	List* lista=new List;
	bool flag=false;
	
	if(s[0]=='\0'){/*end of string*/
		return lista;
	}
	else if(s[0]=='\\'){/*scope is all the string*/
		lista->push(s);
		return lista;
	}
	else if(s[0]=='('){/*insert in the list all the score of the parenthesis and then make recursive call*/

		while(s[i] != '\0'){

			if(s[i]=='('){
				count ++;
			}
			else if(s[i]==')'){
				count --;
				if(count==0)
				{

					lista->push(lambda);
					lambda="";
					i++;
					while(s[i]==' ')
						i++;
					flag=false;
					n++;
					return *lista+*num_Lambda(s.substr(i));
					continue;
				}
			}
			if(!(s[i]=='(' && lambda.length()==0 && flag==false))
				lambda +=s[i];
			else
				flag=true;
			i++;
		}
	}
	else if ((s[0]>=65 && s[0]<=90) || (s[0]>=97 && s[0]<=122) )
	{
		lambda="";

		for ( j = 0; j < s.length(); j++)/*catch whole variable*/
		{
			if((s[j]>=65 && s[j]<=90) || (s[j]>=97 && s[j]<=122))
				lambda+=s[j];
			else
				break;
		}

		lista->push(lambda);
		
		return (*lista+*num_Lambda(s.substr(j)));
	}
	
	else if(s[0]==' ')/*ignore spaces*/
		return num_Lambda(s.substr(1));

}

/*returns the List of free variables the ginen lambda term*/
List* free_variables(string str)
{
	List *FV=new List,*list;
	Node* node;
	bool flag=false;
	string s,head="",type,part;
	int i=0;
	
	str = remove_outer_parenthesis(str);
	type = get_type(str);

	if(type=="abstruction")/*if string is abstruction*/
	{
		head = get_head(str);
		i = get_body_position(str);
		
		list = free_variables(str.substr(i));
		node = list->get_start();
		
		for (int i = 0; i < list->get_size(); i++)/*free variables are the free variables of the subterms wich are different from head*/
		{
			s = node->get_lambda();
			if( s!=head && FV->contains(s)==false)
				FV->push(s);
			
			node->get_next(node);
		}
		return FV;
		
	}
	else if(/*str.length()==1 && ((str[0]>=65 && str[0]<=90) || (str[0]>=97 && str[0]<=122))*/isOneVariable(str)==true)/*if it is variable*/
	{
		//s=str[0];
		//FV->push(s);
		FV->push(str);
		return FV;
	}
	else/*if it is application*/
	{
		list = num_Lambda(str);
		node = list->get_start();
		
		for (int i = 0; i < list->get_size(); i++)/*the List of free variables is the summary of free-variable-list of all subterms*/
		{	
			part = remove_outer_parenthesis(node->get_lambda());
			FV  = *FV + *(free_variables(part));
			
			node->get_next(node);
		}
		return FV;
	}
}

/*returns the List of reserved variables the ginen lambda term*/
List* reserved_variables(string str)
{
	List *reserved_var=new List, *FV;
	string s="";
	
	FV = free_variables(str);
	
	for (int i = 0; i < str.length(); i++)
	{		
		if( ((str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122)))/*if str[i] is variable and is not free-variable*/
			s+=str[i];
		else 
		{
			if (isOneVariable(s)==true && FV->contains(s)==false && reserved_var->contains(s)==false)
				reserved_var->push(s);
			s="";
		}
			
	}
	return reserved_var;
}

/*returns the List of common elements of the given Lists L1,L2*/
List* get_touches(List* L1,List* L2)
{
	Node *ptr=0;
	List *touches=new List;
	string s;

	if (L1!=0 && L2!=0)
	{
		ptr=L1->get_start();
		
		while (ptr!=0)
		{
			s=ptr->get_lambda();
			
			if (L2->contains(s)==true)
			{
				touches->push(s);
			}
			
			ptr->get_next(ptr);
		}
				
	}

	return touches;
}

/*renames all apperances of variable s1 with variable s2 in string str*/
string renameString(string str,string s1,string s2)
{
	string newStr="",s="";
	
	/*for (int i = 0; i < str.length(); i++)
	{
		temp=str[i];
				
		if (temp==s1)
			newStr += s2;
		else
			newStr += str[i];
		
	}*/

	for (int i = 0; i < str.length(); i++)
	{
		if( ((str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122)))
				s+=str[i];
		else 
		{
			if (isOneVariable(s)==true && s==s1)
				newStr += s2;
			else
				newStr += s;

			newStr+=str[i];	
			s="";
		}
	}
	return newStr;
}

/*removes all spaces at start and in the end of str*/
string cutString(string str)
{
	while (str[0]==' ')
		str = str.substr(1);

	while (str[(str.length())-1]==' ')
		str = str.substr(0,str.length()-1);
		

	return str;
}

/*returns the typw of given string ("application" or "abstruction")*/
string get_type(string str)
{
	int count=0;
	bool only_var=true;
	
	if(str[0]=='\\')
		return "abstruction";
	else
		return "application";
}

/*removes all unnecessary parenthesis of the string 
 * (e.g. if sentence="(((x)))" returns "x",if sentence="(((x (\y.y) k)))") returns "x (\y.y) k"*/
string remove_outer_parenthesis(string sentence)
{
	int count=0;
	
	for (int i = 0; i < sentence.length(); i++)
	{
		if(sentence[i]=='(')
			count++;
		else if(sentence[i]==')')
		{
			count--;
			
			if (count==0 && (i == sentence.length()-1) && sentence[0]=='(')
				return remove_outer_parenthesis(sentence.substr(1,sentence.length()-2));
			else if (count==0 && i < sentence.length()-1)
				break;
			
		}
	}
	return sentence;
}

/*
 //unnecessary function
string alpha_redex(string sentence,string new_var)
{
	string newExpr="",l,head;
	int count=0;
	List* FV=free_variables(sentence);
	
	if(FV->contains(new_var)==true)
		return sentence;
	
	head = sentence[1];

	for (int i = 0; i < sentence.length(); i++)
	{
		l = sentence[i];
		if(l=="(")
			count++;
		else if	(l==")")
			count--;
		
			
		if( l == head && count==0)
			newExpr += new_var;
		else	
			newExpr += sentence[i];
	}
	
	delete FV;
	
	return newExpr;
}
*/


string beta_redex(string s1,string s2,bool flag,string head)
{
	string newExpr="",s,type,rn,head2="";	
	List* list,*s1_FV,*s1_RV,*s2_FV,*var_to_rename;
	char c;
	Node* temp=0;
	bool rename=false;
	int n;
	
	s1=remove_outer_parenthesis(s1);
	s2=remove_outer_parenthesis(s2);
	/***************CHECK IF IT NEEDS TO BE RENAMED*******************/

	s1_FV = free_variables(s1);
	s1_RV = reserved_variables(s1);
	
	s2_FV = free_variables(s2);
	
	
	var_to_rename = get_touches((*s1_FV+ *s1_RV), s2_FV);

	temp = var_to_rename->get_start() ;
	
	while (temp!=0)
	{
		s = temp->get_lambda();

		for (int i = 97; i < 123; i++)
		{
			c=i;
			rn=c;
			if(s2_FV->contains(rn)==false && s1_FV->contains(rn)==false && s1_RV->contains(rn)==false)
			{
				newExpr = renameString(s1,s,rn);

				rename=true;
				s1=newExpr;
				
				break;
			}	
		}
		
		if (rename==false)
		{
			for (int i = 65; i < 97; i++)
			{
				c=i;
				s=c;
				if(s2_FV->contains(rn)==false && s1_FV->contains(rn)==false && s1_RV->contains(rn)==false)
				{
					newExpr = renameString(s1,s,rn);

					rename=true;
					s1=newExpr;
					
					break;
				}	
			}
		}
		
		if(rename==false)
		{
			cout<<"Unable to continue process...(ran out of variables)"<<endl;
			exit(0);
		}
		temp->get_next(temp);		
	}	
	/****************RENAME IS DONE (IF NECESSARY)*******************/
	
	type=get_type(s1);
	
	newExpr="";
	
	if (type=="abstruction")/*if the term is abstruction*/
	{		
		head2=get_head(s1);
		n=get_body_position(s1);
		
		if(head2 == head && flag==false)
			return s1;
		else
		{
			if(head==head2)
			{
				s = beta_redex(s1.substr(n),s2,false,head);
				s=heta_redex(s);
				return s;
			}
			else
			{
				s = beta_redex(s1.substr(n),s2,false,head);
				s=heta_redex(s);
				return "\\"+head2+"."+s;
			}
			
			
		}
	}
	else if (isOneVariable(s1)==true)/*if the term is variable (recursive calls stop here)*/
	{
		if(s1==head)
		{
			s2 = remove_outer_parenthesis(s2);

			if (isOneVariable(s2)==true)
				return s2;
			else
				return "("+s2+")";
		}
		else
			return s1;
	}
	
	else/*if the term is application*/
	{
		list = num_Lambda(s1);
		temp = list->get_start();
		
		for (int i = 0; i < list->get_size(); i++)
		{
			s = temp->get_lambda();
			
			s = beta_redex(s,s2,false,head);
			s=remove_outer_parenthesis(s);
			s = heta_redex(s);
			
			if (isOneVariable(s)==false)
				s = "(" + s + ")";
			
			newExpr +=" "+ s;
			
			temp->get_next(temp);
		}
		
		return newExpr;
	}
}

/*check if the last subterm is equal with the head*/
string heta_redex(string sentence)
{
	List *list=0;
	int n,body;
	string newExpr="",s, head;
	Node* node;
	
	sentence = remove_outer_parenthesis(sentence);

	if(get_type(sentence)=="abstruction")
	{
		
		head=get_head(sentence);
		body=get_body_position(sentence);
		
		list=num_Lambda(sentence.substr(body));
		n=list->get_size();
		
		if(n>1)
		{
			if(remove_outer_parenthesis(list->get_last()->get_lambda()) == head )
			{
							
				node=list->get_start();

				for (int i = 0; i < list->get_size()-1; i++)
				{
					s = node->get_lambda();
					
					if (isOneVariable(s)==false)
						s="(" + s + ")";
						
					newExpr += " "+s;
					node->get_next(node);
				}
				
				newExpr = cutString(newExpr);
				return newExpr;
			}
		}
	}

	return sentence;
}

/*transfomrs the given lambda-term to its normalized form*/
string normalize(string lambda)
{
	List *list=0;
	string type="",result="",newExpr="",s="",temp="",head="";
	bool applications=true;
	Node* node=0;
	int body;
	
	
	lambda=cutString(lambda);
	lambda=remove_outer_parenthesis(lambda);
	lambda=cutString(lambda);
	type = get_type(lambda);
	
	if (type=="abstruction")/*if lambda is abstruction*/
	{
		head=get_head(lambda);
		body=get_body_position(lambda);
		
		result=normalize(lambda.substr(body));/*normalize the body*/
		result=heta_redex(result);
		lambda = heta_redex("\\"+head+"."+result);/*concatenate result with "\x." and make heta redauction*/

		return lambda;
	}
	else if (isOneVariable(lambda)==true)/*if lambda is a variable,return lambda.recursive calls stop here*/
	{
		return lambda;
	}
	
	else /*if lambda is application,1)apply the normalized-second term to he normalized-first 
									2)format the new string
									3)make recursive call fro the new string*/
	{
		list = num_Lambda(lambda);
		node=list->get_start();
		
		
		s=heta_redex(remove_outer_parenthesis(node->get_lambda()));
		s=normalize(s);
		s=heta_redex(s);
		s=remove_outer_parenthesis(s);
		type = get_type(s);

		if (type=="abstruction")/*s (the normalized-first-subterm of given lambda) is abstruction*/
		{
			node->get_next(node);
			head = get_head(s);

			temp = heta_redex(normalize(heta_redex(node->get_lambda())));/*normalize the second subterms*/
			s = heta_redex(normalize(beta_redex(s,temp,true,head)));/*make the application*/
			newExpr = s;

			if (isOneVariable(newExpr)==false)
				newExpr = "("+ newExpr +")";
			
			node->get_next(node);
			for (int i = 0; i < list->get_size()-2; i++)/*concatenate the rest subterms with newExpr.then make recursive call*/
			{
				s=node->get_lambda();
				
				if (isOneVariable(s)==true)
					newExpr += " " + s;
				else
					newExpr += " (" + s + ")";
					
				node->get_next(node);
			}
			
			return normalize(newExpr);/*recursive call*/
			
		}
		else/*s (the normalized-first-subterm of given lambda) is application.
			In this situation,concatenate the rest normalized-subterms with the first subterm
			.Do not make any application,just put the normalized subterms side by side!*/
		{
			newExpr = s;

			for (int i = 0; i <list->get_size()-1 ; i++)
			{			
				node->get_next(node);
				s=remove_outer_parenthesis(node->get_lambda());
				heta_redex(s);
				s=normalize(s);
				s=heta_redex(s);
				
				if (isOneVariable(s)==false)
					s= "(" + s + ")";
					
				newExpr+= " " + s;
			}

			return newExpr;
		}
	}
}


bool isOneVariable(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if(!((str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122)))
			return false;
	}
	
	return true;
}
		
/*return the head of an abstruction*/		
string get_head(string str)
{
	string head="";
	
	for (int i = 1; i < str.length(); i++)
	{
		if((str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122))
			head += str[i];
		else if(str[i]=='.')
			break;
		else if(str[i]==' ')
			continue;
		else
		{
			cout<<"get_head:wrong input"<<endl;
			exit(0);
		}
	}
	
	return head;
}

/*return the body of an abstruction*/
int get_body_position(string str)
{
	string head="";
	
	for (int i = 0; i < str.length(); i++)
	{
		if(str[i]=='.')
			return i+1;
	}
	
	return -1;
}
