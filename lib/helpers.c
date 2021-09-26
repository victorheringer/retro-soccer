void clear_screen(void) {
  uint8_t x, y = 18;
  
  while (y) {
    y -= 1;
    x = 20;
      
    while (x) {
      x -= 1;
      gotoxy(x, y);
      setchar(' ');
    }
  }
}

void blank_lines(int number) {
  for(int i = 0; i < number; i++) {
    printf("                    ");
  }
}