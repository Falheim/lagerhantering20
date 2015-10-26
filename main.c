#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
  bool should_quit = false;
  
  while (!should_quit)
    {
      puts("AREPLUQ"); // Valmöjligheter, ersätt med print main menu() eller något
      char input = getchar(); // getchar är förenklat, ersätt med get char när moduler sätts in
      
      switch(toupper(input))
	{
	case 'A': // Add
	  puts("A"); 
	  break;
	  
	case 'R': // Remove
	  puts("R");
	  break;
	  
	case 'E': // Edit
	  puts("E");
	  break;
	  
	case 'L': // List
	  puts("L");
	  break;
	  
	case 'U': // Undo
	  puts("U");
	  break;
	  
	case 'Q': // Quit
	  should_quit = true;
	  break;
	  
	default:
	  puts("Something went wrong. err: default case in main");
	}
    }
}
