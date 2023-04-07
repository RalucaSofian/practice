#ifndef RENDERER_H
#define RENDERER_H
/* @file renderer.h
*
*
*
*
*
*/

/******************
* FUNC DECLARATIONS
******************/

/*  Init GLFW Lib 
*   return 0 if init was successful
*   return -1 otherwise
*/
int rend_init(void);

/*  Create GLFW window and bring it into focus 
*   [in] - window title and window measurements
*   return 0 if creation was successful
*   return -1 otherwise
*/
int rend_create_window(const char* title, int width, int height);

/* Renderer main loop
*  will run until user closes window */
void rend_window_render(void);

/*  Deinit GLFW Lib */
void rend_deinit(void);

#endif /* RENDERER_H */