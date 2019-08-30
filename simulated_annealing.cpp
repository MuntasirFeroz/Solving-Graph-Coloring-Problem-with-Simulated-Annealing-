/*Written by: Muntasir Feroz & Redwan-ul Alam
id: 2015-1-60-058  && 2015-1-60-077
SUBJECT: Graph Coloring Problem solved by Simmulated annealing algorithm
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>//to use rand()
#include<math.h>
using namespace std;

// Number of vertices in the graph
#define TOTAL_NODE 5
#define INFINITY -1000000
#define ITERATION 20

struct color_node {
	int node_index;
	char color;
	//int weight;
}node[TOTAL_NODE],temp[TOTAL_NODE];

int graph[TOTAL_NODE][TOTAL_NODE];
//----------------------------------------------------------------FUNCTIONS-----------------------------------------------------
void initial_graph()
{
    /* Sets all nodes connection in graph to infinity */
    int i ,j;

    for(i=0;i<TOTAL_NODE;i++)
    {
        for(j=0;j<TOTAL_NODE;j++)
        {
            graph[i][j]=INFINITY;
        }//j for

    }//i for

}//end of initial graph
void print_node_color(struct color_node x[])
{
    /*prints color of eatch node with node no */
    for (int i=0;i<TOTAL_NODE;i++)
    {
        cout<<x[i].node_index<<" "<<x[i].color;
        cout<<endl;
    }//end of for

}//end of print_graph_with_node_color()

void print_graph()
{
    /*prints graph */
    int i,j;
    for ( i=0;i<TOTAL_NODE;i++)
    {

        for( j=0;j<TOTAL_NODE;j++)
        {
           cout<<graph[i][j]<<" ";

        }//for j

        cout<<endl;
    }//for i
    cout<<endl;

}//end of print_graph_with_node_color()

void print_graph_with_color(struct color_node x[])
{
    print_graph();
    print_node_color(x);

}//end for print_graph_with_color

void copy_color_Node(struct color_node x[], struct color_node y[])// node and temp
{
    /* This function is used to copy the nodes into a temporary node to copy
    the values of x into y ps:"can be used to copy the values of nodes to temp vice versa . ESP that
    changes can be made to temp during the annealing to create new states " */

    int i=TOTAL_NODE;
    for(i=0;i<TOTAL_NODE;i++)
    {
        y[i].node_index=x[i].node_index;
        y[i].color=x[i].color;
    }
}//end of copy


int check_charecter(char x , char y)
{
    //checks character if matches then return 1 or 0
    if(x==y)
        return 1;
    else
        return 0;

}//end of check_charecter

int costFunction(struct color_node x[], int lenght)
{
    int i,j,error=0;

    for(i=0;i<TOTAL_NODE;i++)
    {
        for(j=0;j<TOTAL_NODE;j++)
        {
            if(graph[i][j]==1 && graph[j][i]==1)
            {
                /* checking graph connection if 1 then there is connection between nodes*/
                if( check_charecter( x[i].color  , x[j].color ) == 1 &&  check_charecter( x[j].color , x[i].color ) == 1 )
                {
                    /* strmp() returns 0 if strings are equal .If equals then increase  error by 1*/
                error++;

                }

            }//end of graph checking


        }//end for j

    }//end for i

    return error/2;//since counting same error twice
}//end of costFunction()

void random_change(struct color_node x[])
{
    int change=rand()%TOTAL_NODE; //randomly choosing the node index to make change in

    int temp1;
    char changed_color;
    /* here 0=R , 1=G , 2=B color this is done by moding rand()
    by 3 cause there are 3 colors*/
    temp1=rand()%3;
  //  cout<<"VALUE OF temp1 "<<change<<endl;
    if(temp1==0)
    {
        changed_color='R';
    }//end of if
    else if(temp1==1)
    {
        changed_color='G';
    }//end of if else
    else
    {
        changed_color='B';
    }//end of else

    x[change].color=changed_color;// making the change

    copy_color_Node(x,temp);//coping the change in temp

}//end of random_change

double probability_function(int old_fitness ,int new_fitness ,int temp) //fitness
{
return exp((new_fitness-old_fitness)/temp);

}//end of probability_function
//---------------------------------------------------------------FUNCTIONS--------------------------------------------------------------

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++========= M A I N ======+++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main()
{


	int x_cordinate , y_cordinate ,old_cost,new_cost , i, j, x, y, index, num,no;
    char color;
    double probability;

    double temperature0=100,cooling_rate=.9;

	cout<< "COLOR GRAPH PRPBLEM WITH SIMULATED ANNEALING"<<endl;
	cout<< "---------------------------------------------"<<endl;

	initial_graph();//setting all connection to infinity at the beginning

	/*Reading values from file called graph.txt to set connection in graph */

	ifstream file("graph.txt");  // file containing graph connections

	while(file>>x>>y)
    {
        x_cordinate=x;
        y_cordinate=y;
        graph[x_cordinate][y_cordinate]=1; //graph cordinates

    }//end of file

    /*Reading values from file called color.txt or test_color.txt to set colors for
    node as the initial state  */

    ifstream file2("test_color.txt"); // file containing node color for the inistial state //other file : test_color.txt
    while(file2>>index>>color)
    {
      no=index;
      node[no].node_index=no;
      node[no].color=color;

    }//end of file2
cout<<"--INITIAL STATE-- "<<endl;
    print_node_color(node);
    old_cost=costFunction(node , TOTAL_NODE);

    cout<<"COST "<<old_cost<<endl;

    i=0;

    while(i<ITERATION)
    {
     cout<<endl<<"NO OF ITERATION = "<<i+1<<endl;
        random_change(node);
        new_cost=costFunction(temp , TOTAL_NODE);
        cout<<"-----TEMP-----"<<endl;
        cout<<"NEW COST"<<new_cost<<endl<<endl;
        print_node_color(temp);
        if(new_cost == 0)
        {
            old_cost=new_cost;
            copy_color_Node(temp,node);
            break;
        }
        else if(new_cost>old_cost)//if new cost is worst than old cost
        {
            probability=probability_function(old_cost,new_cost,temperature0)*10;
            probability=floor(probability);
            num=rand()%10;

            if(num<=probability)
            {
                old_cost=new_cost;
                copy_color_Node(temp,node);
            }


        }

    temperature0=temperature0*cooling_rate;
        i++;

    }//end of while

    cout<<endl<<"-------------------FINAL STATE-------------- :"<<endl;
    print_node_color(node);

    cout<<"COST "<<old_cost<<endl;

    return 0;

}//end of main
