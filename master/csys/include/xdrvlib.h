#ifndef XDRVLIB_H
#define XDRVLIB_H

/* Data Structure for CADDS5 implementation */
#define MagellanInputMotionEvent 1
#define MagellanInputButtonPressEvent 2
#define MagellanInputButtonReleaseEvent 3

union MagellanIntUnion {
	int data[7];
	int button;
};

struct MagellanIntEvent {
	int type;
	MagellanIntUnion u;
};


/* Data Structure for Pro/ENGINEER implementation */
enum _MagellanData_ {
	MagellanX,
	MagellanY,
	MagellanZ,
	MagellanA,
	MagellanB,
	MagellanC
};

struct MagellanFloatEvent {
	int MagellanType;
	int MagellanButton;
	double MagellanData[6];
	int MagellanPeriod;
};

bool MagellanInit(Display*, Window);

bool MagellanSetWindow(Display*, Window);

bool MagellanApplicationSensitivity(Display*, double);

int MagellanErrorHandler(Display*, XErrorEvent*);

bool MagellanInputEvent(Display*, XEvent*, MagellanIntEvent*);

int MagellanTranslateEvent(Display*, XEvent*, MagellanFloatEvent*, double, double);

void MagellanClose(Display*);

Bool MagellanCheckMotionEvent(Display*, XEvent*, char*);

void MagellanRemoveMotionEvents(Display*);

enum _CommandMessages_ {
	NoCommandMessage,
	CommandMessageApplicationWindow = 27695,
	CommandMessageApplicationSensitivity
};

union MagellanTypeConversion {
	float Float;
	short Short[2];
};

#define XHigh32(Value) (Value >> 16) & 0xFFFF
#define XLow32(Value) Value & 0xFFFF

#endif  /* Magellan X Window Driver Header */
