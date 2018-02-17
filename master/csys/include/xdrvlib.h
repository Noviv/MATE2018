#ifndef XDRVLIB_H
#define XDRVLIB_H

/* Data Structure for CADDS5 implementation */
#define MagellanInputMotionEvent 1
#define MagellanInputButtonPressEvent 2
#define MagellanInputButtonReleaseEvent 3

union _MagellanInputEventUnion_ {
	int data[7];
	int button;
};
typedef union _MagellanInputEventUnion_ MagellanIntUnion;

struct _MagellanIntEvent_ {
	int type;
	MagellanIntUnion u;
};
typedef struct _MagellanIntEvent_ MagellanIntEvent;


/* Data Structure for Pro/ENGINEER implementation */
enum _MagellanData_ {
	MagellanX,
	MagellanY,
	MagellanZ,
	MagellanA,
	MagellanB,
	MagellanC
};

struct _MagellanFloatEvent_ {
	int MagellanType;
	int MagellanButton;
	double MagellanData[6];
	int MagellanPeriod;
};

typedef struct _MagellanFloatEvent_ MagellanFloatEvent;



bool MagellanInit(Display*, Window);

bool MagellanSetWindow(Display*, Window);

bool MagellanApplicationSensitivity(Display*, double);

int MagellanErrorHandler(Display*, XErrorEvent*);

bool MagellanInputEvent(Display*, XEvent*, MagellanIntEvent*);

int MagellanTranslateEvent(Display*, XEvent*, MagellanFloatEvent*, double, double);

bool MagellanClose(Display*);

Bool MagellanCheckMotionEvent(Display*, XEvent*, char*);

bool MagellanRemoveMotionEvents(Display*);

extern Atom MagellanMotionEvent, MagellanButtonPressEvent, MagellanReleaseEvent;
extern Window MagellanWindow;
extern bool MagellanExist;

enum _CommandMessages_ {
	NoCommandMessage,
	CommandMessageApplicationWindow = 27695,
	CommandMessageApplicationSensitivity
};

union _MagellanTypeConversion_ {
	float Float;
	short Short[2];
};

typedef union _MagellanTypeConversion_ MagellanTypeConversion;

#define XHigh32(Value) (Value >> 16) & 0xFFFF
#define XLow32(Value) Value & 0xFFFF

#endif  /* Magellan X Window Driver Header */
