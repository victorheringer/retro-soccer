void scrollable_pad_list() {
  int ITEMS_TO_SHOW = 4, END = 0; 
  uint8_t key;
  char* list[17];

  while(1) {
    key = waitpad(J_UP | J_DOWN | J_START);
    waitpadup();

    clear_screen();

    switch(key) {
		
      case J_UP :
        if(SCROLL_LIST_STATE > 0) {
          SCROLL_LIST_STATE--;
        }
        
        break;
      case J_DOWN :
        if(SCROLL_LIST_STATE < sizeof(list)) {
          SCROLL_LIST_STATE++;
        }
        break;
      case J_START : 
        END = 1;
      default :
        break;	
    }

    if(END == 1) {
      return;
    }

    for(int i = 0; i < ITEMS_TO_SHOW; i++) {
      printf("%s POS-%d             ", SCROLL_LIST_STATE == i ? ">" : " ", i);
    }
    
  }
}