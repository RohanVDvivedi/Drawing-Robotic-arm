#include <iostream>
#include <cmath>
#include <SerialClass.h>
#include <windows.h>
Serial s("COM3");  // i used a Serial lib found in one of my previous repository

using namespace std;

float r=31;
float shoulder=90,elbow=90,pen=0; // the values that would be sent
// shoulder for shoulder servo, elbow for elbow servo and the pen tells whether to write or just hover

float x,y;
int pen_pos=0;
unsigned int sh=0,eb=0,pe=0; // finalised data sending variables

void go_servo_go()
{
    /*
        we have 3 data to be sent now shoulder angle , elbow angle and pen
        since we need a resolution of 0.1 degrees and we can send only unsigned integers
        i am multiplying the data here to 10 and than sending to the microcontroller
        the microcontroller devides the data by 10 and writes it to servos
        it also echo the acknowlegement tht is the same data
        it is checked if it is true and them proceeded
        else a problem message is print on the screen
    */

    Sleep(6);

    s.write_uint_serial((int)( shoulder*10 ));
    Sleep(6);// on the microcontroller side i am echoeing the data back
    sh=s.read_uint_serial();

    if(sh==(unsigned int)( shoulder*10 )) // incase the data is misread
    {
        cout<<"DONE - "<<sh<<" = "<<(unsigned int)( shoulder*10 )<<"\t";
    }
    else
    {
        cout<<"Problem - "<<sh<<" != "<<(unsigned int)( shoulder*10 )<<"\t";
        sh=s.read_uint_serial();
    }

    s.write_uint_serial((int)( elbow*10 ));
    Sleep(6);
    eb=s.read_uint_serial();
    if(eb==(unsigned int)( elbow*10 ))
    {
        cout<<"DONE - ";
    }
    else
    {
        cout<<"Problem -  "<<eb<<" != "<<(unsigned int)( elbow*10 )<<"\t";
        eb=s.read_uint_serial();
    }





    s.write_uint_serial((int)( pen_pos ));
    Sleep(6);
    pe=s.read_uint_serial();
    if(pe==(unsigned int)( pen_pos ))
    {
        cout<<"DONE - \n";
    }
    else
    {
        cout<<"Problem - "<<pe<<" != "<<(unsigned int)( pen_pos )<<"\n";
        pe=s.read_uint_serial();
    }


    Sleep(1);
}








int get_angles(float x,float y)
{
    /*
        i am using a geometrical mathematical conversion from
        x,y cartesian coordinates to the angular coordinates that my robotic system understands
        the final angles are stored in floats shoulder and elbow variable
    */

    if(x<0 || y<0)
    {
        return 0;
    }

    float c;
    float m;
    float xlt;
    float ylt;

    if(y>0 && x>=0)
    {
        c=(x*x+y*y)/(2*y);
        m=(-1*x/y);
        xlt=(   ( sqrt(r*r*(1+m*m)-(c*c) ) ) - c*m   )/(1+m*m);
        ylt=xlt*m+c;
    }
    else if (y==0 && x!=0)
    {
        m=x/2;
        xlt=m;
        ylt=sqrt(r*r-m*m)*(-1);
    }
    else if (y==0 && x==0)
    {
        elbow=0;
        return 0;
    }

    //cout<<"xl = "<<xl<<"\n yl = "<<yl<<endl;

    shoulder=(180/3.14)*acos((double)(ylt/r));

    elbow=(180/3.14)*acos((double)((xlt-x)/r)) - shoulder + 90;

    if(shoulder<0)
    {
        shoulder=0;
    }
    else if(shoulder>180)
    {
        shoulder=180;
    }

    if(elbow<0)
    {
        elbow=0;
    }
    else if(elbow>180)
    {
        elbow=180;
    }

    //cout<<"shoulder angle = "<<shoulder<<" elbow angle = "<<elbow<<endl;

    return 0;
}







POINT mouse_position; // predefined windows structure variable used to store mouse pointer location





int main()
{
    while(GetAsyncKeyState(VK_ESCAPE)==0)
    {
        // if else condition
        /*
            bot will write when pen_position is 1
            the condition is achieved when left mouse button is pressed and hold
        */
        if(GetAsyncKeyState(VK_LBUTTON)!=0)
        {
            pen_pos=0;
        }
        else
        {
            pen_pos=1;
        }

        GetCursorPos(&mouse_position); // function is used to get the mouse position

        // now at this point we have the current mouse position on our screen

        // cout<<"x is "<<mouse_position.x<<" and y is "<<mouse_position.y<<endl;
        // uncomment above line to let your code print the present coordinates of mouse pointer on the screen

        x=(float)(mouse_position.y)*(31.0/767.0);
        y=(float)(mouse_position.x)*(40.0/1365.0);
        /*
            scale the screen coordinates to the drawing board coordinates
            my scree coordinates were 767 * 1365
            and my drawing board was 31 inch * 40 inch
        */

        //cout<<" x = "<<x<<" and y = "<<y<<endl;
        // uncomment above line to let the code print your normalised position on the screen

        get_angles(  x   ,  y  ); // this function is devised to get angles that were required in my case


        go_servo_go();  // send the required position or in my case the angles to the uC board


    }
    return 0;
}
