#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 


/* this function calculates the height of the net
*/
int calculate_net_height(int ft,int inches)
{
	
	int newheight;
	newheight = (12*ft)+inches;
	return newheight;

}


/* this function throws the ball at a random height with the rand function
*/
int throw_ball(int netheight)
{
    /* sets the random number to ball and random number
    should be between 0 and the netheight +16
    */

    int net = netheight+17;	
    int ball = rand()%net;
    return ball;

}
/* this function checks to see if the name inputted is valid and doesnt have 
any numbers or other speacial CHARACTERS
*/
int is_name_valid(char name[])
{
    int i;
   /* checks the length of the name to make sure its not greater than 7 
   */
    if(strlen(name)>7)
    {
        
        return 0;
    }
   else
   {
       for( i=0 ;name[i]!='\0';i++)
       {
	       
           if((name[i] >= 65 && name[i]<=90) || (name[i]>= 97 && name[i]<=122) ||name[i] == 32)

           {

                continue;

           
	   }
	   else
	   {
		return 0;
	   }
	  
           
       }

       return 1;
   }
    
}

/* use the values of the main and pass them in to the parameters of gmaelogic
* implemnt game logic then call the gamelogic function in the main
*/



int is_valid_seed(char inSeed[])
{
  int i;
  int seed;
  
 for(i=0;inSeed[i]!='\0';i++)
 {
	 /*checks if the seed is a number using the ascii table values
	*/
	 if((inSeed[i]>=48&&inSeed[i]<=57)||inSeed[i]=='\n')
	 {
		
		continue;
	 }
	 else
	 {
		return 0;
	 }
 }
/* checks if the seed is not greater than 5 numbers or less than 1
  */
    sscanf(inSeed,"%i",&seed);
    if (seed>=1 && seed<=99999)
    {
        return 1;
    }
    else
    {
	    return 0;
    }
    
    
}


int game_logic(char name[],int seed,int netHeight,int total_points)
{
    char inBet[20];
    char inYN[20];
    char ans;
    int compPoints=75;
    int ballheight, newthrow;
    int bet;
    int compthrow,newcompthrow;
    /* while loop so when the total points or the computer points are more than 0 it keeps running
   */
    while (total_points>0 && compPoints>0)
    {
	    
	    printf("%s's turn. How much would you like to bet towards your throw? \n",name);
	    fgets(inBet,20,stdin);
   	    sscanf(inBet,"%i",&bet);
   	    while((bet>11||bet<1)||bet>total_points)
    	{
    	    	    printf("your bet was not within the valid range of [1, 11] or you attempted to bet more points than youcurrently have. Please enter a valid bet: \n");
		    fgets(inBet,20,stdin);
        	    sscanf(inBet,"%i",&bet);

   	    }
	   
   	    printf("	bet %i points\n",bet);
	    /* sets ball heihgt to throw the ball function and the nethwhight as the seed*/     
	    ballheight = throw_ball(netHeight);
	/* checks if the ball height is greater than the netheight and if it is subtract the amount betted
        */
	if(ballheight>netHeight)
        {
            total_points = total_points-bet;
            printf("	Ball height: %i inches, the ball is over the net\n",ballheight);
	        printf("	Deducting %i Points\n",bet);
            printf("	%s now has %i points\n",name,total_points);
	  
        }
	/* else check if the ball height is less than or equal to the netheight
	 * then check if it half the nets size, and if it is you have the option to rethrow the ball
	 */
        else if(ballheight<=netHeight)
        {
            if(ballheight<=((netHeight/2)))
            {
                printf("	Ball height: %i inches, Throw again? Type Y or N:\n",ballheight);
                fgets(inYN,20,stdin);
                sscanf(inYN,"%c",&ans);
                if (ans=='Y')
                {
                   newthrow= throw_ball(netHeight);
                    if(newthrow>netHeight)
                    {
                        total_points=total_points-bet;
			            printf("	Ball height: %i inches, the ball is over the net\n",newthrow);
                        printf("	Deducting %i Points\n",bet);
			            printf("	%s now has %i points\n",name,total_points);
                        
                    }
                    else
                    {
                        total_points=total_points+4;
			            printf("	Ball height: %i inches, ball is below the net\n",newthrow);
                        printf("	Adding %i Points\n",4);
			            printf("	%s now has %i points\n",name,total_points);
                        
                    }
                }
                else if( ans=='N')
                {
                    total_points=total_points+bet;
                    printf("	Adding %i Points\n",bet);
		            printf("	%s now has %i points\n",name,total_points);
                    
                }
                else 
                {	
                    
                    while(ans!='Y'||ans!='N')
		            {
			            printf("	please enter either Y or N");
               			fgets(inYN,20,stdin);
               			sscanf(inYN,"%c",&ans);
		            }

                }
            }
/*
 * if it dosent meet the requirments to rethrow do this
 */
	    else
	    {
            total_points=total_points+2;
           	printf("	Ball height: %i\n",ballheight);
		    printf("	Adding %i Points\n",2);
		    printf("	%s now has %i points\n",name,total_points);
	    }
	    
        }
	if(total_points==0)
	{
		return 1;
		exit(1);

	}
	/*
	 * this portion is the computer or Ai implementation
	 */
	printf("Computers turn\n");
       	compthrow=throw_ball(netHeight);
        if(compthrow>netHeight)
        {
            compPoints=compPoints-9;
            printf("	Ball height: %i inches, the ball is over the net\n",compthrow);
            printf("	Deducting %i Points\n",9);
            printf("	Computer now has %i points\n",compPoints);

        }
        else if (compthrow<=netHeight)
        {
		
		 
            if(compthrow<=(netHeight/2))
            {
                printf("	Ball height: %i inches, ball is below the net, throwing once more\n",compthrow);
                newcompthrow=throw_ball(netHeight);
		        if(newcompthrow<=netHeight)
                {
                    compPoints=compPoints+6;
                    printf("	Ball height: %i inches, ball is below the net\n",newcompthrow);
                    printf("	Adding %i Points\n" ,6);
                    printf("	Computer now has %i points\n",compPoints);


                }
                else{
                    compPoints=compPoints-7;
                    printf("	Ball height: %i inches, the ball is over the net\n",newcompthrow);
                    printf("	Deducting %i Points\n",7);
                    printf("	Computer now has %i points\n",compPoints);

                }

            }

	    else
	    {
	        compPoints=compPoints+4;
        	printf("	Ball height: %i inches, ball is below the net\n",compthrow);
            printf("	Adding %i Points\n",4);
            printf("	Computer now has %i points\n",compPoints);
	}
        }



    }
    if(compPoints<=0)
    {
        return 0;
    }
    else{
        return 1;
    }
    



}




int main()
{
    char inBuff[20];
    char name[20];
    int seed;
    int height;
    int inheight;
    int netHeight;
    int total_points=75,chance=3;
    int game;
    char YN;
    char inSeed[20];
    int count=0;
    int compcount=0;
    char iname[30];
     int namevalid; 
    printf("Welcome to the Gehntoo game\n");
    printf("Enter your name\n");
    fgets(iname,20,stdin);
    sscanf(iname,"%[^\n]",name);
   
    /*
     * checks if the name is valid with the is_name_valid function
     * then if namevalid is not equal to 1 reask the user to enter a
     * valid name
     */
    namevalid= is_name_valid(name);
   	
    	
    while(namevalid==0)
    {
        printf("please enter a valid name that contains only letters and spaces \n");
	fgets(iname,20,stdin);
    	sscanf(iname,"%[^\n]",name);
	namevalid=is_name_valid(name);

	
    }
    /*asks for the seed vlaue
     */
    printf("Enter a seed value to use in the range of [1-99999]\n");
    fgets(inSeed,20,stdin);
    while(is_valid_seed(inSeed)==0)
    {
            printf("Invalid seed, please enter a new seed value in the range [1-99999]\n");
   	    fgets(inSeed,20,stdin);
   	    
    }
    sscanf(inSeed,"%i",&seed);
    printf("Seed value to use is %i\n",seed); 
    srand(seed);
/* gets the height in ft and in inches then converts it all to inches using the calculate _net_height
 */
    printf("Enter the height of the net in feet and inches [xxft xxin] where xx must be [1-99]\n");
    fgets(inBuff,20,stdin);
    sscanf(inBuff,"%ift%iin",&height,&inheight);
    netHeight =calculate_net_height(height,inheight);
    printf("Height of the net: %i inches\n",netHeight);
    printf("Each player is starting with 75 points\n");
    
    
	/* while the user has more than 0 chances keep running
	 */
    while(chance>0)
    {
	    /* calls the game logic function and runs untill a winner is decided
	     */
        game=game_logic(name,seed,netHeight,total_points);
        if(game==0)
        {
            chance--;
	    compcount++;
            printf("Computer won! want to try again Y or N ? trys remaining %i\n",chance);
            fgets(inBuff,20,stdin);
            sscanf(inBuff,"%c",&YN);
	    /*
	     * asks if the player wants to play again
	     */
            if(YN == 'Y')
            {
                continue;
            }
            else{
                printf("%s chose not to play again. Thanks for playing!",name);
                printf("Printing out game statistics now:\n");
                printf("        %s won a total of %i time(s)\n",name,count);
                printf("        Computer won a total of %i time(s)\n",compcount);
                break;
            }

        }
        if(game==1)
        {
	    count++;
            printf("%s has won the current game, congratulations!\n",name);
       	    printf("Would you like to play again %s? Type Y or N:\n" ,name);
            fgets(inBuff,20,stdin);
            sscanf(inBuff,"%c",&YN);
            if(YN == 'Y')
            {
                continue;
            }
            else if (YN=='N'){
                printf("%s chose not to play again. Thanks for playing!\n",name);
                printf("Printing out game statistics now:\n");
		printf("	%s won a total of %i time(s)\n",name,count);
		printf("	Computer won a total of %i time(s)\n",compcount);
		break;
            }
	    
	    
        }
	
    }
    /* if player ran out of chances print this meassage
     */

    if(chance==0)
    {

	   printf("You ran out of chances thanks for playing Gehntoo\n");
    }



	return 0;
}
