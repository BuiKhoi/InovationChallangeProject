void FreeMode() {
  if (ListeningMessage) {
    if (NewMessage) {
      SysMode = 1;
    } else {
      BeginMessageListener();
//      ReciveMessage();
    }
  }
}

void ShowInfo() {
  
}

void ShowDirection() {
  
}
