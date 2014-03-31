// OCL Sample Balloons
// common header for server and client



typedef struct _PIPE_MSG
{
 USHORT  Type;
 USHORT  Data;
} PIPEMSG,  *PPIPEMSG;


#define BALL_PIPE "\\PIPE\\BALLOONS.PIP"
#define BALL_SEM "\\SEM32\\BALLOONS.SEM"

// Messages

#define PIPE_CLIENT_EXIT      WM_USER+1
#define PIPE_START_BALLOONS   WM_USER+2
#define PIPE_STOP_BALLOONS    WM_USER+3
#define PIPE_STOP_CLIENT      WM_USER+4
#define PIPE_SET_NUM          WM_USER+5
#define PIPE_SET_SPEED        WM_USER+6
#define PIPE_SERVER_EXIT      WM_USER+7

// end of source 
