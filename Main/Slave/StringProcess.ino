uint8_t GetChar(int index) {
  static uint8_t RtrCh[16] = "0123456789ABCDEF";
  return RtrCh[index];
}

uint8_t* GetRoute(uint8_t chr) {
  switch (chr) {
    case 'H': {
      return "Head";
    }
    case 'L': {
      return "left";
    }
    case 'R': {
      return "right";
    }
    case 'T': {
      return "to";
    }
    case 'E': {
      return "elevator";
    }
    case 'S': {
      return "stair";
    }
    case 'D': {
      return "destination";
    }
    case 'Y': {
      return "your";
    }
  }
}

