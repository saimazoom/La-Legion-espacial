
// zcc +zx -vn font_E.c -o font_E -create-app -lfzx -lndos

#include <fzx.h>
#include <string.h>
#include <spectrum.h>
#include <input.h>

char *msg = "FZX Fonts by aowen";
struct fzx_enum *e;

main()
{
   int i;
   
   zx_border(INK_BLACK);
   
   while (1)
   {
      // clear screen
      
      memset(16384, 0, 6144);
      memset(22528, INK_BLUE | PAPER_CYAN, 768);
 
      // center introductory message
      
      fzx.font = ff_Swiss;
      fzx.x = (256 - fzx_sExtent(msg)) / 2;
      fzx.y = (192 - (fzx.font->height)) / 2;
      
      fzx_puts(msg);
      
      // wait for key

      in_WaitForNoKey();
      in_WaitForKey();
      
      e = fzxfonts_enum_E;
      while (e->name)
      {
   
         // clear screen
      
         memset(16384, 0, 6144);
         memset(22528, INK_BLACK | PAPER_GREEN, 768);

         // print sample text
      
         fzx.font = ff_Swiss;
         fzx.x = 0; fzx.y = 8;     // use fzx_setat() if you need to worry about left margin
      
         fzx_puts("FONT: ");
         fzx_puts(e->name);
         fzx_puts("\n\n");
      
         fzx.font = e->font;
         fzx_puts("The quick brown fox jumped over the lazy dogs.\n\n");
      
         for (i = 32; i <= (fzx.font->last_char); ++i)
            fzx_putc(i);
      
         // wait for key
         
         in_WaitForNoKey();
         in_WaitForKey();
         
         // next font
         
         ++e;
      }
   
      // returning to basic would crash so let's just loop
      
   }
}
