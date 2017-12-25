
 
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


 
int main(void)
{
    Display *display;
    Window window;
    XEvent event;
    char *msg = "Hello, World!";
    int s;
 
    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

 
    s = DefaultScreen(display);
 
    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 200, 200, 1, BlackPixel(display, s), WhitePixel(display, s));
 
    /* select kind of events we are interested in */
    XSelectInput(display, window, ExposureMask | KeyPressMask);
 
    /* map (show) the window */
    XMapWindow(display, window);
   
 
    int keep_running = 1;
    int x1, y1; x1 = 1; y1 = 1;
    y1 = 10;


    /* event loop */
    while ( keep_running == 1 )
    {
        XNextEvent(display, &event);
 
        /* draw or redraw the window */
        //if (event.type == Expose)
        {
            XDrawString(display, window, DefaultGC(display, s), 50, 50, msg, strlen(msg));
            XFillRectangle(display, window, DefaultGC(display, s), x1 , y1 , 5 , 5 );
        }

        if (event.type == KeyPress)
        {
            printf( "keypress type %d\n", event.type );
            printf( "keypress keycode 02x %02x\n", event.xkey.keycode );
            printf( "keypress keycode dec %d\n", event.xkey.keycode );

            if ( event.xkey.keycode == 9 ) printf( "KEY ESC\n" );
            if ( event.xkey.keycode == 9 ) keep_running = 0;

            if ( event.xkey.keycode == 44 ) y1 = y1 + 10; //j 
            if ( event.xkey.keycode == 45 ) y1 = y1 - 10; //k 

            if ( event.xkey.keycode == 43 ) x1 = x1 - 10; //h
            if ( event.xkey.keycode == 46 ) x1 = x1 + 10; //l
        }
    }
 
    XCloseDisplay(display);
    return 0;
 }
