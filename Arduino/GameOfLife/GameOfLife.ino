//notes:
//complete checklife function
//find the millis for next gen calculation
//find led grid

//100x100 is too much memory for nano and mega
//mega can handle 30x30
const int lifeGridLengthX = 30;
const int lifeGridLengthY = 30;

int lifeGrid[lifeGridLengthX][lifeGridLengthY];
int nextGenGrid[lifeGridLengthX][lifeGridLengthY];

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("Begin lifeGrid init");
  Serial.println(millis());
  
  for (int x = 0; x < lifeGridLengthX; x++)
  {
    for (int y = 0; y < lifeGridLengthY; y++)
    {
      lifeGrid[x][y] = 0;
    }
  }
  
  Serial.println("Life Grid Initialization complete");
  Serial.println(millis());
  
  ShowLifeGrid();
  CreateRandomLife();
  ShowLifeGrid();
}

void CreateRandomLife()
{
  Serial.println("Creating a random life");
  for (int x = 0; x < lifeGridLengthX; x++)
  {
    for (int y = 0; y < lifeGridLengthY; y++)
    {
      lifeGrid[x][y] = random(0, 2); //pick 0 or 1
    }
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  CalculateNextGenLifeGrid();
  //ShowLifeGrid();
  delay(250);
}

void CalculateNextGenLifeGrid()
{
  Serial.println("Begin next gen calc");
  Serial.println(millis());
  for (int y = 0; y < lifeGridLengthY; y++)
  {
    for (int x = 0; x < lifeGridLengthX; x++)
    {
      int newLife = CheckLife(x, y);
      nextGenGrid[x][y] = newLife;
    }
  }
  
  //lifeGrid = nextGenGrid;
  
  //copy nextGenGrid to lifeGrid
  //if there is no difference, end of game
  bool newGrid = false;
  for (int x = 0; x < lifeGridLengthX; x++)
  {
    for (int y = 0; y < lifeGridLengthY; y++)
    {
      if (lifeGrid[x][y] = nextGenGrid[x][y])
      lifeGrid[x][y] = nextGenGrid[x][y];
    }
  }
  
  Serial.println("End next gen calc");
  Serial.println(millis());
}

//check the number of surrounding life and determine whether to live, die, or born.
int CheckLife(int lifeX, int lifeY)
{
  int surroundingLifeCount = 0;
  
  //checking the 3x3 around the life
  //skip the middle of 3x3 (current life)
  //and allow overflow (if the life is at the left most edge, the left life is at the far right)
  
  for (int offsetY = -1; offsetY < 2; offsetY++)
  {
    for (int offsetX = -1; offsetX < 2; offsetX++)
    {
      int checkX = lifeX + offsetX;
      int checkY = lifeY + offsetY;
      
      //this is the center of the 3x3, which is the life we are checking for
      if (offsetX == 0 && offsetY == 0)
      {
        //skip
      }
      else
      {
        //apply the offset and correct the overflow
        
        //if the life is at left edge, overflow to right
        if (checkX < 0)
        {
          checkX += lifeGridLengthX;
        }
        //if at the right edge, overflow to left
        else if (checkX == lifeGridLengthX)
        {
          checkX -= lifeGridLengthX;
        }
        
        if (checkY < 0)
        {
          checkY += lifeGridLengthY;
        }
        else if (checkY == lifeGridLengthY)
        {
          checkY -= lifeGridLengthY;
        }
        
        if (lifeGrid[checkX][checkY] == 1)
        {
          surroundingLifeCount++;
        }
      }
    }
  }
  
  /*
  Serial.println("the life at");
  Serial.print("x = ");
  Serial.println(lifeX);
  Serial.print("y = ");
  Serial.println(lifeY);
  Serial.print("Surrounding count = ");
  Serial.println(surroundingLifeCount);
  */
  //return surroundingLifeCount;
  
  //fewer than 2 neighbor == dead
  if(surroundingLifeCount < 2)
  {
    return 0;
  }
  //more than 3 == dead
  else if (surroundingLifeCount > 3)
  {
    return 0;
  }
  //born if 3 near by
  else if (surroundingLifeCount == 3)
  {
    return 1;
  }
  //if 2, continue as is
  else
  {
    return lifeGrid[lifeX][lifeY];
  }
}

void ShowLifeGrid()
{
  Serial.println("Begin ShowLifeGrid");
  Serial.println(millis());
  for (int y = 0; y < lifeGridLengthY; y++)
  {
    for (int x = 0; x < lifeGridLengthX; x++)
    {
      Serial.print(lifeGrid[x][y]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  
  Serial.println("End ShowLifeGrid");
  Serial.println(millis());
}
