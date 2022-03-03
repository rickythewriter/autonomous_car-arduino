#include "motorfunc.h"

/*–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––/

  This function moves the car forward at a specified speed.

/–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

void forward (int ispeed) // ispeed between 0 and 255
{
  if ((ispeed >= 0) and (ispeed <= 255))
  {
    stop ();  // ensure control pins at 0,0 before changing
    digitalWrite(M1_1A, LOW);
    analogWrite (M1_1B, ispeed);
    digitalWrite(M2_1A, LOW);
    analogWrite (M2_1B, ispeed);
  }
}

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

/*–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––/

  This function moves the car in reverse at a specified speed.

/–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
void reverse (int ispeed) //ispeed between 0 and 255
{
  if ((ispeed >= 0) and (ispeed <= 255))
  {
    stop ();  // ensure control pins at 0,0 before changing
    analogWrite (M1_1A, ispeed);
    digitalWrite(M1_1B , LOW);
    analogWrite (M2_1A, ispeed);
    digitalWrite(M2_1B , LOW);
  }
}

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/


/*–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––/

  This function makes the car do a forward left point turn
    at a specified speed.

/–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

void forward_L(int ispeed)
{
  if ((ispeed >= 0) and (ispeed <= 255))
  {
    stop ();  // ensure control pins at 0,0 before changing
    digitalWrite(M1_1A, LOW);
    analogWrite (M1_1B, ispeed);
    digitalWrite(M2_1A, LOW);
    digitalWrite(M2_1B, LOW);
  }
}

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/


/*–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––/

  This function makes the car do a forward right point turn
    at a specified speed.

/–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

void forward_R(int ispeed)
{
  if ((ispeed >= 0) and (ispeed <= 255))
  {
    stop ();  // ensure control pins at 0,0 before changing
    digitalWrite(M1_1A, LOW);
    digitalWrite(M1_1B, LOW);
    digitalWrite(M2_1A, LOW);
    analogWrite (M2_1B, ispeed);
  }
}

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/


/*–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––/

  This function makes the car do a reverse left point turn
    at a specified speed.

/–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

void reverse_L(int ispeed)
{
  if ((ispeed >= 0) and (ispeed <= 255))
  {
    stop ();  // ensure control pins at 0,0 before changing
    analogWrite (M1_1A , ispeed);
    digitalWrite(M1_1B , LOW);
    digitalWrite(M2_1A , LOW);
    digitalWrite(M2_1B , LOW);
  }
}

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/


/*–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––/

  This function makes the car do a reverse right point turn
    at a specified speed.

/–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

void reverse_R(int ispeed)
{
  if ((ispeed >= 0) and (ispeed <= 255))
  {
    stop ();  // ensure control pins at 0,0 before changing
    digitalWrite(M1_1A , LOW);
    digitalWrite(M1_1B , LOW);
    analogWrite (M2_1A , ispeed);
    digitalWrite(M2_1B , LOW);
  }
}

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/


/*–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––/

  This function stops the car.

/–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

void stop()
{
    digitalWrite(M1_1A, LOW);
    digitalWrite(M1_1B , LOW);
    digitalWrite(M2_1A, LOW);
    digitalWrite(M2_1B , LOW);
}

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
