#ifndef __IDENTIFIER__
#define __IDENTIFIER__

class Identifier {
public:
  int getID();
  Identifier(int analogInputPin);

private:
	int analogInputPin;
};

#endif
